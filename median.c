#include <stdio.h>

int i;
int j;
for (i=0; i<n; i++) 
{ 
	int small=i; 
	for (j=i+1; j<n; j++) 
	{ 
		if (x[j]<x[small]) 
		small=j; 

	} 
	int s=x[small]; 
	x[small]=x[i]; 
	x[i]=s; 
} 
if ((n&1)==0) 
	m=(x[n/2-1]+x[n/2])/2; 
else 
	m=x[n/2];
