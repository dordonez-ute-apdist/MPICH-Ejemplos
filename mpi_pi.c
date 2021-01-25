#include <stdlib.h>
#include <stdio.h>
#include <time.h> //para time()
#include <unistd.h> //para gethostname()
#include <mpi.h>

int main(int argc, char *argv[]) {
   int niter=10000000; /* # de puntos a calcular por CADA proceso */
   int master=0;
   int myid,numprocs;
   int tag=123;
   MPI_Status status;
   char hostname[256];
   
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);
   
   /* Obtenemos nombres de nodos */
   gethostname(hostname, 256);
   if(myid == master)
     printf("El máster es el nodo: %s\n",hostname);   
   
   /* cálculo que hacen todos los procesos */
   srand((unsigned int)time(NULL)+myid);
   int mycount=0;
   for(int i=0; i<niter; i++) {
      double x = (double)rand() / RAND_MAX; /* aleatorio entre 0 y 1 */
      double y = (double)rand() / RAND_MAX;
      double z = x*x + y*y;
      if(z<=1) mycount++; 
   }
   printf("Proceso %d en nodo %s contó: %d\n",myid,hostname,mycount);
   
   if(myid == master) { /* el master recupera lo calculado por los demás */ 
      int totalcount = mycount;
      int yourcount;
      for(int proc=1; proc<numprocs; proc++) {
         MPI_Recv(&yourcount,1,MPI_INT,proc,tag,MPI_COMM_WORLD,&status);
         totalcount += yourcount;        
      }
      double pi=(double)totalcount/(niter*numprocs)*4;
      printf("Total puntos calculados = %d; ", niter*numprocs);
      printf("PI estimado = %.15f \n", pi);
   } else { /* el esclavo envía su cálculo al master */
      MPI_Send(&mycount,1,MPI_INT,master,tag,MPI_COMM_WORLD);
   }
   
   MPI_Finalize();
   return 0;
}
