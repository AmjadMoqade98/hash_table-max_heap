#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash_table.h"

void insertRecordToTable(table_entry* table)
{
    char name[50];
    char gender;
    int year;

    printf("Name: ");
    gets(name);
    gets(name);

    char name1[50];
    strcpy(name1,name);

    printf("Gender: ");
    scanf("%c", &gender);

    printf("Year: ");
    scanf("%d", &year);

    char key[51];
    sprintf(key,"%s%c\0",name1,gender);

    int response = insert_record(table,key,name1, gender,year );
    if(response != -1 )
    {
        printfln("$ record with key= %s inserted", key );
    }
    else
    {
        printfln("$ key already exist or no enough memory to store the record");
    }
}

void deleteRecordFromTable(table_entry* table)
{
    char name[50];
    char temp[100];
    char gender[1];
    char key[51];

    printf("Name to search: ");
    gets(name);
    gets(name);
    sprintf(key,"%s\0",name);

    printf("Gender: ");
    gets(gender);
    sprintf(key,"%s%s\0",key,gender);

    int response = delete_record(table,key);
    if(response != -1 )
    {
        printfln("$ record with key= %s deleted", key );
    }
    else
    {
        printfln("$ record does not exist");
    }
}

void searchForName(table_entry* table)
{
    char name[50];
    char gender;

    printf("Name: ");
    gets(name);
    gets(name);

    char name1[50];
    strcpy(name1,name);

    printf("Gender: ");
    scanf("%c", &gender);

    char key[51];
    sprintf(key,"%s%c\0",name1,gender);

    search_record(table, key);
}


void updateYearFreqRecord(table_entry* table)
{

    char name[50];
    char gender;
    int year, freq;

    printf("Name: ");
    gets(name);
    gets(name);

    char name1[50];
    strcpy(name1,name);

    printf("Gender: ");
    scanf("%c", &gender);

    char key[51];

    sprintf(key,"%s%c\0",name1,gender);

    printf("Year: ");
    scanf("%d", &year);

    printf("Freq: ");
    scanf("%d", &freq);

    update_year_freq(table, key, year, freq);
}

void addYearFreqRecord(table_entry* table)
{

    char name[50];
    char gender;
    int year, freq;

    printf("Name: ");
    gets(name);
    gets(name);

    char name1[50];
    strcpy(name1,name);

    printf("Gender: ");
    scanf("%c", &gender);

    char key[51];
    sprintf(key,"%s%c\0",name1,gender);

    printf("Year: ");
    scanf("%d", &year);

    printf("Freq: ");
    scanf("%d", &freq);

    add_year_freq(table, key, year, freq);
}


void read_names_from_file(table_entry* table)
{
    char name [50], key[51];
    char gender;
    int freq, year;

    printfln("Enter year: ");
    scanf("%d",&year);


    char path[21] ;
    sprintf(path, "data/names_%d.txt\0",year);

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen(path, "r");

    while(fgets(buffer, bufferLength, filePointer))
    {
        char * token = strtok(buffer, ",");
        strcpy(name,token);

        token = strtok(NULL, ",");
        gender = *token;

        token = strtok(NULL, ",");
        freq = atoi(token);

        sprintf(key,"%s%c\0",name,gender);

        for(int i =0 ; i < freq ; i++) {
            insert_record(table,key,name,gender,year);
        }
    }

    fclose(filePointer);
    printfln("$ records added from file successfuly");

}

