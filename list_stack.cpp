#include <stdio.h>
#include <stdlib.h>

void print_menu() {
	
    printf("*******************************************************\n");
    printf("*    1. 初始化链栈     *    2. 输出链栈所有元素 *\n");
    printf("*    3. 入栈           *    4. 出栈             *\n");
    printf("*    5. 访问栈顶元素   *    6. 退出系统         *\n"); 
    printf("*******************************************************\n");
    
}

int input_n(){//选择模式
	int n;
    printf("\n请输入模式对应数字 (1-6): ");
    scanf("%d",&n);
    return n;
}


//结构体定义 
typedef int ElemType;//栈中元素的数据类型为int

    //链栈节点定义
    typedef struct StackNode{
        ElemType data;
        StackNode *next;
    }StackNode,*linkstackprt;

    //
    typedef struct LinkStack{
        linkstackprt top;//栈顶指针
        int count;//栈中元素个数
    }Linkstack;


//初始化空栈
void InitStack(LinkStack *S){
    LinkStack *S = (LinkStack*)malloc(sizeof(LinkStack)); // 分配空栈内存
    if (S == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    S->top = NULL;  // 栈顶指针置空
    S->count = 0;   // 元素计数清零
}


//输出链栈所有元素All
void All(LinkStack *S){
    StackNode *temp=S->top;

    if (S->count!=0){
        while(temp!=NULL){
            printf("%d ",temp->data);
            temp=temp->next;
        }
    }
    else printf("栈为空栈，输出失败！");
}


//入栈Push
void Push(LinkStack *S,ElemType e){
    StackNode *newnode=(StackNode*)malloc(sizeof(StackNode));//分配节点内存
    if (newnode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newnode->next=S->top;
    newnode->data=e;
    S->top=newnode;
    S->count++;
}


//出栈Pop
void Pop(LinkStack *S){
    if (S->count!=0){
        StackNode *temp=S->top;
        printf("%d ",temp->data);
        S->top=temp->next;
        S->count--;
        free(temp);
    }
    else printf("栈为空栈，出栈失败！");
}


//访问栈顶元素Get
void Get(LinkStack *S){
    if (S->count!=0){
       printf("%d ",S->top->data);
    }
    else printf("栈为空栈，访问失败！");
}

//链栈的销毁Dele
void Dele(LinkStack *S){
    while (S->count!=0){//遍历链栈
        StackNode *temp=S->top;
        S->top=temp->next;
        S->count--;
        free(temp);
    }
}


//主函数
int main()
{
    print_menu();
	int n=input_n();

    LinkStack *S;
    InitStack(S); //初始化空栈
	
	while (n!=1){
		printf("还未初始化链栈！");
		n=input_n();
	}

	if (n==1){//先输入数据至第一个节点以初始化链栈

        char flag;//结束创造节点的标志：y/n 
        do{
            int e0;
            printf("请输入数据：");
            scanf("%d",&e0);
            Push(S,e0);
            
	        printf("continue?(y/n):");
	        scanf(" %c",&flag);

        }while (flag=='y');
		
        n=input_n();
		while(n!=6){
	
			switch(n){
				case 2:
                    All(S);//输出链栈所有元素 
					n=input_n();
					break;
				case 3:
                    int e;
                    printf("请输入数据：");
                    scanf("%d",&e);
                    Push(S,e);//入栈
					n=input_n();
					break;
				case 4:
                    Pop(S);//出栈
					n=input_n();
					break;
				case 5:
                    Get(S);//访问栈顶元素
					n=input_n();
					break;
				case 6:
                    Dele(S);//链栈的销毁
					printf("链栈已销毁！");
					break;
			}
		}
	}
	return 0; 
}