#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
    void* name;
    void* phone;
}Entry;

typedef struct {
    Entry *entries;
    int size,total;
    Entry (*makeNode)(void*,void*);
    int (*comparePhone)(void*,void*);
}PhoneBook;

//Make new entry
Entry makeNode(void* name,void* phone){
    Entry new;
    new.name = strdup((char*)name);
    new.phone = strdup((char*)phone);
    return new;
}

//Free SymbolTable
void dropPhoneBook(PhoneBook book){
    int i;
    for(i = 0; i< book->total;i++){
        free(book->entries[i].name);
        free(book->entries[i].phone);
    }
    free(book->entries);
    free(book);
}

//Compare by key
int comparePhone(void* key1,void* key2){
    return strcmp((char*)key1,(char*)key2);
}

//Create new Symbol Table
PhoneBook* createPhoneBook(Entry (*makeNode)(void*,void*),int (*comparePhone)(void*,void*)){
    PhoneBook* book = malloc(sizeof(PhoneBook));
    book->entries = malloc(INITIAL_SIZE*sizeof(Entry));
    book->total = 0;
    book->size = INITIAL_SIZE;
    book->makeNode = makeNode;
    book->comparePhone = comparePhone;
    return book;
}

PhoneBook* addPhoneBook(PhoneBook* book,void *name,void* phone){
    int total_tmp = book->total;
    int max_tmp = book->size;
    book->entries[book->total] = book->makeNode(name,phone);
    if(total_tmp >= max_tmp){
        book->size = book->size + INCREMENTAL_SIZE;
        book->entries = relloc(book->entries,INITIAL_SIZE*sizeof(Entry));
    }
    book->total++;
    return book;
};

Entry* getEntry(void* name,PhoneBook book){
    int i,state;
    state = 0;
    for(i = 0; i< book->total;i++){
        if(strcmp(book->entries[i].name,name) == 0){
            return book->entries[i];
            state = 1;
        }
    }
    if(state == 1){
        printf("Found\n");
    }else{
        printf("Not found\n");
    }
    return NULL;
};

void printPhoneBook(PhoneBook* book){
    long tmp = 0;
    int i;
    for(i = 0; i< book->total;i++){
        tmp = atoi(book->entries[i].phone);
        printf("%d:\nName:%s\nPhone:%ld\n",i,book->entries[i].name,tmp);
    }
}

int main(){
    PhoneBook* book = createPhoneBook(makeNode,comparePhone);
    book = addPhoneBook(book,"tuan","1300000000");
    book = addPhoneBook(book,"ha","20000");
    book = addPhoneBook(book,"linh","20000");
    book = addPhoneBook(book,"dat","20000");
    printPhoneBook(book);
    dropPhoneBook(book);
    return 0;

}