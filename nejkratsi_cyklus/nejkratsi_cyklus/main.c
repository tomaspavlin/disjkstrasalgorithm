//nejkratsi cyklus
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
int s, s2;


void vstup(void);
void vystup(void);
void vystup_pisCestuK(int,int);
int removeEdge(int,int);
void dijstra(void);


int removeEdge(int v1, int v2){//vrátí 1, pokud hranu našel
    for(int i = 0; i < pocet_hran; i++){
        if((edges[i].v1 == v1 && edges[i].v2 == v2) || (edges[i].v1 == v2 && edges[i].v2 == v1)){
            edges[i].removed = 1;
            return 1;
        }
    }
    return 0;
}

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
    
    scanf("%i %i",&s,&s2);
}

void vystup_pisCestuK(int i, int first){
    if(i == -1)return;
    vystup_pisCestuK(vertex[i].parent,0);
    if(first) printf("%i",i);
    else printf("%i-",i);

}
void vystup(){
    
        if(vertex[s2].vzdalenost < INT_MAX){
            printf("Nejkratsí cyklus obsahujici hranu (%i,%i) je ",s,s2);
            vystup_pisCestuK(s2,1);
            printf(". Jeho delka je %i.",vertex[s2].vzdalenost);
        } else printf("Zadana hrana neni na zadnem cyklu.");
        
        printf("\n");
    
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
            
            if(vertex[ii].vzdalenost + edges[i].m < vertex[sousedI].vzdalenost){
                vertex[sousedI].vzdalenost = vertex[ii].vzdalenost + edges[i].m;// 2/2
                vertex[sousedI].parent = ii;
                vertex[sousedI].delkaVHranach = vertex[ii].delkaVHranach + 1;
                vertex[sousedI].jednoznacnost = 1;
            }
            
        }
    }

}

int main (int argc, const char * argv[]){
    vstup();
    removeEdge(s,s2);
    dijstra();
    vystup();
    
    return 0;
}

