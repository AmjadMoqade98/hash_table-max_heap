#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/hash_table.h"
#include "../headers/max_heap.h"

#define INITIAL_SIZE   4

struct  years_freq
{
    int years[50];
    int freq[50];
    int n ;
};


struct table_entry
{
    char name[50];
    char gender;
    char key[51];
    years_freq* years_freq;
};

struct hash_table
{
    table_entry* entries;
    size_t size; // total number of slots in the table
    size_t used; // number of used slots in the table
};



hash_table* create_table()
{
    // Allocate space for hash table.
    hash_table* table = malloc(sizeof(hash_table));
    if (table == NULL)
    {
        return NULL;
    }
    table->used = 0;
    table->size = INITIAL_SIZE;

    // Allocate space for entries.
    table->entries = calloc(table->size, sizeof(table_entry));

    for(int i = 0 ; i < table->size ; i++)
    {
        table->entries[i].years_freq =  malloc(sizeof(years_freq));
        table->entries[i].years_freq->n = 0;
    }

    if (table->entries == NULL)
    {
        free(table);
        return NULL;
    }
    return table;
}

void destroy_table(hash_table* table)
{

    //free keys in entries.
    for (size_t i = 0; i < table->size; i++)
    {
        if (table->entries[i].key != NULL)
        {
            free((void*)table->entries[i].key);
        }
    }

    // Then free entries.
    free(table->entries);
    free(table);
}

int hash_code(const char* key)
{
    int len = strlen(key);

    int hash = 0;
    for (int i = 0; i < len; i++)
    {
        hash = 31*hash + key[i];
    }

    return hash;
}

char* insert_entry(table_entry* entries, size_t size, char key[51], size_t* used, char name[50], char gender, int year)
{

    int hash = hash_code(key);
    size_t index = (size_t)(hash % size);
    int j = 1 ;
    // Loop till we find an empty entry using quadratic probing .
    while (strlen(entries[index].key) != 0)
    {
        if (strcmp(key, entries[index].key) == 0)
        {
            int yearNum = entries[index].years_freq->n;
            for(int i = 0 ; i< yearNum; i++)
            {
                if(year == entries[index].years_freq->years[i])
                {
                    entries[index].years_freq->freq[i]++;
                    return -1 ;
                }
            }

            entries[index].years_freq->years[yearNum] = year;
            entries[index].years_freq->freq[yearNum] = 1 ;
            entries[index].years_freq->n++;

            return -1;
        }
        // Key wasn't in this slot, move to next (linear probing).

        index += j*j;
        j++;

        if (index >= size)
        {
            // At end of entries array, wrap around.
            index = 0;
        }
    }

    if(used != NULL)
    {
        (*used)++;
    }
    strcpy(entries[index].key, key);
    strcpy(entries[index].name, name);
    entries[index].gender = gender;
    entries[index].years_freq->years[0] = year;
    entries[index].years_freq->freq[0] = 1 ;
    entries[index].years_freq->n = 1;

    return 1;
}

bool expand_table(hash_table* table)
{

    size_t new_size = table->size * 2;

    if (new_size < table->size)
    {
        return false;  // overflow (size would be too big)
    }

    table_entry* new_entries = calloc(new_size, sizeof(table_entry));

    for(int i = 0 ; i < new_size ; i++)
    {
        new_entries[i].years_freq =  malloc(sizeof(years_freq));
        new_entries[i].years_freq->n = 0;
    }
    if (new_entries == NULL)
    {
        return false;
    }


    // move all non-empty old table entries to new table entries.
    for (size_t i = 0; i < table->size; i++)
    {
        table_entry entry = table->entries[i];
        if (strlen(entry.key) != 0)
        {
            for(int j = 0 ; j < entry.years_freq->n; j++)
            {
                insert_entry(new_entries, new_size, entry.key,NULL,entry.name, entry.gender,entry.years_freq->years[j]);
            }

        }
    }
    // Free old entries array and update this table's details.
    free(table->entries);
    table->entries = new_entries;
    table->size = new_size;
    return true;
}

