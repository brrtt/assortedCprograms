//utilitizes insert sort correctly. 
void combine_sort(int* a, int* b, int *c,int M, int N)
{
	int i;
	int j;
	int tmp=0;
	for(i=0;i<M;i++)
	{
	  *(c+i)=*(a+i);
	}
	for(i=0;i<N;i++)
	{
	  *(c+N+i)=*(b+N-1-i);
	}
	for(i=1;i<M+N;i++)
        {
	  tmp=*(c+i);
	  j=i-1;
	  while(j>=0 && *(c+j)<tmp)
	    {
	      *(c+j+1)=*(c+j);
	      j=j-1;
	    }
	 *(c+j+1)=tmp;
	}
}
	  
	  
	  
	    
		
		
