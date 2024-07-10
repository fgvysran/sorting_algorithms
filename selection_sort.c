#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define LOW_NUM  5000

#define swap(a,b){\
    __typeof(a) _t=a;\
    a=b;b=_t;\
}

#define TEST(func,arr,n){\
    printf("TEST %s :",#func);\
    int*temp=(int *)malloc(sizeof(int)*n);\
    memcpy(temp,arr,sizeof(int)*n);\
    long long f=clock();\
    func(temp,0,n);\
    long long e=clock();\
    if(check(temp,0,n)){\
        printf(" OK ");\
    }else{\
      printf("false");\
    }\
    printf("%lldms",1000*(e-f)/CLOCKS_PER_SEC);\
}
int *get_rand_data(int n){
    int *a=(int *)malloc(sizeof(int)*n);
    for(int i=0,s;i<n;i++){
           s=rand()%10000;
           a[i]=s;
    }return a;
}

int check(int*a,int l,int r){
    for(int i=l+1;i<r-1;i++){
        if(a[i]<a[i-1])return 0;
    }return 1;
}
//Ñ¡ÔñÅÅÐò£¨selection_sort£©;//
void slection_sort(int *a,int l,int r){
     for(int i=0;i<r-1;i++){
        int ind=i;
        for(int j=i+1;j<r;j++){
            if(a[j]<a[ind])ind=j;
        }
        swap(a[ind],a[i]);
     }
}

int main(){
    srand(time(0));
    int *arr=get_rand_data(LOW_NUM);
    TEST(slection_sort,arr,LOW_NUM);
    return 0;
}