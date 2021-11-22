#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;


void matvec(int matrix[5][5], int vector[], int result[], int size_i, int size_j)
{
   int i,j;
#pragma omp parallel shared(matrix,result,vector) private(i,j) 
   {
#pragma omp for  schedule(static)
   for (i=0; i<size_i; i=i+1){
      result[i]=0.;
      for (j=0; j<size_j; j=j+1){
         result[i]=(result[i])+((matrix[i][j])*(vector[j]));
      }
   }
   }
 
}


int main()
{
int m[5][5];
int n1=5;	
int n2=5;

for(int i=0;i<5;i++)
{
for(int j=0;j<5;j++)
{
	m[i][j]=1;
	}
	}
	
int vec[5];
for(int i=0;i<n1;i++)
{
	vec[i]=1;
	}
	
int res[5];

matvec(m,vec,res,n1,n2);
for(int i=0;i<5;i++)
cout<<res[i]<<" ";
cout<<endl;
return 0;


}
