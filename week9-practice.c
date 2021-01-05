//Nguyen Thanh Trung
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jrb.h"
#include "dllist.h"

int vertexTotal;
int edgeTotal;

#define INFINITIVE_VALUE 10000000

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;


void readFile(Graph g,char* filename);
void printNeighborMatrix(Graph g);
void printfNeighborMatrixVertex(Graph g);
void printDirectWalkingNeighbor(Graph g);
void printMaxIndgreeCastle(Graph g);
Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
double shortestPath(Graph graph, int s, int t, int *path, int *length);
void dropGraph(Graph graph);

int main(){
    Graph g = createGraph();

    //Case 1:
    readFile(g,"graph.txt");

    //printNeighborMatrix(g);

    //Case 2:
    //printfNeighborMatrixVertex(g);
    
    //Case 3a:
    //printDirectWalkingNeighbor(g);

    //Case 3b:
    //printMaxIndgreeCastle(g);

    //Case 4:
    int s, t, path[100], length;
    s = 1;
    t = 99;
    double distance_s_t = shortestPath(g, s, t, path, &length);
    if (distance_s_t != INFINITIVE_VALUE){
        printf("Shortest distance from s --> t: %lf\n", distance_s_t);
        printf("Path: ");
        for (int i=length-1; i>=0; i--){
            printf("%d ", path[i]);
        }
        printf("\n");
    }else{
        printf("No Path from s --> t\n");
    }
}

void readFile(Graph g, char* filename){
    FILE *fp;
    int id1,id2,time;
    int i;

    if((fp = fopen(filename, "r")) == NULL){
        printf("Can't read from %s\n", filename);
    }else{
        fscanf(fp,"%d",&vertexTotal);
        fscanf(fp,"%d",&edgeTotal);
        for(i = 0; i < edgeTotal; i++){
            fscanf(fp,"%d",&id1);
            fscanf(fp,"%d",&id2);
            fscanf(fp,"%d",&time);

            // printf("%d - ",id1);
            // printf("%d - ",id2);
            // printf("%d\n",time);
            
            addVertex(g,id1,"V");
            addVertex(g,id2,"V");

            addEdge(g,id1,id2,(double)time);
            addEdge(g,id2,id1,(double)time);
        }
    }

    fclose(fp);
}

void printNeighborMatrix(Graph g){
    int i,j;
    for(i = 1; i<= vertexTotal;i++){
        for(j = 1;j<= vertexTotal;j++){
            int v = getEdgeValue(g,i,j);
            if(v == INFINITIVE_VALUE){
                printf("0\t");
            }else{
                printf("%d\t",v);
            }
            if(j == vertexTotal){
                printf("\n");
            }
        }
    }
};

JRB jvalToJRB(Jval v){
    return (JRB)v.v;
}

void printfNeighborMatrixVertex(Graph g){
    JRB tmp;
    JRB tmp2;
    jrb_traverse(tmp,g.edges){
        printf("- Castle %d: ",tmp->key);
        jrb_traverse(tmp2,jvalToJRB(tmp->val)){
            printf("%d ",tmp2->key);
        }
        printf("\n");
    };
};

void printDirectWalkingNeighbor(Graph g){
    int boolean; //IF boolean = 1 => can go by horse directly, boolean = 0 => return
    JRB tmp;
    JRB tmp2;
    printf("The castle list go to by walking directly only:");
    jrb_traverse(tmp,g.edges){
        boolean = 0;
        //printf("- Castle %d: ",tmp->key);
        jrb_traverse(tmp2,jvalToJRB(tmp->val)){
            //printf("%d - ",(tmp2->val).d);
            if((tmp2->val).d < 50){
                boolean = 1;
            }
        }
        if(boolean == 0){
            printf("%d ",tmp->key);
        }
        //printf("\n");
    };
    printf("\n");

};

void printMaxIndgreeCastle(Graph g){
    int max = 0;
    int list[vertexTotal];
    int count = 0;
    int output[100];
    int n,i;
    JRB tmp;
    JRB tmp2;
    printf("The castle list has maximum indegree:");
    jrb_traverse(tmp,g.edges){
        n = indegree(g,(tmp->key).i,output);
        if(n > max){
            count = 0;
            max = n;
            list[count] = (tmp->key).i;
        }else if(n == max){
            count++;
            list[count] = (tmp->key).i;
        }
    };

    for(i = 0; i < vertexTotal; i++){
        if(list[i] > 0){
            printf("%d ",list[i]);
        }
    }
    printf("\n");
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
    if (node==NULL) // only add new vertex
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL)
        return NULL;
    else
        return (jval_s(node->val));
}

// Make connection between v1 and v2
void addEdge(Graph graph, int v1, int v2,double weight){
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

double getEdgeValue(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
        return INFINITIVE_VALUE;
    }
    JRB tree = (JRB)jval_v(node->val);
    JRB node1 = jrb_find_int(tree, v2);
    if (node1 == NULL) {
        return INFINITIVE_VALUE;
    }
    return jval_d(node1->val);
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
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node==NULL)
        return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree){
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

double shortestPath(Graph graph, int s, int t, int *path, int *length){
    // Khoi tao cac distance = 0
    double distance[1000], min;
    int previous[1000], u, visit[1000];
    
    for (int i=0; i<1000; i++){
        distance[i] = INFINITIVE_VALUE;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visit[s] = 1;
    
    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));
    
    // Duyet Queue
    while (!dll_empty(queue)){
        min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue){
            // Lay ra min{distance}
            u = jval_i(ptr->val);
            if (min > distance[u]){
                min = distance[u];
                node = ptr;
            }
        }
        
        u = jval_i(node->val);
        //printf("%d ", u);
        dll_delete_node(node);
        int output[100];
        int size = outdegree(graph,u,output);
        for(int i = 0; i < size; i++)
        {
            if(visit[output[i]] == 0)
            {
                visit[output[i]] = 1;
                dll_append(queue, new_jval_i(output[i]));
            }
            if((getEdgeValue(graph, u, output[i]) + distance[u])
               < distance[output[i]])
            {
                distance[output[i]] = distance[u] +
                getEdgeValue(graph, u , output[i]);
                previous[output[i]] = u;
            }
        }
    }
    int current = t;
    int ln = 0;
    path[0] = t;
    while(current!=s)
    {
        ln++;
        current = previous[current];
        path[ln] = current;
    }
    *length = ln;
    return distance[t];
}
