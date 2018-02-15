void MyMatMat(double C[N/NPROCS][N],
              double A[N/NPROCS][N], double B[N][N/NPROCS], int n){
     int  i, j, k, l;
     int  ib;
     int  lend = numprocs;
     int  iloop,ierr;
     int  j_start;
     int  isendPE, irecvPE;

     MPI_Status istatus;

     /* Information of Send and recv PEs */
     isendPE = myid - 1;
     irecvPE = myid + 1;
     if (myid == 0) isendPE = numprocs - 1;
     if (myid == numprocs - 1) irecvPE = 0;

     /* Block Length */
     ib = n/numprocs;

     /* Local Matrix-Matrix Multiplication -------------------  */
     /* This shoule be modified to finish parallelizing.        */
     for(l=0;l<lend;l++){
       j_start = ib *((myid+l)%lend);
       for(i=0;i<ib;i++){
         for(j=0;j<ib;j++){
           for(k=0;k<n;k++){
             C[i][j_start+j] += A[i][k] * B[k][j];
           }
         }
       }
       if(l!=lend-1){
         if(myid%2==1){
           MPI_Send(B,ib*n,MPI_DOUBLE,isendPE,l,MPI_COMM_WORLD);
           MPI_Recv(B_T,ib*n,MPI_DOUBLE,irecvPE,l+numprocs,MPI_COMM_WORLD,&istatus);
         }else{
           MPI_Recv(B_T,ib*n,MPI_DOUBLE,irecvPE,l,MPI_COMM_WORLD,&istatus);
           MPI_Send(B,ib*n,MPI_DOUBLE,isendPE,l+numprocs,MPI_COMM_WORLD);
         }
         for(i=0;i<n;i++){
           for(j=0;j<ib;j++){
             B[i][j] = B_T[i][j];
           }
         }
       }

     }
     /* -----------------------------------------------------  */

}
