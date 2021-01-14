#include<stdio.h>
#include<stdlib.h>

void main(){
    int min;
    int budget;
    int count = -1;
    int cost = 0;
    printf("Enter min value:");
    scanf("%d",&min);
    fflush(stdin);
    printf("Enter budget:");
    scanf("%d",&budget);

    while (cost<budget)
    {
        cost = cost + min;
        min = min*2;
        count++;
    }
    cost = cost -(min/2);

    printf("\tRESULT\t\n");
    printf("Cost:%d\n",cost);
    printf("Count:%d\n",count);
    printf("Max:%d\n",min/4);
    printf("Remain:%d\n",budget-cost);
    
}