char* insert_record(hash_table* table, char key[51], char name[50], char gender, int year)
{
    assert(strlen(key) != 0);
    if (strlen(key) == 0)
    {
        return -1;
    }

    // If length will exceed half of current size, expand it.
    if (table->used >= table->size / 2)
    {
        if (!expand_table(table))
        {
            return NULL;
        }
    }
    // Set entry and update length.
    return insert_entry(table->entries, table->size, key,&table->used, name, gender, year);
}

void print_table(hash_table* table)
{
    printf("table size: %d\n", table->size);
    printf("table used size: %d\n", table->used);
    printf("table entries: \n\n");
    table_entry* entries = table->entries;
    for (int i = 0; i < table->size; i++)
    {
        table_entry entry = entries[i];
        printf("index %d :", i);

        if (strlen(entry.key) == 0)
        {
            printf("empty\n");
        }
        else
        {
            int total_freqency = 0 ;
            for(int j = 0 ; j < entry.years_freq->n ; j++)
            {
                total_freqency+= entry.years_freq->freq[j];
            }
            printfln("\n\tkey: %s", entry.key);
            printfln("\tname: %s", entry.name);
            printfln("\tgender: %c", entry.gender);
            printfln("\ttotal_frequency: %d",total_freqency);
        }
    }
}

int get_record_index(hash_table* table, const char* key)
{

    int hash = hash_code(key);
    size_t index = (size_t)(hash % table->size);

    int j = 1 ;
    while (strlen(table->entries[index].key)!= 0)
    {
        if (strcmp(key, table->entries[index].key) == 0)
        {
            // Found key, return value.
            return index;
        }

        index += j*j;
        j++;

        if (index >= table->size)
        {
            // At end of entries array, wrap around.
            index = 0;
        }
    }
    return -1;
}


void search_record(hash_table* table, char key[50])
{

    int index = get_record_index(table,key);

    if(index == -1)
    {
        printfln("$ key does not exist");
    }
    else
    {
        table_entry entry = table->entries[index];


        heapSort(entry.years_freq->freq,entry.years_freq->years,entry.years_freq->n);

        int nyears = entry.years_freq->n;

        for(int i = 0 ; i< nyears ; i++)
        {
            printfln("year: %d , frequency= %d", entry.years_freq->years[i], entry.years_freq->freq[i]);
        }
    }
}

int delete_record(hash_table* table, char key[51])
{
    int record_index = get_record_index(table,key);

    printf("%d", record_index);
    if(record_index != -1)
    {
        table->entries[record_index].key[0] = '\0';
        table->used--;
    }
    return record_index;
}

void add_year_freq(hash_table* table, char key[50], int year, int freq)
{
    int index = get_record_index(table,key);

    if(index == -1)
    {
        printfln("$ key does not exist");
        return ;
    }
    else
    {
        table_entry entry = table->entries[index];
        int yearNum = entry.years_freq->n;
        for(int i = 0 ; i< entry.years_freq->n ; i++) {
            if(year == entry.years_freq->years[i]){
                printfln("$ year exists");
                return ;
            }
        }

        entry.years_freq->years[yearNum] = year;
        entry.years_freq->freq[yearNum] = freq ;
        entry.years_freq->n++;

        printfln("$ year/freq record added");
    }
}

void update_year_freq(hash_table* table, char key[50], int year, int freq)
{
    int index = get_record_index(table,key);

    if(index == -1)
    {
        printfln("$ key does not exist");
        return ;
    }
    else
    {
        table_entry entry = table->entries[index];

        for(int i = 0 ; i< entry.years_freq->n ; i++) {
            if(year == entry.years_freq->years[i]){
                entry.years_freq->freq[i] = freq ;
                printfln("$ key/freq record updated");
                return ;
            }
        }

        printfln("$ year not exist");
    }
}

