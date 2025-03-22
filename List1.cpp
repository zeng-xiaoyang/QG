#include <stdio.h>
#include <stdlib.h>
#define len sizeof(struct note)

void print_menu() {
	
    printf("*******************************************************\n");
    printf("*    1. 初始化链表    *    2. 输出链表     *\n");
    printf("*    3. 插入新节点    *    4. 删除节点     *\n");
    printf("*    5. 查询链表      *    6. 退出系统     *\n"); 
    printf("*******************************************************\n");
    
}

int input_n(){
	int n;
    printf("\n请输入对应数字 (0-6): ");
    scanf("%d",&n);
    return n;
}

//结构体定义
struct note{
	int std_num;
	int score;
	char grade;
	struct note*next;
}; 

//单链表的输出函数 
void list_print(struct note *head){
	struct note *p;
	p=head;
	 
	printf("\n当前的链表数据如下:\n");//打印单链表数据
	while(p!=NULL){
		printf("%d %d %c\n",p->std_num,p->score,p->grade);
		p=p->next;
	}
}
//单链表的生成 
struct note *head_position()//动态链表的创建，该函数返回一个头指针 
{
	struct note data,*head,*p1,*p2;
	p2=p1=(struct note*)malloc(len);
	printf("\n（至少输入三次节点的数据）\n");
	printf("请分别输入他的学号、成绩、等级(eg:\"xx xx x\"):");
	scanf("%d %d %c",&p1->std_num,&p1->score,&p1->grade);
	
	head=p1;
	
	char flag;//结束创造节点的标志：y/n 
	printf("continue?(y/n):");
	scanf(" %c",&flag);

	while(flag=='y'){
		
		p1=(struct note*)malloc(len);
		p2->next=p1;
		p2=p1;
		
		printf("分别输入他的学号、成绩、等级(eg:\"xx xx x\"):");
		scanf("%d %d %c",&p1->std_num,&p1->score,&p1->grade);
		printf("continue?(y/n):");
		scanf(" %c",&flag);
	}
	
	p2->next=NULL;
	return head;
}


//单链表的【插入】函数 
void list_new(struct note *head){ 
	
		struct note *newlist;
		newlist=(struct note*)malloc(len);
		
		printf("\n请选择在头部/中间/尾部插入数据(请对应输入1/2/3)：");
		int sign1;//插入位置的标志
		scanf("%d",&sign1);
		printf("请输入数据：");
		scanf("%d %d %c",&newlist->std_num,&newlist->score,&newlist->grade);
		
		switch(sign1){
		case 1:
			newlist->next=head;
			head=newlist;
			break;
		case 2:
			printf("请选择在第几个数据前插入该数据：");
			int sign2;//插入中间某位置的标志
			scanf("%d",&sign2);
			
			int i;
			struct note *q1,*q2;
			q1=q2=head;
			
			for(i=1;i<sign2;i++){//插入的后一个指针 
				q1=q1->next;
			}
			for(i=1;i<sign2-1;i++){//插入的前一个指针 
				q2=q2->next;
			}
			
			newlist->next=q1;
			q2->next=newlist;
			
			break;
		case 3:
			struct note *q3;
			q3=head;
			
			while(q3!=NULL){
				q3=q3->next;
			}
			
			q3=newlist;
			newlist->next=NULL;
			
			break;
		}
	
	printf("\n插入过后的链表内容如下：\n");
	struct note *pp1;
	pp1=head;
	while(pp1!=NULL){
		printf("%d %d %c\n",pp1->std_num,pp1->score,pp1->grade);
		pp1=pp1->next;
	}
}

//单链表的【删除】 函数 
void list_dele(struct note *head)
{
		printf("\n请选择在头部/中间/尾部删除数据(请对应输入1/2/3)：");
		int flag1;//插入位置的标志
		scanf("%d",&flag1);
		
		switch(flag1){
		case 1:
			struct note *u;
			u=head;
			head=head->next;
			free(u);
			break;
		case 2:
			printf("请选择删除第几个数据：");
			char flag2;//插入中间某位置的标志
			scanf("%d",&flag2);
	
			struct note *u1,*u2,*u3;
			u1=u2=u3=head;
			
			int j;
			for(j=0;j<flag2;j++){//删除的后一个指针 u1
				u1=u1->next;
			}
			for(j=0;j<flag2-1;j++){//删除的那个指针 u2
				u2=u2->next;
			}
			for(j=0;j<flag2-2;j++){//删除的前一个指针 u3
				u3=u3->next;
			}
			
			u3->next=u1;
			u2->next=NULL;
			free(u2);
			break;
		case 3:
			struct note *q3;
			q3=head;
			
			while(q3->next->next!=NULL){
				q3=q3->next;
			}
			
			free(q3->next->next);
			q3->next=NULL;
			break;
		
	}
	
	printf("\n删除过后的链表内容如下：\n");
	struct note *pp2;
	pp2=head;
	while(pp2!=NULL){
		printf("%d %d %c\n",pp2->std_num,pp2->score,pp2->grade);
		pp2=pp2->next;
	}
} 

//单链表的【查找】函数 
void list_search(struct note *head)
{
	int num;
	int k=0;
	printf("\n请输入你要查找的第几个数据:");
	scanf("%d",&num);
	
	struct note *pp3;
	pp3=head;
	for(k=1;k<num;k++){
		pp3=pp3->next;
	}
	printf("\n您所需查找的链表内容如下：\n");
	printf("\n%d %d %c\n",pp3->std_num,pp3->score,pp3->grade);
}

//单链表的【销毁】函数 
void list_delete(struct note *head)
{
	struct note *p=head;
	printf("%p\n",p);
	struct note *t;
	
	while(p!=NULL){
		t=p;
		p=p->next;
		free(t);
		}
	printf("%p\n",p);
	printf("%p",head);
	
	if (head == NULL)
        printf("链表头指针已置空，销毁成功！\n");
    else 
        printf("链表未被完全销毁！\n");
	
}

//【主函数】 //
int main(){
	
	print_menu();
	int n=input_n();
	
	while (n!=1){
		printf("还未初始化链表！");
		n=input_n();
	}
	if (n==1){
		struct note *p=head_position();
		struct note *head=p;
	
		n=input_n();
		
		while(n!=6){
	
			switch(n){
				case 2:
					list_print(head);//单链表的输出打印 
					n=input_n();
					break;
				case 3:
					list_new(head);//单链表的插入
					n=input_n();
					break;
				case 4:
					list_dele(head);//单链表的删除
					n=input_n();
					break;
				case 5:
					list_search(head);//单链表的查找
					n=input_n();
					break;
				case 6:
					list_delete(head);//单链表的销毁
					printf("链表已销毁！");
					break;
			}
		}
	}
	
	return 0; 
}