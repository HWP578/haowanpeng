#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define ElemType int
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
//定义顺序表结构体
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
}SqList;
//定义初始化函数
int InitList_Sq(SqList *L)
{
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    //分配失败返回错误
    if(L->elem == NULL)
        return OVERFLOW;
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}
//定义初始数据函数
int AssignInitalValues_Sq(SqList *L,ElemType *a,int e)
{
    //判断是否足够存储
    while(L->listsize < e)
    {
        L->elem = (ElemType *)realloc(L->elem,sizeof(ElemType)*(LIST_INIT_SIZE+LISTINCREMENT));
        if(L->elem == NULL)
            return OVERFLOW;
        L->listsize +=LIST_INIT_SIZE;
    }
    for(int i=0;i<e;i++)
    {
        *(L->elem+i) = *(a+i);
    }
    L->length = e;
    return OK;
}
//定义插入函数
int ListInsert_Sq(SqList *L,ElemType e,int i)
{
    //判断位置是否合法
    if(i<1 || i>L->length + 1)
        return ERROR;
    //判断顺序表是否已满
    while(L->length >= L->listsize)
    {
        ElemType *newbase = (ElemType *)realloc(L->elem,(LIST_INIT_SIZE+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            return OVERFLOW;
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType *p = L->elem+i-1; //找到插入位置
    ElemType *q = L->elem+L->length-1;//找到最后一个位置
    //从最后开始依次往后移动一位
    for(;q>=p;q--)
    {
        *(q+1) = *q;
    }
    *p = e;
    L->length++;
    return OK;
}
//定义删除函数
int ListDelete_Sq(SqList *L,int i,ElemType *e)
{
    //删除位置是否合法
    if(i<1 || i>L->length)
        return ERROR;
    ElemType *p = L->elem+i-1;   //找到删除位置
    *e = *p;     //将删除的数据保存
    ElemType *q = L->elem + L->length-1;  //找到最后一个位置
    //从删除位置的下一个位置开始依次前移一位
    for(p++;p<=q;p++)
    {
        *(p-1) = *p;
    }
    L->length--;
    return OK;
}
//定义合并函数
int ListMerge_Sq(SqList *L1,SqList *L2,SqList *L3)
{
    //L3->elem = 
    ElemType *p,*q,*r,*p_last,*q_last;
    p = L1->elem;
    q = L2->elem;
    p_last = L1->elem + L1->length-1;
    q_last = L2->elem + L2->length-1;
    L3->length = L3->listsize = L1->length + L2->length;
    L3->elem = (ElemType *)malloc(L3->listsize*sizeof(ElemType));
    if(L3->elem == NULL)
        return OVERFLOW;
    r = L3->elem;
    while(p <= p_last && q <= q_last)
    {
        if(*p<*q)
        {   
            *r = *p;
            r++;
            p++;
        }
        else
        {
            *r = *q;
            r++;
            q++;
        }
    }
    while(p <= p_last)
        *r++ = *p++;
    while(q <= q_last)
        *r++ = *q++;
    return OK;
}
int main()
{
    SqList List1,List2,List3;
    ElemType Value = 0;
    ElemType a[] = {1,3,5,7,9};
    ElemType b[] = {2,4,6,8,10};
    int l = sizeof(a)/sizeof(a[0]);
    InitList_Sq(&List1);
    InitList_Sq(&List2);
    AssignInitalValues_Sq(&List1,a,l);
    AssignInitalValues_Sq(&List2,b,l);
    ListInsert_Sq(&List1,2,2);
    ListDelete_Sq(&List2,1,&Value);
    ListMerge_Sq(&List1,&List2,&List3);
    printf("List1 values:\n");
    for(int i=0;i<List1.length;i++)
    {
        printf("%d\t",*(List1.elem+i));
    }
    printf("\n");
    printf("List2 values:\n");
    for(int i=0;i<List2.length;i++)
    {
        printf("%d\t",*(List2.elem+i));
    }
    printf("\n");
    printf("List3 values:\n");
    for(int i=0;i<List3.length;i++)
    {
        printf("%d\t",*(List3.elem+i));
    }
    return 0;
}