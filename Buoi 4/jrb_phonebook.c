#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

//Print all names and phone numbers
void jrb_print_db(JRB tree){
    JRB tmp;
    jrb_traverse(tmp,tree){
        printf("Name:%s - Phone:%ld\n",jval_s(tmp->key), jval_l(tmp->val));
    }

}

//Find a name based on a phone numbers
JRB jrb_find_key(JRB tree,Jval value){
    JRB tmp;
    jrb_traverse(tmp,tree){
        if(jval_l(tmp->val) == jval_l(value)){
            return tmp;
        }
    }
    return NULL;
}


int main()
{
    JRB phonebook, node;
    phonebook = make_jrb();

    jrb_insert_str(phonebook, "Tuan con", new_jval_l(1234567));
    jrb_insert_str(phonebook, "Dat", new_jval_l(88888));
    jrb_insert_str(phonebook, "Tung", new_jval_l(66666));
    jrb_insert_str(phonebook, "Linh bo", new_jval_l(00120012));
    

    node = jrb_find_str(phonebook, "Tuan con");
    printf("%ld\n", jval_l(node->val));

    node = jrb_find_key(phonebook, new_jval_l(88888));
    printf("%s\n", jval_s(node->key));

    jrb_print_db(phonebook);
    jrb_free_tree(phonebook);

}