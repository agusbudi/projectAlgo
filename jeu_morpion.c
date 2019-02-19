#include <stdio.h>
#include <stdbool.h>
#define Nmax 100

typedef int morpion[Nmax][Nmax];

typedef struct{
    int x;
    int y;
} Coordonees;

void initBoard(morpion m, int N){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            m[i][j]= -1;
}

void affichage(morpion m, int N){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            char x = ' ';
            if(m[i][j]==0)  x= 'O';
            else if(m[i][j]==1)  x= 'X';
            
            printf("[%c]", x);
        }
        printf("\n");
    }
}


int impossible(morpion m, int N){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++){
            if(m[i][j]== -1)
                return 0;
        }

    return 1;
}


bool checkTie(morpion board, int N)
{ 
    int i,j, available=0;
    for (i= 0; i < N; i++) {
        for (j= 0; j < N; j++) {
            if(board[i][j]==-1)
                return false;
        }
    }
    //if(available==0)
    return true;
 }


int jouer(morpion m, int i, int j, int joueur){
    if(m[i][j]==-1){
        m[i][j]= joueur;
        return 0;
    }
    return 1;
}

int gagnant(morpion m, int joueur, int N){
    int i, j, statut;

    //horizontal
    for(i=0;i<N;i++){
        statut=1;
        for(j=0;(j<N) && (statut ==1);j++){
            if(m[i][j]!=joueur)
                statut=0;
        }
        if(statut==1)
            return 1;
    }

    //vertical
    for(i=0;i<N;i++){
        statut=1;
        for(j=0;(j<N) && (statut ==1);j++){
            if(m[j][i]!=joueur)
                statut=0;
        }
        if(statut==1)
            return 1;
    }

    //diagonal
    statut=1;
    for(i=0;i<N;i++){
        if(m[i][i]!=joueur)
            statut=0;
    }
    if(statut==1)
        return 1;

    statut=1;
    for(i=0;i<N;i++){
        if(m[N-1-i][i]!=joueur)
            statut=0;
    }
    if(statut==1)
        return 1;

    return 0;
}


int Min(morpion m, int N);

int Max(morpion m, int N){
    if(gagnant(m, 0, N))    return 10;
    else if(gagnant(m, 1, N))    return -10;
    else if(impossible(m, N)==1)    
        return 0;

    int Score = -100;
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(m[i][j]==-1){
                m[i][j] = 0;
                int valeur = Min(m, N);
                if( Score < valeur)     Score = valeur;
                m[i][j] = -1;
            }
        }        
    }
    return Score;
}

int Min(morpion m, int N){
    if (gagnant(m, 0, N)) { return 10; }
    else if (gagnant(m, 1, N)) { return -10; }
    else if (impossible(m, N)==1) 
        { return 0; }

    int Score = 100;
    int i,j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        { 
            if(m[i][j]==-1){
                m[i][j] = 1;
                int valeur = Max(m, N);
                if( Score > valeur)     Score = valeur;
                m[i][j] = -1;
            }
        }
    }

    return Score;
}

Coordonees MinMax(morpion m, int N){
    int Score = 100;
    Coordonees coo;
    coo.x=0;
    coo.y=0;
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(m[i][j]==-1){
                m[i][j] = 1; 
                int valeur = Max(m, N);

                printf("\n");
                affichage(m,N);
                printf("score: %d\n", valeur);
                if( valeur < Score ){
                    Score = valeur;
                    coo.x=i;
                    coo.y=j;
                }
                m[i][j] = -1;                
            }
        }        
    }

    return coo;
}

int main()
{
    int N;
    scanf("%d", &N);
    morpion m;
    initBoard(m,N);
    affichage(m, N);
    int i=0, j=N*N;
    int l=j-(N-1)*2;

    do{
        int joueur = i%2;
        int x,y;
        if(joueur==0){
            do{
                printf("Player %d \n\tx: ", joueur);
                scanf("%d",&x);
                printf("\ty: ");
                scanf("%d",&y);
            }while(jouer(m,x,y, joueur));            
        }
        else{
            printf("\nComputer Move: ");
            Coordonees coo = MinMax(m, N);
            printf("\n\trow:%d\tcol:%d\n", coo.x, coo.y);
            m[coo.x][coo.y] = joueur;
        }

        
        int k = gagnant(m, joueur, N);
        if(k==1){
            printf("\nPlayer %d win!!!\n", joueur);  
            i=j+5;          
        } else if(k==-1){
            printf("\nimpossible!!!\n");  
            i=j+5;          
        }

        affichage(m, N);
        i++;
    }while(i<=j);

    return 0;
}