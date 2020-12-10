// Name:
// Phan Huy Thang
//Nguyen Manh Tien
// Bui Thanh Tung

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jrb.h"
#include "dllist.h"

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int DAG(Graph graph);
void dropGraph(Graph graph);

int main(){
    Graph g = createGraph();
    addVertex(g, 0, "Node 0");
    addVertex(g, 1, "Node 1");
    addVertex(g, 2, "Node 2");
    addVertex(g, 3, "Node 3");
    addVertex(g, 4, "Node 4");
    addVertex(g, 5, "Node 5");
    
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    
    int output[10];
    int n = outdegree(g, 2, output);
    printf("Outdegree: ");
    for (int i=0; i < n; i++){
        printf("%d ", output[i]);
    }
    printf("\n");
    
    int check = DAG(g);
    if (check == 0){
        printf("Not DAG\n");
    }else{
        printf("It is DAG\n");
    }
    
    dropGraph(g);
}

Graph createGraph(){
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void dropGraph(Graph graph){
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

void addVertex(Graph graph, int id, char* name){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL)
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
    else
        strcpy(jval_s(node->val), name);
}

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL)
        return NULL;
    else
        return (jval_s(node->val));
}

// Make connection between v1 and v2: v1 --> v2
void addEdge(Graph graph, int v1, int v2){
    JRB node, tree;
    JRB tree2 = make_jrb();
    if (!hasEdge(graph, v1, v2)){
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else{
            tree = (JRB) jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    
    //add v2 into, but not add connection v2->v1
    JRB node2 = jrb_find_int(graph.edges, v2);
    if(node2 == NULL){
        jrb_insert_int(graph.edges,v2,tree2);
    }
}

// v1 is connected to v2?
int hasEdge(Graph graph, int v1, int v2){
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
        return 0;
    tree = (JRB) jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
        return 0;
    else
        return 1;
}

int indegree(Graph graph, int v, int* output){
    int total = 0;
    JRB node;
    jrb_traverse(node,graph.edges) {
        JRB tree = (JRB) jval_v(node->val);
        if (jrb_find_int(tree,v) != NULL) {
            output[total++] = jval_i(node->key);
        }
    }
    return total;
}

int outdegree(Graph graph, int v, int* output){
    int total =0;
    JRB node = jrb_find_int(graph.edges,v);
    if (node != NULL) {
        JRB tree = (JRB) jval_v(node->val);
        if (tree == NULL) {
            return 0;
        }
        JRB tmp;
        jrb_traverse(tmp,tree) {
            output[total++] = jval_i(tmp->key);
        }
    }
    return total;
}
int maxKey(Graph graph){
    int max = 0;
    JRB temp;
    jrb_traverse(temp,graph.vertices){
        if(jval_i(temp->key) > = max){
            max = jval_i(temp->key)
        }
    }
    return max;
}

int DAG(Graph graph){
    int result = 0;
    int sizeVisitedArray = maxKey +1;
    int *visittedArray = (int*)malloc(sizeVisitedArray*sizeof(int));
    for(int i=0;i<sizeVisitedArray;i++){
        visittedArray[i] = 0;
    }
    
    Dllist stack = new_dllist();
    dll_append(stack,graph.vertices->val);
    visittedArray[jval_i(graph.vertices->key)] = 1;
    
    while (! dll_isEmpty(stack)) {
        int check = 0;
        JRB tmp;
        JRB node = jrb_find_int(graph.vertices,dll_last(stack)->value);
        JRB tree = (JRB)jval_v(node->val);
        
        jrb_traverse(tmp,tree){
            if(visittedArray[jval_i(tmp->key)] == 0){
                dll_append(stack,tmp->key);
                visittedArray[jval_i(tmp->key)] == 1;
                check++;
            }else{
                result = 1;
            }
        }
        if(check == 0){
            dll_delete(dll_last(stack));
        }
    }
    return result;
}
