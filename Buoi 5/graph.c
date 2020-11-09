#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

typedef struct {
    int* matrix; 
    int sizemax;
}Graph;

Graph createGraph(int sizemax){
    Graph new;
    int i,j;
    new.sizemax = sizemax;
    new.matrix = malloc(sizeof(int)*sizemax*sizemax);
    for(i = 0;i<sizemax;i++){
        for(j = 0;j<sizemax;j++){
            new.matrix[i][j] = 0;
        }
    }
    return new;
}

void addEdge(Graph graph,int v1,int v2){
    if(v1 >= 0 && v2>= 0 && v1<graph.sizemax & v2<graph.sizemax){
        graph.matrix[v1][v2] = 1;
        graph.matrix[v2][v1] = 1;
    }else{
        printf("Error input!");
        exit(-1);
    }
}

int adjacent(Graph graph,int v1,int v2){
    if(v1 >= 0 && v2>= 0 && v1<graph.sizemax & v2<graph.sizemax){
        if(graph.matrix[v1][v2] == 1 && graph.matrix[v2][v1] == 1){
            return 1;
        }else{
            return 0;
        }
    }else{
        printf("Error input!");
        exit(-1);
    }
}

int getAdjacentVertices(Graph graph,int vertex,int* output){
    int i,j,num;
    for(i = 0;i < graph.sizemax; i++){
        for(j = 0;j < graph.sizemax; j++){
            if(i == vertex){
                
            }
            if(graph.matrix[i][j] == 1){
                output[num++] = j;
            }
        }
    }
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