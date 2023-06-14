#include <stdio.h>
#include <stdlib.h>

void begin();
void init();
void inputMN();
void inputAvailable();
void inputAllocation();
void inputMax();
void getNeed();
void inputRequest();
void tryDistribute();
void safeTest();
void recursion(int Num, int *Work, int *Finish, int **safeLists, int *safelist, int *safelistNum);
void add(int **safeLists, int *safelist, int *safelistNum);

int *Available;   // 可利用资源向量
int **Max;        // 最大需求矩阵
int **Allocation; // 分配矩阵
int **Need;       // 需求矩阵
int *Request;     // 请求向量
// ArrayList Work=new ArrayList<>();//工作向量
// ArrayList<Boolean> Finish=new ArrayList<>();//
int N; // 进程数
int M; // 资源数
int t;
int Pi; // 进程序号
int function;

int main(int argc, char const *argv[])
{
    begin();
    return 0;
    // system("pause");
}
void begin()
{
    
    while(1)
    {
    printf("***********************************************************\n");
    printf("请选择功能:\n1、系统是否安全\n2、是否立即分配\n3、退出\n:");
    scanf("%d", &function);
    if(function==3)
	{
		break; 
	} 
	 
    inputMN();
    inputAvailable();
    inputAllocation();
    inputMax();
    getNeed();
    inputRequest();
    tryDistribute();
    safeTest();
    }
}
void init()
{
}
void inputMN()
{
    printf("输入：（进程数 资源数）\n");
    scanf("%d%d", &N, &M);
}
void inputAvailable()
{
	int i = 0;
    printf("请输入Available矩阵:\n");
    Available = (int *)malloc(sizeof(int) * M);
    for (i = 0; i < M; i++)
    {
        scanf("%d", Available + i);
    }
}
void inputAllocation()
{
    int i;
    int j;
    printf("请输入Allocation矩阵:\n");
    Allocation = (int **)malloc(sizeof(int *) * N);
    for (i = 0; i < N; i++)
    {
        Allocation[i] = (int *)malloc(sizeof(int) * M);
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            scanf("%d", Allocation[i] + j);
        }
    }
}
void inputMax()
{
    int i;
    int j;
    printf("请输入Max矩阵:\n");
    Max = (int **)malloc(sizeof(int *) * N);
    for (i = 0; i < N; i++)
    {
        Max[i] = (int *)malloc(sizeof(int) * M);
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            scanf("%d", Max[i] + j);
        }
    }
}
void getNeed()
{
    int i;
    int j;
    Need = (int **)malloc(sizeof(int *) * N);
    for (i = 0; i < N; i++)
    {
        Need[i] = (int *)malloc(sizeof(int) * M);
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}
// void print(ArrayList list)
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < M; j++)
//         {
//                 System.out.print(((ArrayList)list.get(i)).get(j));
//         }
//         System.out.println();
//     }
// }
void inputRequest()
{
	int i = 0;
    if (function == 1)
    {
        Pi = 0;
        Request = (int *)malloc(sizeof(int) * M);
        for (i = 0; i < M; i++)
        {
            Request[i] = 0;
        }
    }
    else
    {
        printf("输入进程序号");
        scanf("%d", &Pi);
        Pi--;//使输入序号从1开始而运算还是按从0开始；即对用户来说第一个序号为1，对计算机第一个序号为0
        Request = (int *)malloc(sizeof(int) * M);
        for (i = 0; i < M; i++)
        {
            scanf("%d", Request + i);
        }
    }
}
void tryDistribute()
{
	int i=0;
    for (i = 0; i < M; i++)
        if (Request[i] > Max[Pi][i])
        {
            printf("所需要的资源数已超过它所宣布的最大值");
            return;
        }
    for (i = 0; i < M; i++)
        if (Request[i] > Available[i])
        {
            printf("表示尚无足够资源");
            return;
        }

    for (i = 0; i < M; i++)
    {
        Available[i] -= Request[i];
        Allocation[Pi][i] += Request[i];
        Need[Pi][i] -= Request[i];
    }
}
void safeTest()
{
    int **Work;
    int *Finish;
    int safelistNum = 0; // 安全序列数
    int i;
    int j;
    int **safeLists; // 所有安全序列
    int *safelist;   // 一个安全序列
    // 初始化Work
    Work = (int *)malloc(sizeof(int) * M);
    for (i = 0; i < M; i++)
    {
        Work[i] = Available[i];
    }
    
    // 初始化Finish
    Finish = (int *)malloc(sizeof(int) * N);
    for (i = 0; i < N; i++)
    {
        Finish[i] = 0;
    }
    // 初始化safelist
    safelist = (int *)malloc(sizeof(int) * N);
    //初始化safeLists
    safeLists=(int**)malloc(sizeof(int*)*40);
	for(i=0;i<40;i++) 
    {
    	safeLists[i]=(int*)malloc(sizeof(int)*N); 
    }
    recursion(1, Work, Finish, safeLists, safelist, &safelistNum); // 找安全序列第1个进程
    if (safelistNum != 0)
    {
        printf("安全序列数为%d\n所有的安全序列:\n",safelistNum);
        for (i = 0; i < safelistNum; i++)
        {
            for (j = 0; j < N; j++)
            {
                printf("p%d ", safeLists[i][j]+1);//+1使输出序号从1开始而运算还是按从0开始；即对用户来说第一个序号为1，对计算机第一个序号为0
            }
            printf("\n");
        }
    }
    else
    {
        if(function==1)
        {
            printf("系统不安全\n");
        }
        else
        {
            printf("不可立即分配\n");
        }
    }
    return;
}
void recursion(int Num, int *Work, int *Finish, int **safeLists, int *safelist, int *safelistNum)
{ // 找安全序列第Num个进程
    if (Num == N+1)
    {
        add(safeLists, safelist, safelistNum);
        return;
    }
    int i = 0;
    for (i = 0; i < N; i++) // 序列第Num个进程为i
        if (!Finish[i])
        {
            int ok = 1;
            int j=0;
            for (j = 0; j < M; j++)
                if (Need[i][j] > Work[j])
                    ok = 0;
            if (!ok)
                continue;
            for (j = 0; j < M; j++)
                //Work[j] += Allocation[i][j];
                Work[j] += Allocation[i][j];
                
            safelist[Num - 1] = i;
            Finish[i] = 1;
            recursion(Num + 1, Work, Finish, safeLists, safelist, safelistNum); // 找安全序列第Num+1个进程
            Finish[i] = 0;
            // safelist.remove(safelist.size() - 1);
            for (j = 0; j < M; j++)
                //Work[j] -= Allocation[i][j];
                Work[j] -= Allocation[i][j];
        }
}
void add(int **safeLists, int *safelist, int *safelistNum) // 将safelist追加到safelists后
{
    int i = 0;
    int j = 0;
    (*safelistNum)++;
    //printf("%d",safelistNum);
    //int **fornow = (int **)malloc(sizeof(int *) * (*safelistNum));
    //int **fornow;
    //int *t;
    //fornow=safeLists;
    //fornow=(int **)malloc(sizeof(int *) * (*safelistNum));
    //for (i = 0; i < *safelistNum; i++)
    //{
      //  fornow[i] = (int *)malloc(sizeof(int) * N);
    //}
    //
     //for (i= 0; i < (*safelistNum) - 1; i++)       
    //{                                              
      //  for (j = 0; j < N; j++)                    
        //{                                          
            //printf("%d",safeLists[i][j]);          
     //   }                                          
    //}                                              
    //
    /*for (i = 0; i < (*safelistNum) - 1; i++)
    {
        for (j = 0; j < N; j++)
        {
            fornow[i][j] = safeLists[i][j];
        }
    } */
     
    for (j = 0; j < N; j++)
    {
        safeLists[(*safelistNum)-1][j] = safelist[j];
    }
    //free(safeLists);
   
}