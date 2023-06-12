#include<stdio.h>
#include<stdlib.h>

#define Maxsize 50
#define InitSize 100

//顺序表实现

//静态分配
typedef struct Sqlist
{
    int data[Maxsize];//使用静态数组存放数据元素
    int length;//顺序表当前类型
}Sqlist;//将顺序表结构体类型 struct Sqlist 定义(重命名)为Sqlist 可读性高

void InitList(Sqlist &L){
    for(int i=0;i<Maxsize;i++)
    L.data[i]=0;
    L.length=0;
}
//静态分配按位插入
bool ListInsert(Sqlist &L,int i, int e){
    if(i<1||i>L.length+1)
    return false;
    if(L.length>=Maxsize)
    return false;
    for(int j=L.length;j>=i;j--){//从尾部开始向后移
        L.data[i]=L.data[i-1];
    }
    L.data[i-1]=e;//第i个元素对应数组i-1
    L.length++;
    return true;
}

//静态分配按位删除
bool ListDelete(Sqlist &L,int i, int &e){
    if(i<1||i>L.length)
    return false;
    if(L.length==0)
    return false;
    e=L.data[i-1];
    for(int j=i;j<L.length;j++){
        L.data[j-1]=L.data[j];
    }
    L.length--;
    return true;
}
//遍历打印静态分配顺序表
void PrintList(Sqlist L){
    printf("当前共有%d个元素：\n",L.length);
    for(int i=0;i<L.length;i++){
        printf("第%d个元素为%d\n",i+1,L.data[i]);
    }
    
}
//静态分配 按位查找
int GetElem(Sqlist L,int i){
    if(i<1||i>L.length)
    return 9999;
    return L.data[i-1];
}
//按值查找,返回值为位序(位序从1开始，数组下标从0开始)
int LocateElem(Sqlist L,int e){
    int i=0;
    for(;i<L.length;i++){
        if(L.data[i-1]==e)//若顺序表中元素类型为结构体类型，则需对各个分量进行分别比对，不能用==
        return i+1;
    }
    return 0;
}




//动态分配
typedef struct Seqlist
{
    int *data;//指向分配内存空间的指针
    int MaxSize;//最大容量
    int length;//当前长度
}Seqlist;

void InitList(Seqlist &L){
    L.data = (int*)malloc(InitSize*sizeof(int));
    L.length=0;
    L.MaxSize=InitSize;
}  //动态分配初始化也只是申请固定长度空间，只是在改变长度时，重新再申请空间，释放旧空间;

void IncreaseSize(Seqlist &L,int len){
    int *p=L.data;
    L.data=(int*)malloc((InitSize+len)*sizeof(int));
    for(int i=0;i<L.length;i++){
        L.data[i]=p[i];
    }
    L.MaxSize+=len;
    free(p);
}
//动态分配 按位查找;实现随机存取，时间复杂为为O(1)
int GetElem(Seqlist L,int i){
    if(i<1||i>L.length)
    return 9999;
    return L.data[i-1]; 
}






int main(){
    Sqlist L;
    int e;
    InitList(L);    
    for(int i=1;i<=10;i++)
    ListInsert(L,i,i);
    PrintList(L);
    ListDelete(L,7,e);
    PrintList(L);
    e=GetElem(L,7);
    printf("e为%d",e);
    LocateElem(L,4);
    return 0;   
}