#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define LOW_NUM  600000

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
    printf("\n");\
}
//get rand date
int *get_rand_data(int n){
    int *a=(int *)malloc(sizeof(int)*n);
    for(int i=0,s;i<n;i++){
           s=rand()%10000;
           a[i]=s;
    }return a;
}
//check sort success
int check(int*a,int l,int r){
    for(int i=l+1;i<r;i++){
        if(a[i]<a[i-1])return 0;
    }return 1;
}
//sort kinds
//selection_sort------
void selection_sort(int *arr,int l,int r);
//insertion_sort---------
void insertion_sort(int *arr,int l,int r);
void insertion_sort2(int *arr,int l,int r);
//shell_sort --------
void  insert_sort_for_shell(int*arr,int l,int r,int step);
void shell_sort(int*arr ,int l ,int  r);//1
void shell_sort_hibbard(int*arr,int l,int r);//2
//buble_sort--------
void buble_sort_1(int *arr,int l,int r);
//quick sort -------
int  partion_sort(int*arr,int l,int r);
void quick_sort(int*arr,int l,int r);//index include r
void quick_sort_v2(int *arr,int l,int r);//index not include r
int three_point_select(int a,int b,int c);
void quick_sort_v3(int*arr ,int l,int r);
void __quick_sort(int*arr ,int l,int r);
void quick_sort_v4(int*arr,int l,int r);



int main(){
    srand(time(0));
    int *arr=get_rand_data(LOW_NUM);
    //TEST(selection_sort,arr,LOW_NUM);
   //TEST(insertion_sort,arr,LOW_NUM);
    //TEST(insertion_sort2,arr,LOW_NUM);
    TEST(shell_sort,arr,LOW_NUM);
    TEST(shell_sort_hibbard,arr,LOW_NUM);
    //TEST(buble_sort_1,arr,LOW_NUM);
    TEST(quick_sort,arr,LOW_NUM-1);
    TEST(quick_sort_v2,arr,LOW_NUM);
    TEST(quick_sort_v3,arr,LOW_NUM);
    TEST(quick_sort_v4,arr,LOW_NUM);


    free(arr);
    return 0;
}


//1. selection_sort
void selection_sort(int *a,int l,int r){
     for(int i=0;i<r-1;i++){
        int ind=i;
        for(int j=i+1;j<r;j++){
            if(a[j]<a[ind])ind=j;
        }
        swap(a[ind],a[i]);
     }
}
//2 .insertion_sort
void insertion_sort(int *arr,int l,int r){
    //find min
    int min=l;
    for(int i=l;i<r;i++){
        if(arr[i]<arr[min])min=i;
    }
    while(min>l){
        swap(arr[min-1],arr[min]);min--;
    }
    //start sort
    for(int i=l+1;i<r;i++){
        int j=i;
        while(arr[j] < arr[j-1]){
            swap(arr[j],arr[j-1]);j--;
        }
    }
}
//2.1.insertion_sort2
void insertion_sort2(int *arr,int l,int r){
    //find min
    int min=l;
    for(int i=l;i<r;i++){
        if(arr[i]<arr[min])min=i;
    }
    swap(arr[min],arr[0]);
    for(int i=l+1;i<r;i++){
        int t=arr[i];
        int j=i-1;
        while(arr[j]>t){
            arr[j+1]=arr[j];j--;
        }
        arr[j+1]=t;
    }
    return;
}

// 3 . shell_sort
void  insert_sort_for_shell(int*arr,int l,int r,int step){
    int min=l;
    //find min
    for(int i=l+step;i<r;i+=step){
          if(arr[min] > arr[i])min=i;
    }
    swap(arr[l],arr[min]);
    for(int i=l+2*step;i<r;i+=step){
        int t=arr[i];
        int j=i-step;
        while(arr[j] > t){
            arr[j+step]=arr[j];
            j-=step;
        }
        arr[j+step]=t;
    }
    return ;
}

void shell_sort(int*arr ,int l ,int  r){
    int n=(r-l);int step;int k=2;
    do{
        step=(n/k)==0? 1 : n/k;
        for(int i=l,I=l+step;i<I;i++){
              insert_sort_for_shell(arr,i,r,step);
        }
       k=k*2;
    }while(step!=1);
    return ;
}

void shell_sort_hibbard(int*arr,int l,int r){
    int n=(r-l);int step=1;
    for(;step<=n/2;step=step*2+1);
    do{
        step/=2;
        for(int i=l,I=l+step;i<I;i++){
            insert_sort_for_shell(arr,i,r,step);
        }
    }while(step>1);
    return;
}

//4. buble_sort
void buble_sort_1(int *arr,int l,int r){
    for(int i=l;i<r-1;i++){int f=0;
        for(int j=1;j<r-i;j++){
            if(arr[j]<arr[j-1]){
                swap(arr[j-1],arr[j]);
                f++;
            } 
        }if(f==0)break;
    }
    return ;
}

//quick_sort    index include r;
int partion_sort(int*arr,int l,int r){
    int x=arr[l];
    while(l<r){
        while( l<r && arr[r] >= x)r--;
        if(l<r)arr[l++]=arr[r];
        while ( l < r && arr[l] <= x )l++;
        if(l<r)arr[r--]=arr[l];
    }
    arr[l]=x;
    return l; 
}

void quick_sort(int*arr,int l,int r){
    if(l<r){
        int mid=partion_sort(arr,l,r);
        quick_sort(arr,l,mid-1);
        quick_sort(arr,mid+1,r);
    }
    return ;
}
//2.0 quick_sort    index not include r
void quick_sort_v2(int *arr,int l,int r){
    if(r-l<=2){
        if(r-l<=1)return;
        if(arr[l] > arr[l+1])swap(arr[l],arr[l+1]);
        return;
    }
    int x=l,y=r-1,t=arr[l];
    do{
        while(arr[x] < t)x++;
        while(arr[y] > t)y--;
        if(x<=y){
            swap(arr[x],arr[y]);
            x++;y--;
            }
    }while(x<=y);
    quick_sort_v2(arr,l,y+1);
    quick_sort_v2(arr,x,r);
    return ;
}
//quick_sort_v3 
int three_point_select(int a,int b,int c){
    if(a>b)swap(a,b);
    if(a>c)swap(b,c);
    if(b>c)swap(b,c);
    return b;
}
void quick_sort_v3(int*arr ,int l,int r){
    if(r-l<=2){
        if(r-l<=1)return;
        if(arr[l] > arr[l+1])swap(arr[l],arr[l+1]);
        return;
    }
    while(l<r){
    int x=l,y=r-1,t=three_point_select(arr[l],arr[(l+r)/2],arr[r-1]);
    do{
         while(arr[x] < t)x++;
         while(arr[y] > t)y--;
        if(x<=y){
            swap(arr[x],arr[y]);
            x++;y--;
        }
    }while(x<=y);
    quick_sort_v3(arr,l,y+1);
    l=x;
    }    
    return ;
}

//insert_sort combined quick_sort  16
void __quick_sort(int*arr ,int l,int r){
    while(r-l > 16 ){
    int x=l,y=r-1,t=three_point_select(arr[l],arr[(l+r)/2],arr[r-1]);
    do{
         while(arr[x] < t)x++;
         while(arr[y] > t)y--;
        if(x<=y){
            swap(arr[x],arr[y]);
            x++;y--;
        }
    }while(x<=y);
    __quick_sort(arr,l,y+1);
    l=x;
    }    
    return ;
}

void quick_sort_v4(int*arr,int l,int r){
    __quick_sort(arr,l,r);
    insertion_sort2(arr,l,r);
    return ;
}