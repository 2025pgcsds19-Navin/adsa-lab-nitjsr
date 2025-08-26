#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void printArray(int arr[], int n) {
    for(int i=0;i<n;i++) printf("%d ", arr[i]);
    printf("\n");
}

void insertionSort(int arr[], int n) {
    for(int i=1;i<n;i++) {
        int key=arr[i], j=i-1;
        while(j>=0 && arr[j]>key) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void bubbleSort(int arr[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-1-i;j++) {
            if(arr[j]>arr[j+1]) {
                int temp=arr[j]; arr[j]=arr[j+1]; arr[j+1]=temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for(int i=0;i<n;i++) {
        int min=i;
        for(int j=i+1;j<n;j++)
            if(arr[j]<arr[min]) min=j;
        int tmp=arr[i]; arr[i]=arr[min]; arr[min]=tmp;
    }
}

void shellSort(int arr[], int n) {
    for(int gap=n/2;gap>0;gap/=2) {
        for(int i=gap;i<n;i++) {
            int temp=arr[i], j=i;
            while(j>=gap && arr[j-gap]>temp) {
                arr[j]=arr[j-gap]; j-=gap;
            }
            arr[j]=temp;
        }
    }
}

void quickSort(int arr[], int low, int high) {
    if(low<high) {
        int pivot=arr[high], i=low-1;
        for(int j=low;j<high;j++) {
            if(arr[j]<pivot) {
                i++;
                int t=arr[i]; arr[i]=arr[j]; arr[j]=t;
            }
        }
        int t=arr[i+1]; arr[i+1]=arr[high]; arr[high]=t;
        int pi=i+1;
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1=m-l+1, n2=r-m;
    int L[n1], R[n2];
    for(int i=0;i<n1;i++) L[i]=arr[l+i];
    for(int j=0;j<n2;j++) R[j]=arr[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2) {
        if(L[i]<=R[j]) arr[k++]=L[i++];
        else arr[k++]=R[j++];
    }
    while(i<n1) arr[k++]=L[i++];
    while(j<n2) arr[k++]=R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if(l<r) {
        int m=(l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i) {
    int largest=i, l=2*i+1, r=2*i+2;
    if(l<n && arr[l]>arr[largest]) largest=l;
    if(r<n && arr[r]>arr[largest]) largest=r;
    if(largest!=i) {
        int t=arr[i]; arr[i]=arr[largest]; arr[largest]=t;
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[], int n) {
    for(int i=n/2-1;i>=0;i--) heapify(arr,n,i);
    for(int i=n-1;i>=0;i--) {
        int t=arr[0]; arr[0]=arr[i]; arr[i]=t;
        heapify(arr,i,0);
    }
}

int getMax(int arr[], int n) {
    int mx=arr[0];
    for(int i=1;i<n;i++) if(arr[i]>mx) mx=arr[i];
    return mx;
}

void countSortExp(int arr[], int n, int exp) {
    int output[n], count[10]={0};
    for(int i=0;i<n;i++) count[(arr[i]/exp)%10]++;
    for(int i=1;i<10;i++) count[i]+=count[i-1];
    for(int i=n-1;i>=0;i--) {
        output[count[(arr[i]/exp)%10]-1]=arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for(int i=0;i<n;i++) arr[i]=output[i];
}


void radixSort(int arr[], int n) {
    int m=getMax(arr,n);
    for(int exp=1;m/exp>0;exp*=10) countSortExp(arr,n,exp);
}

void countingSort(int arr[], int n) {
    int max=arr[0], min=arr[0];
    for(int i=1;i<n;i++) {
        if(arr[i]>max) max=arr[i];
        if(arr[i]<min) min=arr[i];
    }
    int range=max-min+1;
    int *count=(int*)calloc(range,sizeof(int));
    for(int i=0;i<n;i++) count[arr[i]-min]++;
    int idx=0;
    for(int i=0;i<range;i++)
        while(count[i]--) arr[idx++]=i+min;
    free(count);
}

void bucketSort(int arr[], int n) {
    int max=arr[0];
    for(int i=1;i<n;i++) if(arr[i]>max) max=arr[i];
    int bucketCount=max/10+1;
    int **buckets=(int**)malloc(bucketCount*sizeof(int*));
    int *sizes=(int*)calloc(bucketCount,sizeof(int));
    for(int i=0;i<bucketCount;i++) buckets[i]=(int*)malloc(n*sizeof(int));

    for(int i=0;i<n;i++) {
        int bi=arr[i]/10;
        buckets[bi][sizes[bi]++]=arr[i];
    }
    int idx=0;
    for(int i=0;i<bucketCount;i++) {
        insertionSort(buckets[i], sizes[i]);
        for(int j=0;j<sizes[i];j++) arr[idx++]=buckets[i][j];
        free(buckets[i]);
    }
    free(buckets); free(sizes);
}

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if(left>=right || bit<0) return;
    int i=left,j=right;
    while(i<=j) {
        while(i<=j && !((arr[i]>>bit)&1)) i++;
        while(i<=j && ((arr[j]>>bit)&1)) j--;
        if(i<j) { int t=arr[i]; arr[i]=arr[j]; arr[j]=t; }
    }
    radixExchangeSort(arr,left,j,bit-1);
    radixExchangeSort(arr,i,right,bit-1);
}

void addressCalculationSort(int arr[], int n) {
    int min=arr[0], max=arr[0];
    for(int i=1;i<n;i++) {
        if(arr[i]<min) min=arr[i];
        if(arr[i]>max) max=arr[i];
    }
    int range=max-min+1;
    int *buckets=(int*)calloc(range,sizeof(int));
    for(int i=0;i<n;i++) buckets[arr[i]-min]++;
    int idx=0;
    for(int i=0;i<range;i++)
        while(buckets[i]--) arr[idx++]=i+min;
    free(buckets);
}

int main() {
    int arr[]={44,7,98,99,5,62,32,7};
    int n=sizeof(arr)/sizeof(arr[0]);
    printf("Original: "); printArray(arr,n);
	selectionSort(arr,n);
    printf("Sorted:   "); printArray(arr,n);
    return 0;
}

