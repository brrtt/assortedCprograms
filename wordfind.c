/*
 * J Barrett Chesebrough
 * Wordfind. The program solves wordsearches through files and sorting them into 2d arrays. It can open the puzzle and the word list, and then compares them in arrays. Then produces a new a file containing the solutions.
 * ECE 209 
*Note all coordinates are off by one, didnt have time to fix
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *puzzle;
FILE *solns;
FILE *words; 
FILE *fp;

char parray[50][50];
char warray[50][50];
char sarray[100][100];
int main(){
    int i=0;
    int j=0;
    int b;
    int c=0;
    char name[20];
    char namec[30];
    char nameb[30];
    printf("Enter file name \n");
    while(i!=1){
        scanf("%s",name);/*tests character names using strlen function*/
        if(strlen(name)>12){
            printf("please use name shorter than 12 characters\n");
        }
        if(strlen(name)<=12){
            printf("accepted\n");
            i=1;
        }
    }
    char ext1[4]=".txt";
    char ext2[11]="_words.txt";
    char ext3[10]="_soln.txt";
    strcpy(namec,name);
    strcpy(nameb,name);
    strcat(name, ext1);
    printf("%s\n",name);
    puzzle=fopen(name, "r"); /*puzzle opens and reads*/
    fscanf(puzzle,"%d",&b); 
    printf("%d\n",b); /*test item */
    
    for(i=0; i<b; i++){
        for (j=0; j<b; j++){
            fscanf(puzzle,"%1s",&parray[i][j]);
            }
        }
    fclose(puzzle);
     for(i=0; i<b; i++){
        for (j=0; j<b; j++){
            printf("%c ", parray[i][j]);
            if(j==b-1){
                printf("\n");
            }
        }
     }
   strcat(namec,ext2);
    printf("%s\n",namec);
    words=fopen(namec,"r");/*word list opens and reads*/
    i=0;
    while(fscanf(words,"%s",warray[i]) != EOF){
        i++;
    }
    fclose(words);
    strcat(nameb,ext3);
    printf("%s\n",nameb);
    solns=fopen(nameb,"a");/*as words are found their just appended to the solution file*/
    int k=0;			/*much easier solution than storing them to an array*/
    int m=0;
    int z=0;
    for(i=0;i<b;i++){
        for(j=0;j<b;j++){
            for(k=0;k<=c;k++)
            while(z!=1){
                if(parray[i+k][j]==warray[k][m]){
                    m++;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) S",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                }
            }
            z=0;
            k=0;
            m=0;
            while(z!=1){
                if(parray[i-k][j]==warray[k][m]){
                    m++;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) N",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
            }
            z=0;
            k=0;
            m=0;
             while(z!=1){
                if(parray[i][j+k]==warray[k][m]){
                    m++;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) E",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
             }
            z=0;
            k=0;
            m=0;
             while(z!=1){
                if(parray[i][j-k]==warray[k][m]){
                    m++;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) W",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
             }
            z=0;
            k=0;
            m=0;
             while(z!=1){
                if(parray[i+k][j+k]==warray[k][m]){
                    m++;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) SE",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
             }
            z=0;
            k=0;
            m=0;
             while(z!=1){
                if(parray[i+k][j-k]==warray[k][m]){
                    m++;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) SW",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
             }
            z=0;
            k=0;
            m=0;
             while(z!=1){
                if(parray[i-k][j-k]==warray[k][m]){
                    ++m;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) NW",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
             }
            z=0;
            k=0;
            m=0;
             while(z!=1){
                if(parray[i-k][j+k]==warray[k][m]){
                    ++m;
                    if(k==strlen(warray[i])){
                        solns=fprintf("%s (%d,%d) NE",warray[k],&i,&j);
                        z=1;
                        c-=1;
                    }
                    z=1;
                }
             }
        }
    }
    
    fclose(solns);
  

    
   
}