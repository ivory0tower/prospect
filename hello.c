
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define Max 50
#define bool int
#define true 1
#define false 0
//全局变量 
int no1;//进程数
int no2;//资源种类数
int r;//安全标志
int max[Max][Max],allocation[Max][Max],need[Max][Max],avaiable[Max];
//函数声明 
void Init();
void check();
void print(); 


void main(){
	int i,j,f1,f2;
	char c;
	int request[no2],allocation1[no1][no2],need1[no1][no2],avaiable1[no2];
	Init();
	print();
	check();
	if(r==1)
	{
		do{
			f1=0,f2=0;
			
			
			printf("请输入请求资源的进程号（1~%d)\n",no1);
			while(1)
			{
				scanf("%d",&i);
				if(i>no1)
				{
					printf("输入错误，请重新输入\n");
					continue; 
				}
				else	break;
				
			}
			
			printf("请输入所请求的资源数request[j]：");
			for(j=0;j<no2;j++)
			scanf("%d",&request[j]);
			
			for(j=0;j<no2;j++)
			{
				if(need[i-1][j]<request[j])
				{
					f1=1;break;
				}
			} 
			if(f1)printf("请求资源数高于所需资源数，请求失败!\n");
			else{
					for(j=0;j<no2;j++)
					{
						if(request[j]>avaiable[j])
						{
							f2=1;break;
						}
					}
					if(f2)printf("请求资源数高于可分配资源数，请求失败！\n");
					else//可分配 
					{
						for(j=0;j<no2;j++)
						{
							avaiable1[j]=avaiable[j];
							allocation1[i-1][j]=allocation[i-1][j];
							need1[i-1][j]=need[i-1][j];//保留原有数据，恢复用 
							
							avaiable[j]-=request[j];
							need[i-1][j]-=request[j];
							allocation[i-1][j]+=request[j];//进行分配 
						} 
						printf("\n尝试分配资源\n");
						print();//输出当前资源情况 
						printf("\n检查分配后安全性\n"); 
						check();//检查安全性
						if(r==0)//不安全恢复 
						{
							for(j=0;j<no2;j++)
							{
								avaiable[j]=avaiable1[j];
								allocation[i-1][j]=allocation1[i-1][j];
								need[i-1][j]=need1[i-1][j];
							} 
							printf("恢复资源为分配前状态\n");
							print(); 
						} 
						else if(r==1)
						{
							int flag=1;
							for(j=0;j<no2;j++)
							{
								if(need[i-1][j]!=0)
								{
									flag=0;
									break;
								}
							}
							if(flag==1)
							{
								for(j=0;j<no2;j++)
								{
									avaiable[j]+=allocation[i-1][j];
									allocation[i-1][j]=0;
								}
							}
							print();
						}
					}
				}
			
			printf("是否要继续分配（Y/N）\n");
			c=getchar();
			c=getchar();
		
		}while(c=='y'||c=='Y');
	}
} 

void Init(){
	int i,j;
	printf("********************************\n");
	printf("*           银行家算法         *\n");
	printf("********************************\n");
	printf("请输入进程数目：\n");
	scanf("%d",&no1);
	printf("请输入资源种类数：\n");
	scanf("%d",&no2);
	printf("请输入Max矩阵：\n");
	for(i=0;i<no1;i++){
		for(j=0;j<no2;j++){
			scanf("%d",&max[i][j]);
		}
	} 
	printf("请输入Allocation矩阵：\n");
	for(i=0;i<no1;i++){
		for(j=0;j<no2;j++){
			scanf("%d",&allocation[i][j]);
		}
	} 
	printf("请输入可分配资源数:\n");
	for(j=0;j<no2;j++)
	scanf("%d",&avaiable[j]);
	for(i=0;i<no1;i++){
		for(j=0;j<no2;j++){
			need[i][j]=max[i][j]-allocation[i][j];	
		}
	} 
} 
void print(){
	int i,j;
	printf("\n");
	printf("----当前资源分配情况----\n");
	printf("|进程名\t|\tMax\t\t|Allocation\t|Need\t\t|Available\n");
	for(i=0;i<no1;i++){
		printf("process%d\t",i+1);
		for(j=0;j<no2;j++)
		printf("%d ",max[i][j]);
		printf("\t   ");
		for(j=0;j<no2;j++)
		printf("%d ",allocation[i][j]);
		printf("\t");
		
			for(j=0;j<no2;j++)
		printf("%d ",need[i][j]);
		printf("\t");
		if(i==0){
			for(j=0;j<no2;j++)
			printf("%d ",avaiable[j]);
		}
		printf("\n");
	} 
}
void check(){
	int i,j;
	int f;
	int n=0;
	int k=no1;
	int work[no2];
	bool finish[no1];
	int a[no1];
	r=1;
	for(i=0;i<no1;i++)
	finish[i]=false;
	for(j=0;j<no2;j++)
	work[j]=avaiable[j];
	do{
		for(i=0;i<no1;i++)//对每个进程来说 
		{
			f=0;
			if(finish[i]==false)//进程属性判断 
			{
				f=1;
			}
			
			// 其内部资源条件判断 
			for(j=0;j<no2;j++) 
				{
					if(work[j]<need[i][j])
					{
						f=0;
						break;
					}
				}
			// 
			if(f==1)
			{
				finish[i]=true;
				a[n++]=i;
				for(j=0;j<no2;j++)
				work[j]+=allocation[i][j];
			}
		}
		k--;
	}while(k>0);
	
	
	for(i=0;i<no1;i++)
	{
		if(finish[i]==false)
		{
			r=0;
			break;
		}
	}
	if(r==0)
	{
		printf("系统当前处于不安全状态！"); 
	}
	else{
		printf("系统当前处于安全状态，安全序列为：");
		printf("p%d",a[0]+1);
		for(i=1;i<no1-1;i++)
		printf(",p%d",a[i]+1);
		printf(",p%d",a[no1-1]+1); 
		printf("\n");
		
	}
} 