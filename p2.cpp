#include<iostream>
#include<omp.h>
#include<chrono>
#include<algorithm>
using namespace std;
void bubblesort(int *arr,int size )
{
     int step=0;
        for(step=0;step<size-1;++step){
        for(int i=1;i<size-step-1;i++){
        if(arr[i]>arr[i+1]){
        swap(arr[i],arr[i+1]);
        }    
    }
    }
}

void parallelbubblesort(int *arr,int size )
{
     int step=0;
        #pragma omp paralle for
        for(step=0;step<size-1;++step){
        #pragma omp parallel for
        for(int i=1;i<size-step-1;i++){
        if(arr[i]>arr[i+1]){
        swap(arr[i],arr[i+1]);
        }    
    }
    }
}

void merge(int *arr,int s,int e)
{
 int mid=(s+e)/2;
 int len1=mid-s+1;
 int len2=e-mid;


 int *first=new int[len1];
 int *second=new int[len2];

 int mainIndex=s;

 for(int i=0;i<len1;i++){
    first[i]=arr[mainIndex++];
 }
for(int i=0;i<len2;i++){
    second[i]=arr[mainIndex++];
 }
mainIndex=mid+1;

for(int i=0;i<len2;i++){
    second[i]=arr[mainIndex++];
 }

int index1=0;
int index2=0;

mainIndex=s;

while(index1<len1 && index2<len2)
{
    if(first[index1]<=second[index2]){
        arr[mainIndex++]=first[index1++];
    }
    else{
        arr[mainIndex++]=second[index2++];
    }
}

while(index1<len1)
{
    arr[mainIndex++]=first[index1++];
}

while(index2<len2)
{
    arr[mainIndex++]=second[index2++];
}
delete []first;
delete []second;
}

void mergesort(int *arr,int s,int e)
{
    if(s>=e)
    {
        return ;
    }

    int mid=(s+e)/2;

    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);

    merge(arr,s,e);

}
void parallelmergesort(int *arr,int s,int e){
    if(s>=e){
        return ;
    }

    int mid=(s+e)/2;

    #pragma omp paralle sections
    {
        #pragma omp selection
        parallelmergesort(arr,s,mid);

        #pragma omp selection
        parallelmergesort(arr,mid+1,e);

    }
    merge(arr,s,e);
}
int main(){
    int arr[5]={1,4,3,5,2};
    for(int i=0;i<5;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

  
    bubblesort(arr,5);
    parallelbubblesort(arr,5);
    mergesort(arr,0,5);
    parallelmergesort(arr,0,5);
    
    for(int i=0;i<5;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}