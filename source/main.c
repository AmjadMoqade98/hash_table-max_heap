#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/printfln.h"
#include "../headers/hash_table.h"
#include "../headers/ui_actions.h"

hash_table* table ;
int main()
{
    table = create_table();

    while(1)
    {
        printMenu();
        int option = inputMenuOption();
        performInterfaceAction(option);

    }

    return 0 ;
}

bool autoDirectoryFlag = true ;
void printMenu()
{
    printfln("\n\n************ Menu ************");
    printfln("1- load names files from a specific folder");
    printfln("2- print hash table ");
    printfln("3- add new name/gender record");
    printfln("4- delete a name record");
    printfln("5- add new names year/freq record");
    printfln("6- update a names year/freq record");
    printfln("7- search for name ");
    if(autoDirectoryFlag)
    {
        printfln("8- disable auto directory to load the names");
    }
    else
    {
        printfln("8- enable auto directory to load the names");
    }
    printfln("9- exit the program");
    printfln("******************************");
}

int inputMenuOption()
{
    int option;
    printf("Select an option: ");
    scanf("%d", &option);
    return option;
}

void performInterfaceAction(int option)
{
    switch (option)
    {
    case 1:
    {
        read_names_from_file(table);
        break;
    }
    case 2:
    {
        print_table(table);
        break;
    }
    case 3:
    {
        insertRecordToTable(table);
        break;
    }
    case 4:
    {
        deleteRecordFromTable(table);
        break;
    }
    case 5:
    {
        addYearFreqRecord(table);
        break;
    }
    case 6:
    {
        updateYearFreqRecord(table);
        break;
    }
    case 7:
    {
        searchForName(table);
        break;
    }
    case 8:
    {
        autoDirectoryFlag = !autoDirectoryFlag;
        break;
    }
    case 9:
    {
        exit(1);
        break;
    }

    default:
        printfln("$ wrong option");
        break;
    }
}
