#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5


typedef struct{
    char name[80];
    long number;
}PhoneEntry;

typedef struct PhoneBook_t{
    PhoneEntry *entries;
    int total;
    int max;
}PhoneBook;

PhoneBook* createPhoneBook(){
    PhoneBook* book = malloc(sizeof(PhoneBook));
    book->entries = malloc(INITIAL_SIZE*sizeof(PhoneEntry));
    book->total = 0;
    book->max = INITIAL_SIZE;
    return book;
}

PhoneEntry newPhoneEntry(char *name,long number){
    PhoneEntry new;
    strcpy(new.name,name);
    new.number = number;
    return new;
}

PhoneBook* addPhoneBook(PhoneBook* book,char *name,long number){
    int total_tmp = book->total;
    int max_tmp = book->max;
    PhoneEntry new = newPhoneEntry(name,number);
    if(total_tmp >= max_tmp){
        book->max = book->max + INCREMENTAL_SIZE;
    }
    strcpy(book->entries[total_tmp].name,new.name);
    book->entries[total_tmp].number = new.number;
    book->total++;
    return book;
};

void printPhoneBook(PhoneBook* book){
    int total_tmp = book->total;
    int i;
    for(i = 0; i< total_tmp;i++){
        printf("%d:\nName:%s\nPhone:%ld\n",i,book->entries[i].name,book->entries[i].number);
    }
}

int main(){
    PhoneBook* book = createPhoneBook();
    book = addPhoneBook(book,"tuan",10000);
    book = addPhoneBook(book,"ha",20000);
    book = addPhoneBook(book,"linh",100000);
    book = addPhoneBook(book,"dat",12312312323);
    printPhoneBook(book);
    return 0;

}