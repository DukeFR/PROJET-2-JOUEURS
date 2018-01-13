#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
typedef struct score;
struct score
{
    char nom[100];
    int score;
    char nom2[100];
    int score2;
};
void gotoligcol(int lig, int col)
{
// ressources
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
void menu(struct score *score,int *mode)
{
    int i,choix,choix1,nombre[10];
    char pseudo[10];
    char nom[1000];
    do{
    printf("-------------------------------------------\n");
    for(i=0;i<2;i++)
    {
        printf("|                                         |\n");
    }
    printf("|            MENU                         |\n");
    for(i=0;i<2;i++)
    {
        printf("|                                         |\n");
    }
    printf("-------------------------------------------\n\n\n");
    printf("1.MODE ARCADE\n");
    printf("2.AIDE\n");
    printf("3.HIGH SCORE\n");
    printf("4.MODE 2 JOUEURS\n");
    do{
    scanf("%d",&choix);
    }while((choix!=1)&&(choix!=2)&&(choix!=3)&&(choix!=4));

    if(choix==1)
    {
        printf("Saisissez votre pseudo:\n");
        scanf("%s",score->nom);
        system("cls");
        choix1=1;
        *mode=1;
    }
    if(choix==4)
    {
        printf("Saisissez le pseudo du joueur 1:\n");
        scanf("%s",score->nom);
        printf("Saisissez le pseudo du joueur 2:\n");
        scanf("%s",score->nom2);
        system("cls");
        choix1=1;
        *mode=2;
    }
    if(choix==2)
    {
        printf("------------------------------AIDE------------------------------\n\n\n");
        printf("Pour le joueur 1:\n");
        printf("Z: Se deplacer vers le haut\n");
        printf("S: Se deplacer vers le bas\n");
        printf("Q: Se deplacer vers la gauche\n");
        printf("D: Se deplacer vers la droite\n\n");

        printf("Pour le joueur 2:\n");
        printf("I: Se deplacer vers le haut\n");
        printf("K: Se deplacer vers le bas\n");
        printf("J: Se deplacer vers la gauche\n");
        printf("L: Se deplacer vers la droite\n\n");

        printf("Augmentez votre score en attrapant un maximum de O!\n");
        printf("Attention de ne pas attraper les L!\n\n");
        printf("Bonne chance!\n");
        choix1=2;


    }
    if (choix==3)
    {
        FILE*fichier;
        fopen("Score.txt","r");
        if(fichier=!NULL)
        {
            printf("Voici le classement des meilleurs joueurs!\n");
            for(i=0;i<10;i++)
            {
            fscanf(fichier,"%s" "%d",pseudo[i],nombre[i]);
            fprintf("%d. %s:%d\n",i,pseudo[i],nombre[i]);
            }
        }
        fclose(fichier);

    choix1=2;
    }
    }while(choix1!=1);
}
void affichage (struct score score)
{
    int i;
    printf("-------------------------------------------\n");
    for(i=0;i<41;i++)
    {
    printf("|                                         |\n");
    }
    printf("-------------------------------------------\n");
    printf("PSEUDO:%s\n",score.nom);
    printf("SCORE:%d\n",score.score);
}
int main()
{
    int choix;
    struct score score;
    srand(time(NULL));
    score.score=0;
    score.score2=0;
    menu(&score,&choix);
    if(choix==1)
    {affichage(score);
    snake(score);}
    if(choix==2)
    {
        affichage2joueurs(score);
        snake2joueurs(score);
    }

    return 0;
}

void fichier(struct score score)
{
    FILE*fic;
    fopen("Score.txt","");
    if(fic!=NULL)
    {
      fprintf(fic,"%s %d",score.nom,score.nom);
    }
    fclose(fic);

}

void snake(struct score score)
{
    score.score=0;
    int key;
    int x,y,dx,dy,xold,yold,xold1,yold1,a,b,c,d,i,der;
    for(i=0;i<1;i++)
    {
    a=rand()%40+1;
    b=rand()%40+1;
    gotoligcol(a,b);
    printf("O");
    }
    for(i=0;i<1;i++)
    {
    c=rand()%40+1;
    d=rand()%40+1;
    gotoligcol(c,d);
    printf("L");
    }
    x=rand()%40+1;
    y=rand()%40+1;
    dx=1;
    dy=0;
   do{
        xold=x;
        yold=y;
        xold1=xold-dx;
        yold1=yold-dy;
        ///moteur de jeu autonome: deplacement
        x+=dx;
        if(x>40) x=1;
        if(x<1) x=40;
        y+=dy;
        if(y>40) y=1;
        if(y<1) y=40;
        ///affichage
        ///effacer a l'ancienne position
        gotoligcol(yold,xold);
        printf(" ");
        ///afficher a la nouvelle position
        gotoligcol(y,x);
        printf("<");
        if((a==y)&&(b==x))
        {
            score.score=score.score+100;
            system("cls");
            der=score.score/100;
            affichage(score);
            for(i=0;i<1;i++)
            {
            a=rand()%40+1;
            b=rand()%40+1;
            gotoligcol(a,b);
            printf("O");
            }
            gotoligcol(c,d);
            printf("L");
        }
        if((c==y)&&(d==x))
        {
            score.score=score.score-100;
            system("cls");
            der=score.score/100;
            affichage(score);
            for(i=0;i<1;i++)
            {
            c=rand()%40+1;
            d=rand()%40+1;
            gotoligcol(c,d);
            printf("L");
            }
            gotoligcol(a,b);
            printf("O");
        }
        if(score.score>0)
        {
        gotoligcol(y-dy,x-dx);
        printf("x");
        gotoligcol(yold-der*dy,xold-der*dx);///-der*DY
        printf(" ");
        }
        if((dx==xold)&&(dy==yold))
        {
            system("cls");
        }
        Sleep(50);
        ///partie ev.
        if(kbhit()){
                key=getch();
                switch(key){
                    case 'Q' :
                        system("cls");
                        affichage(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf("");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=-1;dy=0;
                               break;
                    case 'D' :
                        system("cls");
                        affichage(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=1;dy=0;
                               break;
                    case 'Z' :
                        system("cls");
                        affichage(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=0;dy=-1;
                               break;
                    case 'S' :
                        system("cls");
                        affichage(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=0;dy=1;
                               break;
                }
        }
   }while(key!='w');
}
void affichage2joueurs (struct score score)
{
    int i;
    printf("-------------------------------------------                       -------------------------------------------\n");
    for(i=0;i<41;i++)
    {
    printf("|                                         |                       |                                         |\n");
    }
    printf("-------------------------------------------                       -------------------------------------------\n\n");
    printf("PSEUDO:%s                                                         PSEUDO:%s\n",score.nom,score.nom2);
    printf("SCORE:%d                                                          SCORE:%d\n",score.score,score.score2);
}

void snake2joueurs(struct score score)
{
    score.score=0;
    score.score2=0;
    int key;
    int key2;
    int x,y,dx,dy,xold,yold,a,b,c,d,i,j,der;
    int x2,y2,dx2,dy2,xold2,yold2,a2,b2,c2,d2;
    for(i=0;i<1;i++)
    {
    a=rand()%40+1;
    b=rand()%40+1;
    gotoligcol(a,b);
    printf("O");
    }
    for(i=0;i<1;i++)
    {
    c=rand()%40+1;
    d=rand()%40+1;
    gotoligcol(c,d);
    printf("L");
    }
    x=rand()%40+1;
    y=rand()%40+1;
    dx=1;
    dy=0;
    for(j=0;j<1;j++)
    {
    a2=rand()%40+1;
    b2=67+rand()%40+1;
    gotoligcol(a2,b2);
    printf("O");
    }
    for(j=0;j<1;j++)
    {
    c2=rand()%40+1;
    d2=67+rand()%40+1;
    gotoligcol(c2,d2);
    printf("L");
    }
    x2=50+rand()%40;
    y2=rand()%40;
    dx2=1;
    dy2=0;
    do{
        xold=x;
        yold=y;
        ///moteur de jeu autonome: deplacement
        x+=dx;
        if(x>40) x=1;
        if(x<1) x=40;
        y+=dy;
        if(y>40) y=1;
        if(y<1) y=40;
        ///affichage
        ///effacer a l'ancienne position
        gotoligcol(yold,xold);
        printf(" ");
        ///afficher a la nouvelle position
        gotoligcol(y,x);
        printf("<");
        if((a==y)&&(b==x))
        {
            score.score=score.score+100;
            system("cls");
            der=score.score/100;
            affichage2joueurs(score);
            for(i=0;i<1;i++)
            {
            a=rand()%40;
            b=rand()%40;
            gotoligcol(a,b);
            printf("O");
            }
            gotoligcol(c,d);
            printf("L");
            gotoligcol(c2,d2);
            printf("L");
            gotoligcol(a2,b2);
            printf("O");
        }
        if((c==y)&&(d==x))
        {
            score.score=score.score-100;
            system("cls");
            der=score.score/100;
            affichage2joueurs(score);
            for(i=0;i<1;i++)
            {
            c=rand()%40;
            d=rand()%40;
            gotoligcol(c,d);
            printf("L");
            }
            gotoligcol(a,b);
            printf("O");
            gotoligcol(c2,d2);
            printf("L");
            gotoligcol(a2,b2);
            printf("O");
        }
        if(score.score>0)
        {
        gotoligcol(y-dy,x-dx);
        printf("x");
        gotoligcol(yold-der*dy,xold-der*dx);///-der*DY
        printf(" ");
        }
        if((dx==xold)&&(dy==yold))
        {
            system("cls");
        }
        xold2=x2;
        yold2=y2;
        ///moteur de jeu autonome: deplacement
        x2+=dx2;
        if(x2>107) x2=67;
        if(x2<67) x2=107;
        y2+=dy2;
        if(y2>40) y2=1;
        if(y2<1) y2=40;
        ///affichage
        ///effacer a l'ancienne position
        gotoligcol(yold2,xold2);
        printf(" ");
        ///afficher a la nouvelle position
        gotoligcol(y2,x2);
        printf("<");

        if((a2==y2)&&(b2==x2))
        {
            score.score2=score.score2+100;
            system("cls");
            der=score.score2/100;
            affichage2joueurs(score);
            for(i=0;i<1;i++)
            {
            a2=rand()%40+1;
            b2=67+rand()%40+1;
            gotoligcol(a2,b2);
            printf("O");
            }
            gotoligcol(c2,d2);
            printf("L");
            gotoligcol(c,d);
            printf("L");
            gotoligcol(a,b);
            printf("O");
        }
        if((c2==y2)&&(d2==x2))
        {
            score.score2=score.score2-100;
            system("cls");
            der=score.score2/100;
            affichage2joueurs(score);
            for(j=0;j<1;j++)
            {
            c2=rand()%40+1;
            d2=67+rand()%40+1;
            gotoligcol(c2,d2);
            printf("L");
            }
            gotoligcol(a2,b2);
            printf("O");
            gotoligcol(c,d);
            printf("L");
            gotoligcol(a,b);
            printf("O");
        }
        if(score.score2>0)
        {
        gotoligcol(y2-dy2,x2-dx2);
        printf("x");
        gotoligcol(yold2-der*dy2,xold2-der*dx2);///-der*DY
        printf(" ");
        }
        if((dx2==xold2)&&(dy2==yold2))
        {
            system("cls");
        }
        Sleep(50);
        ///partie ev.
        if(kbhit()){
                key=getch();
                switch(key){
                    case 'Q' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf("");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=-1;dy=0;
                               break;
                    case 'D' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=1;dy=0;
                               break;
                    case 'Z' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=0;dy=-1;
                               break;
                    case 'S' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        gotoligcol(y,x);
                        dx=0;dy=1;
                               break;
                    case 'J' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf("");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        gotoligcol(y2,x2);
                        dx2=-1;dy2=0;
                               break;
                    case 'L' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der)*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        gotoligcol(y2,x2);
                        dx2=1;dy2=0;
                               break;
                    case 'I' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        gotoligcol(y2,x2);
                        dx2=0;dy2=-1;
                               break;
                    case 'K' :
                        system("cls");
                        affichage2joueurs(score);
                        gotoligcol(a2,b2);
                        printf("O");
                        gotoligcol(c2,d2);
                        printf("L");
                        gotoligcol(a,b);
                        printf("O");
                        gotoligcol(c,d);
                        printf("L");
                        //gotoligcol(y-dy,x-dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der-1)*dx);
                        //printf(" ");
                        //gotoligcol(y-der*dy+1,x-(der+1)*dx);
                        //printf(" ");
                        //gotoligcol(y-(der-1)*dy+1,x-der*dx);
                        //printf(" ");
                        //gotoligcol(y-(der+1)*dy+1,x-der*dx);
                        //printf(" ");
                        gotoligcol(y2,x2);
                        dx2=0;dy2=1;
                               break;
                }
        }
    }while(key!='w');
}
