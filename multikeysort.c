#include <stdio.h>
#include <stdlib.h>

struct song {
  char title[100];
  char album[100];
  char artist[100];
  int year;
  int playlist;
};

typedef struct song item;



void swap(struct song* a,struct song* b)
{
  struct song tmp= *a;
  *a=*b;
  *b=tmp;
}

int partition(struct song array[],int low,int high,int filter)
{
  struct song pivot=array[high];
  int i=(low-1);
  int j;
 if(filter==0)//sort by artist
    {
      for(j=low;j<=high-1;j++)
       {
	 if(strcmp(array[j].artist,pivot.artist)<1)
	   {
	     i++;
	     swap(&array[i],&array[j]);
	   }
       }
    }
 else if(filter==1)//sort by album
    {
       for(j=low;j<=high-1;j++)
	 {
	   if(strcmp(array[j].album,pivot.album)<1)
	     {
	       i++;
	       swap(&array[i],&array[j]);
	     }
	 }
    }
 else  if(filter==2)//sort by year
    {
       for(j=low;j<=high-1;j++)
	 {
	   if(strcmp(array[j].year,pivot.year)<1)
	     {
	       i++;
	       swap(&array[i],&array[j]);
	     }
	 }
    }
  swap(&array[i+1],&array[high]);
  return (i+1);
}

void quicksort(struct song array[],int low, int high,int filter)
{
  int pi;
  if (low<high)
    {
       pi=partition(array,low,high,filter);
    }
  quicksort(array,low,pi-1,filter);
  quicksort(array,pi+1,high,filter);
}


void sort(item a[],int size, int key)
{
  int high=size-1;
  int low=0;
  quicksort(a,low,high,key);
}

