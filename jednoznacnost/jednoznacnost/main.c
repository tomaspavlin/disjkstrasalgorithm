//jednoznacnost
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct edge{
    int v1;
    int v2;
    int m;
    int removed;//pokud 1, hrana jako by nebyla
};

struct vertex{
    int vzdalenost;//sem uklada dijkstra vypočítanou vzdálenost
    int urceno;//pro dijstra.. určuje, zda už je vzdálenost definitivní
    int parent;
    int delkaVHranach;
    int jednoznacnost;
};

int pocet_vrcholu;
int pocet_hran;
struct edge* edges;
struct vertex* vertex;
int s;

void vstup(void);
void vystup(void);
void vystup_pisCestuK(int,int);
void dijstra(void);


void vstup(){
    scanf("%i",&pocet_vrcholu);
    scanf("%i",&pocet_hran);
    edges = malloc(sizeof(struct edge)*pocet_hran);
    vertex = malloc(sizeof(struct vertex)*pocet_vrcholu);
    
    for(int i = 0; i < pocet_hran; i++){
        scanf("%i",&edges[i].v1);
        scanf("%i",&edges[i].v2);
        scanf("%i",&edges[i].m);
    }
    
    scanf("%i",&s);
}

void vystup(){
    for(int i = 0; i < pocet_vrcholu; i++){
        printf("%i: ",i);
        //if(vertex[i].vzdalenost < INT_MAX)
        if(vertex[i].jednoznacnost <= 1){
            printf("1");
        } else printf("0");
        
        printf("\n");
    }
}

void dijstra(){
    //původní nastavení hran
    for(int i = 0; i < pocet_vrcholu; i++){
        vertex[i].vzdalenost = INT_MAX;
        vertex[i].urceno = 0;
        vertex[i].parent = -1;
        vertex[i].delkaVHranach = INT_MAX;
        vertex[i].jednoznacnost = 0;
    }
    
    vertex[s].vzdalenost = 0;
    vertex[s].parent = -1;
    vertex[s].delkaVHranach = 0;
    
    //algorithm
    while(1){
        //najde nejbližší vrchol z neurčených
        int minVzdalenost = INT_MAX;
        int ii = -1;
        for(int i = 0; i < pocet_vrcholu; i++){
            if(vertex[i].urceno == 1)continue;
            if(vertex[i].vzdalenost < minVzdalenost){
                minVzdalenost = vertex[i].vzdalenost;
                ii = i;
            }
        }
        if(ii == -1)break;
        
        //tento vrchol přesune do určených
        vertex[ii].urceno = 1;
        //..a zkusí vylepšit cestu k jeho sousedům
        for(int i = 0; i < pocet_hran; i++){
            if(edges[i].removed)continue;
            int sousedI;
            if(edges[i].v1 == ii)sousedI = edges[i].v2;
            else if(edges[i].v2 == ii)sousedI = edges[i].v1;
            else continue;
            
            if(vertex[ii].vzdalenost + edges[i].m == vertex[sousedI].vzdalenost){
                vertex[sousedI].jednoznacnost++;                
            }
            if(vertex[ii].vzdalenost + edges[i].m < vertex[sousedI].vzdalenost){
                vertex[sousedI].vzdalenost = vertex[ii].vzdalenost + edges[i].m;
                vertex[sousedI].parent = ii;
                vertex[sousedI].jednoznacnost = 1;
            }
        }
    }
}

int main (int argc, const char * argv[]){
    vstup();
    dijstra();
    vystup();
    return 0;
}

