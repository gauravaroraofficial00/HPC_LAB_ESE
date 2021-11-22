#include<stdio.h>

__global__ void Factorial(int *gpu_num,long int *gpu_res)
{
  int i;
  *gpu_res=1;
  for(i=1;i<=*gpu_num;i++)
  {
    *gpu_res = *gpu_res * i;      
  }
}

int main()
{
  int Number;  
  int *dev_number;
  long int *res, result; //store result 
  
  printf("\n\t Enter the number : ");
  scanf("%d",&Number);
  
  //to allocate memory for a number on the GPU/Device
  cudaMalloc((void**)&dev_number,sizeof(int));
  cudaMalloc((void**)&res,sizeof(long int));
  
  //copy number to the GPU/Device memory
  cudaMemcpy(dev_number,&Number,sizeof(int),cudaMemcpyHostToDevice);
 
  //call square function which will execute parallely on GPU
  Factorial<<<1,1>>>(dev_number,res);

  //copy result back from device/GPU back to CPU/Host
  cudaMemcpy(&result,res,sizeof(long int),cudaMemcpyDeviceToHost);

  //display result on the screen
  printf("\n\t Factorial of number %d is %ld \n",Number,result); 
 
  //deallocate GPU/Device memory
  return 0; 
}

