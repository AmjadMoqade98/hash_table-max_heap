#include <stdbool.h>
#include <stddef.h>


typedef struct hash_table hash_table;
typedef struct table_entry table_entry;
typedef struct years_freq years_freq;

hash_table* create_table();

void destroy_table(hash_table* table);

char* insert_record(hash_table* table, char key[51], char name[50] , char gender, int year);

void print_table(hash_table* table);

int delete_record(hash_table* table, char key[51]);

void search_record(hash_table* table , char key[50]);

void add_year_freq(hash_table* table , char key[50], int year , int freq);

void update_year_freq(hash_table* table , char key[50], int year , int freq);
