#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DIM 2

typedef double ** Matrix;

const double SQRT5 = 2.23606797749979;
const double PHI = 1.618033988749895;
const double PSI = -0.6180339887498949;

double explog(double a, int n);
void printmat(Matrix A, int n);
void genmat(Matrix *A, int n);
void freemat(Matrix *A, int n);
void fillmat(Matrix *A, int n);
void idenmat(Matrix *A, int n);
void copymat(Matrix A, Matrix *B, int n);
void multimat(Matrix A, Matrix B, Matrix *C);
void potmat(Matrix *A, int b, int n);
void expmat(Matrix *A, Matrix P, Matrix D, Matrix R, int b, int n);

int main()
{
	Matrix A;
	genmat(&A, DIM);
	A[0][0] = 0.0; A[1][0] = 1.0;
	A[0][1] = 1.0; A[1][1] = 1.0;
	printmat(A, DIM);
	
	Matrix P, D, R;
    genmat(&P, DIM);
    genmat(&D, DIM);
    genmat(&R, DIM);
	
	// P
    P[0][0] = 1.0; P[0][1] = 1.0;
    P[1][0] = PHI; P[1][1] = PSI;
	
	// D
    D[0][0] = PHI; D[0][1] = 0.0;
    D[1][0] = 0.0; D[1][1] = PSI;
	
	// P^-1
    double detP = -SQRT5;
    R[0][0] =  PSI / detP; R[0][1] = -1.0 / detP;
    R[1][0] = -PHI / detP; R[1][1] =  1.0 / detP;
	
	int num = 500;
	printf("n: %d\n", num);
	//potmat(&A, num, DIM);
	expmat(&A, P, D, R, num, DIM);

	printmat(A, DIM);
	freemat(&A, DIM);
	freemat(&P, DIM);
    freemat(&D, DIM);
    freemat(&R, DIM);
	return 0;
}

double explog(double a, int n)
{ 	 
	if (n == 0) return 1;
		
	if (n%2 == 1)
		return (a * explog(a, n-1));
	else
	{
		double temp = explog(a, n/2);
		return temp * temp;
	}
}

void printmat(Matrix A, int n)
{
    int i,j;
    for(i = 0; i < n; i ++)
        for(j = 0; j < n; j ++)
        {
            printf("%lf\t", A[i][j]);
            if((j+1)%n == 0)
                printf("\n");
		}
    printf("\n");
}

void genmat(Matrix *A, int n)
{
	int i;
    *A = (double **)malloc(sizeof(double *)*n);
    for(i = 0; i < n; i ++)
    {
        (*A)[i] = (double *)malloc(sizeof(double)*n);
    }
}

void freemat(Matrix *A, int n)
{
    int i;
    for(i = 0; i < n; i ++)
    {
        free((*A)[i]);
    }
    free(*A);
    *A = NULL;
}

void fillmat(Matrix *A, int n)
{
    int i,j;
    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < n; j ++)
        {
            (*A)[i][j] = 0.0;
        }
    }
}

void idenmat(Matrix *A, int n)
{
    int i,j;
    for(i = 0; i < n; i ++)
        for(j = 0; j < n; j ++)
        {
			if(i == j)
				(*A)[i][j] = 1.0;
			else
				(*A)[i][j] = 0.0;
        }
}

void copymat(Matrix A, Matrix *B, int n)
{
	int i,j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            (*B)[i][j] = A[i][j];
}

void multimat(Matrix A, Matrix B, Matrix *C)
{
	(*C)[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
	(*C)[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
	(*C)[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
	(*C)[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
}

void potmat(Matrix *A, int b, int n)
{
    int i;
    Matrix res;
    Matrix tem;
    genmat(&res, n);
    idenmat(&res, n);
    genmat(&tem, n);
    for (i = 0; i < b; i++)
    {
        fillmat(&tem, n);
        multimat(res, *A, &tem);
        copymat(tem, &res, n);
    }
    copymat(res, A, n);
    freemat(&res, n);
    freemat(&tem, n);
}

void expmat(Matrix *A, Matrix P, Matrix D, Matrix R, int b, int n)
{
    Matrix temp;
    genmat(&temp, n);

    // D^b
    D[0][0] = pow(D[0][0], b); D[0][1] = 0.0;
    D[1][0] = 0.0;             D[1][1] = pow(D[1][1], b);
    if (fabs(D[1][1]) < 1e-2) D[1][1] = 0.0; // estabilización
	
    multimat(P, D, &temp);   // temp = P * D^b
    multimat(temp, R, A);    // *A = temp * P^-1
	
	//floor
	(*A)[0][0] = floor((*A)[0][0]);
	(*A)[0][1] = floor((*A)[0][1]);
	(*A)[1][0] = floor((*A)[1][0]);
	(*A)[1][1] = floor((*A)[1][1]);
	
    freemat(&temp, n);
}