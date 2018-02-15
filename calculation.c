#include<stdio.h>
#include<math.h>
#include"calculation.h"

//fft$B$N$?$a$N%G!<%?$r:n$k@.8y(B0$B<:GT(B1
static int fft_init(double *re, double *im, int num);

int power_two(int num)
{
	int power=0;

	while(num!=1){
		power++;
		num >>= 1;
	}

	return power;
}

static int fft_init(double *re, double *im, int num)
{
	int i, j;
	int indexfrom, offset;
	int indexto;
	int dfttimes;
	int power;
	double *rbuf, *ibuf;

	if((rbuf = (double*)malloc(sizeof(double)*num)) == NULL){
		fprintf(stderr, "Allocation Error\n");
		return 1;
	}

	if((ibuf = (double*)malloc(sizeof(double)*num)) == NULL){
		fprintf(stderr, "Allocation Error\n");
		free(rbuf);
		return 1;
	}

	dfttimes = num;
	power = power_two(num);  //num$B$,#2$N2?>h$G$"$k$+$rJV$9(B

	for(i=0; i<power-1; i++){
		indexto = offset = 0;

		while(indexto < num){
			indexfrom = 0;
			while(indexfrom < dfttimes){
				rbuf[indexto] = re[indexfrom + offset];
				ibuf[indexto] = im[indexfrom + offset];

				indexto++;
				indexfrom += 2;
				if(indexfrom == dfttimes) indexfrom = 1;
			}

			offset += dfttimes;
		}

		for(j=0; j<num; j++){
			re[j] = rbuf[j];
			im[j] = ibuf[j];
		}
		dfttimes /= 2;
	}

	free(rbuf);
	free(ibuf);

	return 0;

}

void swap(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int fft_ifft(double *re, double *im, int num, int flag)
{
	int i, j, k, power;
	int newnum;
	double unit_angle, step_angle;
	int dft, dftnum;
	int indexto, indexfrom1, indexfrom2;
	double *temp_re, *temp_im;
	double rbuf, ibuf, angle;

	power = power_two(num);

	//newnum$B$O(Bnum$B$N$&$A#2$NN_>h$GI=8=$G$-$kItJ,$N?t(B($B%U!<%j%(JQ49$9$k8D?t(B)
	for(i=0, newnum=1; i<power; i++){
		newnum <<= 1;
	}

	if((temp_re = (double*)malloc(sizeof(double)*newnum)) == NULL){
		fprintf(stderr, "Allocationerror!\n");
		return -1;
	}

	if((temp_im = (double*)malloc(sizeof(double)*newnum)) == NULL){
		fprintf(stderr, "Allocationerror!\n");
		free(temp_re);
		return -1;
	}

	if(flag == IDFT){
		for(i=0; i<newnum; i++){
			re[i] = re[i]/newnum;
			im[i] = im[i]/newnum;
		}
	}

	fft_init(re, im, newnum); //$B%G!<%?$NJB$S$r=i4|2=(B

	unit_angle = 2.0 * PI / newnum;
	dft = 2;

	for(i=0; i<power; i++){
		dftnum = newnum / dft;
		step_angle = unit_angle * dftnum;

		for(j=0; j<dftnum; j++){
			angle = 0.0;

			for(k=0; k<dft; k++){
				indexto = j*dft + k;

				if(k < dft/2){
					indexfrom1 = indexto;
					indexfrom2 = indexfrom1 + dft/2;
				}else{
					indexfrom2 = indexto;
					indexfrom1 = indexto - dft/2;
				}

				rbuf = re[indexfrom2];
				ibuf = im[indexfrom2];
				temp_re[indexto] = re[indexfrom1] + rbuf*cos(angle) + flag*ibuf*sin(angle);
				temp_im[indexto] = im[indexfrom1] + ibuf*cos(angle) - flag*rbuf*sin(angle);

				angle += step_angle;
			}
		}
		for(j=0; j<newnum; j++){
			re[j] = temp_re[j];
			im[j] = temp_im[j];
		}

		dft *= 2;
	}

	free(temp_re);
	free(temp_im);

	return newnum;
}

void fft_swap(double *re, double *im, int num)
{
	int power;
	int i;
	int newnum;

	power = power_two(num);

	for(i=0, newnum=1; i<power; i++){
		newnum <<= 1;
	}

	for(i=0; i<newnum/2; i++){
		swap(&re[i], &re[newnum/2 + i]);
		swap(&im[i], &im[newnum/2 + i]);
	}
}

