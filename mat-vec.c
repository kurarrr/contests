#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <mpi.h>

#define  N    100000
#define  N2   (N+288-1)/288
#define  DEBUG  0
#define  EPS    1.0e-18

/* Please define the matrices in HERE. */
static double  A[N2][N];
static double  x[N], y[N];

int     myid, numprocs;

void MyMatVec(double y[N], double A[N2][N], double x[N], int n);

int main(int argc, char* argv[]) {

     double  t0, t1, t2, t_w;
     double  dc_inv, d_mflops;

     int     ierr;
     int     i, j;
     int     iflag, iflag_t;
     const int n2 = N2;

     ierr = MPI_Init(&argc, &argv);
     ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);
     ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

     /* matrix generation --------------------------*/
     if (DEBUG == 1) {
       for(i=0; i<N; i++) {
         x[i] = 1.0;
       }

       for(j=0; j<n2; j++) {
         for(i=0; i<N; i++) {
           A[j][i] = 1.0;
         }
       }
     } else {
       srand(1);
       dc_inv = 1.0/(double)RAND_MAX;
     for(i=0; i<N; i++) {
         x[i] = rand()*dc_inv;
       }
       for(j=0; j<n2; j++) {
         for(i=0; i<N; i++) {
           A[j][i] = rand()*dc_inv;
         }
       }
     } /* end of matrix generation --------------------------*/

     /* Start of mat-vec routine ----------------------------*/
     ierr = MPI_Barrier(MPI_COMM_WORLD);
     t1 = MPI_Wtime();

     MyMatVec(y, A, x, N);

     ierr = MPI_Barrier(MPI_COMM_WORLD);
     t2 = MPI_Wtime();
     t0 =  t2 - t1;
     ierr = MPI_Reduce(&t0, &t_w, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
     /* End of mat-vec routine --------------------------- */

     if (myid == 0) {
       printf("N = %d\n",N);
       printf("Mat-Vec time  = %lf [sec.] \n",t_w);

       d_mflops = 2.0*(double)N*(double)N/t_w;
       d_mflops = d_mflops * 1.0e-6;
       printf(" %lf [MFLOPS] \n", d_mflops);
     }

     if (DEBUG == 1) {
       iflag_t = 0;
       int istart,iend;
       istart = myid * n2;
       if((myid+1)*n2<N) iend = (myid+1)*n2;
       else iend = N;

       for(i=istart; i<iend; i++) {
         if (fabs(y[i] - (double)N) > EPS) {
           printf(" Error! in %d th argument in PE %d y[i] =  %d\n",i, myid,y[i]);
           iflag_t = 1;
           break;
         }
       }
       ierr = MPI_Reduce(&iflag_t, &iflag, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
              if (iflag == 0) {
         if (myid == 0) printf("OK! \n");
       }
     }

     ierr = MPI_Finalize();

     exit(0);
}
void MyMatVec(double y[N], double A[N2][N], double x[N], int n)
{
     int  i, j, ystart ,jend,n2;
     n2 = N2;

     if((myid+1)*n2<N) jend = n2;
     else jend = N - myid*n2;
     if(jend<0) jend = 0;

     ystart = myid * n2;

     for(j=0; j<jend; j++) {
       y[j+ystart] = 0.0;
       for(i=0; i<n; i++) {
         y[j+ystart] += A[j][i] * x[i];
       }
     }

}e