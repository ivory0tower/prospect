#include <stdio.h>
#include <stdlib.h>
#define Maxsize 50
#define InitSize 100
typedef struct  {
    int data[Maxsize];
    int length;
}Sqlist;//静态分配

typedef struct 
{
    int *data;
    int MaxSize,length;
}SeqList;
void InitList(Sqlist *L);
void InitSeqList(SeqList *L);
void Increase(SeqList *L,int len);
int ListInsert(Sqlist *L,int i,int e);//i为位序
int ListDelete(Sqlist *L,int i,int *e);
int getElem(Sqlist L,int i);//按位寻找
int locatElem(Sqlist L,int e);
void printList(Sqlist L);
void main(){
    Sqlist  L;
    InitList(&L);
    ListInsert(&L,1,2);
    ListInsert(&L,2,0);
    ListInsert(&L,3,2);
    ListInsert(&L,4,3);
    ListInsert(&L,5,1);
    PrintList(L);
}

void InitList(Sqlist *L){
    for(int i=0;i<Maxsize;i++)
    L->data[i]=0;
    L->length=0;

}
void InitSeqList(SeqList *L){
    L->data=(int *)malloc(InitSize*sizeof(int));
    L->length=0;
    L->MaxSize=InitSize;
}
void Increase(SeqList *L,int len){
    int *p=L->data;
    L->data=(int*)malloc((InitSize+len)*sizeof(int));
    for(int i=0;i<L->length;i++){
        L->data[i]=p[i];
    }
    L->MaxSize=L->MaxSize+len;
    free(p);
}
int ListInsert(Sqlist *L,int i,int e){//位序为i，是第i个，但实际存储在data[i-1]
    if(i<1||i>L->length+1)
    return 1;
    if(L->length>=Maxsize)
    return 1;
    for(int j=L->length;j>=i;j--){//将[i-1]到[length-1]移到[i]到[length]
        L->data[j]=L->data[j-1];
    }
    L->length++;
    L->data[i-1]=e;
    return 0;
}
int ListDelete(Sqlist *L,int i,int *e){
    if(i<1||i>L->length)
    return 1;
    if(L->length==0)
    return 2;
    e=L->data[i-1];
    for(int j=i;j<L->length;i++)//data[i]到data[length-1]  移到 data[i-1] 到[length-2]
    {
        L->data[i-1]=L->data[i];
    }
    L->length--;
    return 0;
}
int getElem(Sqlist L,int i){
    return L.data[i-1];
}
int locateElem(Sqlist L, int e){
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
        return i+1;//返回位序

        return 0;
}
void PrintList(Sqlist L){
    for(int i=0;i<L.length;i++)
    {
        printf("第%d个元素为%d\n",i+1,L.data[i]);
    }
}