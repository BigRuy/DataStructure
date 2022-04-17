#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define N 100
typedef int SLDataType;

//静态数据表
// typedef struct SeqList
// {
// 	SLDataType a[N];	
// 	int size;//表示数组存储了多少个数据
// }SL;
//动态顺序表
typedef struct SeqList
{
	SLDataType* a;
	int size;//表示数组存储了多少个数据
	int capaticy;//数组能实际存数据的空间容量多大
}SL;


//接口函数的声明
//顺序表的初始化
void SeqListInit(SL *ps)
{
	ps->a = NULL;
	ps->capaticy = ps->size = 0;
}
//打印顺序表
void SeqListPrint(SL *ps)
{
	for(int i=0;i<ps->size;i++){
		printf("%d ",ps->a[i]);
	}
	printf("\n");
}
//销毁顺序表
void SeqDestloryList(SL *ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->capaticy = ps->size = 0;
}
//检查空间是否需要扩容
void SeqCheckList(SL *ps)
{
	//如果没有空间或者空间不足，则扩容
	if(ps->size == ps->capaticy){
		int newcapaticy = ps->capaticy ==0 ? 4 : ps->capaticy*2;
		SLDataType* tmp = (SLDataType*)relloc(ps->a,newcapaticy*sizeof(SLDataType));
		//判断申请动态内存空间是否成功
		if(tmp == NULL){
			printf("relloc fail\n");
			exit(-1);
		}
		//申请成功后
		ps->a = tmp;
		ps->capaticy = newcapaticy;
	}
}
//顺序表尾部插入数据
/*
	分析：
		1.整个顺序表没有空间
		2.顺序表空间不够，需要扩容才能继续插入
		3.空间足够，直接插入数据即可
*/
void SeqListPushBack(SL *ps,SLDataType x)
{
	//检查增容
	SeqCheckList(ps);
	//直接插入
	ps->a[ps->size] = x;
	ps->size++;

	//销毁顺序表
	DestloryList(ps);
}
//顺序表尾部删除数据
/*
	分析：
		如果没有数据删除需要判断size的大小
*/
void SeqListPopBack(SL *ps)
{
	//ps->a[ps->size-1] = 0;
	//判断顺序表中是否还有顺序
	if(ps->size>0){
		ps->size--;
	}else{
		printf("顺序表为空\n");
	}
}
//顺序表头部插入数据
/*
	分析：
		1.整个顺序表没有空间
		2.顺序表空间不够，需要扩容才能插入
		3.空间足够，直接在头部插入
*/
void SeqListPushFront(SL *ps,SLDataType x)
{
	//如果空间满了需要扩容
	SeqCheckList(ps);
	//从后往前挪动数据
	int end = ps->size-1;
	while(end >= 0){
		ps->a[end+1] = ps->a[end];
		end--;
	}
	//头部插入数据
	ps->a[0] = x;
	ps->size++;
}
//顺序表头部删除
void SeqListPopFront(SL *ps)
{
	//如果顺序表为空直接终止程序
	assert(ps->size>0);
	int begin = 1;
	while(begin<ps->size){
		ps->a[begin-1] = ps->a[begin];
		begin++;
	}
	ps->size--;
}
//顺序表查找数据的位置，找到了就返回x的下标，没有找到就返回-1
int SeqListFind(SL *ps,SLDataType x)
{
	
	for(int i=0;i<ps->size;i++){
		if(x==ps->a[i]){
			return i;
		}
	}
	return -1;
}
//顺序表在指定位置插入数据
void SeqListInsert(SL *ps,int pos,SLDataType x)
{
	//判断是否是头部插入还是尾部插入
	if(pos=0){//如果指定位置是头部
		SeqCheckList(ps);//检查是否需要扩容
		SeqListPushFront(ps,x);
	}else if(pos = ps->size-1){//如果指定位置是尾部
		SeqCheckList(ps);//检查是否需要扩容
		SeqListPushBack(ps,x);
	}else if(pos>=ps->size){
		printf("顺序表只允许按顺序依次插入数据\n");
	}else{
		//从后往前向后挪动数据
		int end = ps->size-1;
		while(end>pos){
			ps->a[end+1] = ps->a[end];
			end--;
		}
		//指定pos位置插入
		ps->a[pos] = x;
		ps->size++;
	}

}
//顺序表删除指定位置的数据
void SeqListErase(SL *ps,int pos)
{
	//判断顺序表是否为空
	assert(ps->size<0);
	//判断是否为头部删除或者是尾部删除或者指定位置没有数据
	if(pos=0){//如果指定位置是头部
		SeqListPopFront(ps);
	}else if(pos = ps->size-1){//如果指定位置是尾部
		SeqListPopBack(ps);
	}else if(pos>=ps->size){//如果指定位置没有数据
		printf("此位置没有数据可删除\n");
	}else{//不是尾部或者头部的情况
		while(pos<ps->size-1){
			ps->a[pos] = ps->a[pos+1];
			pos++;
		}
		ps->size--;
	}
}


int main()
{
	SL sl;
	//测试初始化
	SeqListInit(&sl);
	//测试尾插
	SeqListPushBack(&sl,1);

	return 0;
}



















