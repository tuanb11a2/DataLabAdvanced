// Name:
// Phan Huy Thang
//Nguyen Manh Tien
// Bui Thanh Tung
#define INFINITIVE_VALUE 100000000
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

// Make connection between v1 and v2: v1 --> v2 with weight of edges
void addEdge(Graph graph, int v1, int v2,int weight){
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
        jrb_insert_int(tree, v2, new_jval_i(weight));
    }
    //add v2 into, but not add connection v2->v1
    JRB node2 = jrb_find_int(graph.edges, v2);
    if(node2 == NULL){
        jrb_insert_int(graph.edges,v2,tree2);
    }
}

// v1 --> v2?
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

JRB findEdges(Graph graph,int v1,int v2){
    JRB node,tree,value;
    node = jrb_find_int(graph.edges,v1);
    if(node == NULL){
        return NULL;
    }else{
        tree = jrb_find_int(node->val,v2);
        if(tree == NULL){
            return NULL;
        }else{
            return tree;
        }
    }
}

void setEdgeValue(Graph graph,int v1,int v2){
    JRB node,tree,value;
    node = jrb_find_int(graph.edges,v1);
    if(node == NULL){
        return 0;
    }else{
        tree = jrb_find_int(node->val,v2);
        if(tree == NULL){
            return 0;
        }else{
            return tree->val;
        }
    }
}

int getEdgeValue(Graph graph,int v1,int v2){
    JRB node,tree,value;
    node = jrb_find_int(graph.edges,v1);
    if(node == NULL){
        return 0;
    }else{
        tree = jrb_find_int(node->val,v2);
        if(tree == NULL){
            return 0;
        }else{
            return tree->val;
        }
    }
}

int countGraph(Graph graph){
    JRB tmp;
    int count;
    jrb_traverse(tmp,graph.vertices){
        count++;
    }
    return count;
}

//Dijkstra's Algorithms
int shortestPath(Graph graph, int s,int t,int* path,int* length){
    int count = countGraph(graph);
    Dllist queue = new_dllist();
    int index = 0;
    JRB tmp,tmp2;
    JRB distance[100];
    distance[s]->key = new_jval_i(s);
    distance[s]->val = new_jval_i(0);
    queue = dll_append(queue,new_jval_i(s));
    while(tmp != jrb_find_int(graph.edges,t)){
        s = jval_i(queue->val);
        queue = queue->flink;
        tmp = jrb_find_int(graph.edges,s);
        jrb_traverse(tmp2,tmp->val){
            if(distance[s]->val + getEdgeValue(graph,s,jval_i(tmp->val)) < )
            distance[jval_i(tmp2->val)]->key = new_jval_i(jval_i(tmp2->val));
             jval_i
        }
    }


}
