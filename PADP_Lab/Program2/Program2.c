#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	int **a,**b,**c;
	int n=atoi(argv[1]),i,j,k;
	//int t=atoi(argv[2]);
//	printf("Enter dimensions of A: "); scanf("%d%d",&m,&n);
//	printf("Enter dimensions of B: "); scanf("%d%d",&p,&q);
//	if(n!=p){
//		printf("Incompatible");
//		return 0;
//	}
	a=(int**)malloc(n* sizeof (int*));
	for(i=0; i<n; i++){
		a[i] = (int*) malloc(n * sizeof (int));
	}
	b=(int**)malloc(n* sizeof (int*));
	for(i=0; i<n; i++){
		b[i] = (int*) malloc(n * sizeof (int));
	}
	c=(int**)malloc(n* sizeof (int*));
	for(i=0; i<n; i++){
		c[i] = (int*) malloc(n * sizeof (int));
	}
	// printf("Enter elements of A\n");
	omp_set_num_threads(16);
	#pragma openmp parallel for
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			a[i][j] = rand()%n;
	// printf("Enter elements of B\n");
	omp_set_num_threads(16);
	#pragma openmp parallel for
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			b[i][j] = rand()%n;

	for(int t=8; t>=1; t/=2){
		//int t=1;
		double x = omp_get_wtime();
		omp_set_num_threads(t);
		#pragma openmp parallel for private(j,k)
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				c[i][j]=0;
				for(k=0; k<n; k++)
					c[i][j] += a[i][k]*b[k][j];
			}
		}
		double y = omp_get_wtime();
		printf("Time for matrix %d* %d with %d threads: %lf\n",n,n,t, y-x);
	}
	
	return 0;
}
