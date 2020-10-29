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

Entry makeNode(void* name,void* phone){
    Entry new;
    new.name = strdup((char*)name);
    new.phone = malloc(2*sizeof(long)); //Why 2*sizeoflong ?
    memcpy(new.phone,phone,2*sizeof(long));
    return new;
}

int comparePhone(void* key1,void* key2){
    return strcmp((char*)key1,(char*)key2);
}

PhoneBook* createPhoneBook(Entry (*makeNode)(void*,void*),int (*comparePhone)(void*,void*)){
    PhoneBook* book = malloc(sizeof(PhoneBook));
    book->entries = malloc(INITIAL_SIZE*sizeof(Entry));
    book->total = 0;
    book->size = INITIAL_SIZE;
    book->makeNode = (*makeNode);
    book->comparePhone = (*comparePhone);
    return book;
}

PhoneBook* addPhoneBook(PhoneBook* book,void *name,void* phone){
    int total_tmp = book->total;
    int max_tmp = book->size;
    book->entries[book->total] = book->makeNode(name,phone);
    if(total_tmp >= max_tmp){
        book->size = book->size + INCREMENTAL_SIZE;
    }
    book->total++;
    return book;
};

void printPhoneBook(PhoneBook* book){
    long tmp = 0;
    int total_tmp = book->total;
    int i;
    for(i = 0; i< total_tmp;i++){
        tmp = atoi(book->entries[i].phone);
        printf("%d:\nName:%s\nPhone:%ld\n",i,book->entries[i].name,tmp);
    }
}

int main(){
    Entry (*makeNode_ptr)(void*,void*) = &makeNode;
    int (*comparePhone_ptr)(void*,void*) = &comparePhone;
    PhoneBook* book = createPhoneBook((*makeNode_ptr),(*comparePhone_ptr));
    book = addPhoneBook(book,"tuan","1300000000");
    book = addPhoneBook(book,"ha","20000");
    book = addPhoneBook(book,"linh","20000");
    book = addPhoneBook(book,"dat","20000");
    printPhoneBook(book);
    return 0;

}