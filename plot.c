#include <stdio.h>
#include <omp.h>

/* Function to plot the 2D array
 * 'gnuplot' is instantiated via a pipe and 
 * the values to be plotted are passed through, along 
 * with gnuplot commands */

FILE *gnu=NULL;

int MeshPlot(int t, int m, int n, char **mesh)
{
	int i,j;
	char iter[60];
	sprintf (iter, "\"Iter = %d\"", t );

	if(gnu==NULL) 
	  gnu = popen("gnuplot","w");
	
	fprintf(gnu,"set title %s\n",iter);
	fprintf(gnu,"set size square\n");
	fprintf(gnu,"set key off\n");
	fprintf(gnu,"plot [0:%d] [0:%d] \"-\"\n",m-1,n-1);
    
#pragma omp parallel for schedule(static) private( i,j) firstprivate(mesh, gnu,m, n)
	for(i=1;i<m-1;i++) {
	    for(j=1;j<n-1;j++)
	        if (mesh[i][j]) {
		   fprintf(gnu,"%d %d\n",j,n-i-1);
              // int thread_count = omp_get_num_threads();
            //    printf("num threads  : %d ", thread_count);
		}
	}
			
	fprintf(gnu,"e\n");
	fflush(gnu);

	return(0);
}
