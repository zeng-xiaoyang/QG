#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 链栈节点定义（用于字符栈）
typedef struct StackNode {
    char data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

// 字符链栈结构
typedef struct LinkStack {
    LinkStackPtr top;
    int count;
} LinkStack;

// 初始化字符栈
LinkStack* InitCharStack() {
    LinkStack *S = (LinkStack*)malloc(sizeof(LinkStack));
    S->top = NULL;
    S->count = 0;
    return S;
}

// 判断运算符优先级
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    else if (op == '*' || op == '/') return 2;
    return 0;
}

// 字符入栈
void PushChar(LinkStack *S, char e) {
    StackNode *newnode = (StackNode*)malloc(sizeof(StackNode));
    newnode->data = e;
    newnode->next = S->top;
    S->top = newnode;
    S->count++;
}

// 字符出栈
char PopChar(LinkStack *S) {
    if (S->top == NULL) return '\0';
    StackNode *temp = S->top;
    char data = temp->data;
    S->top = temp->next;
    S->count--;
    free(temp);
    return data;
}

/*自己敲的，运行出现问题，未解决成功
//中缀表达式转后缀表达式的 入栈规定
void InfixToPostfix(LinkStack *S){
    char expression;

    do{
        scanf(" %c",&expression);

        if(expression == '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9' ){
            int num = expression -'0';//将字符型数字转换为int类型数字
            printf("%d ",num); 
        }
        else if(expression=='('){
            Push(S,expression);
        }

        else if(expression==')'){
            while(S->top->data!='('){
                Pop(S);
            }
            StackNode *temp2=S->top;//对于左括号的处理：不pop,直接出栈free掉
            S->top=temp2->next;
            S->count--;
            free(temp2);
        }
        else if(expression == '+'||'-'||'*'||'/'){
            
            if (JudgePriority(S)==1){//当当前运算符优先比栈顶的运算符高时 -> 当前运算符进栈
                StackNode *newnode=(StackNode*)malloc(sizeof(StackNode));//分配节点内存
                if (newnode == NULL) {
                    printf("内存分配失败！\n");
                    exit(1);
                }
                newnode->data=expression;
                newnode->next=S->top;
                S->top=newnode;
                S->count++;
            }
            else{//当当前运算符优先比栈顶的运算符低时 -> 栈顶运算符出栈，后，当前运算符不进栈而输出
                Pop(S);
                printf("%c",expression);
            }

            //最后将当前运算符入栈
            StackNode *newnode=(StackNode*)malloc(sizeof(StackNode));//分配节点内存
            if (newnode == NULL) {
                printf("内存分配失败！\n");
                exit(1);
            }
            newnode->next=S->top;
            newnode->data='(';
            S->top=newnode;
            S->count++;
        }
    }while(expression!='\n');
    
    //结束时把栈剩余的数据出栈到空为止
    Dele(S);
}
*/

// 学习AI的方法
// 中缀转后缀表达式并保存到数组
void Infix_To_Postfix(LinkStack *S, char *postfix) {
    char expression;
    int i = 0;

    printf("请输入中缀表达式：");
    while (scanf(" %c", &expression) == 1 && expression != '\n') {
        if (isdigit(expression)) {
            // 处理多位数
            while (isdigit(expression)) {
                postfix[i++] = expression;
                if (scanf("%c", &expression) != 1 || !isdigit(expression)) break;
            }
            postfix[i++] = ' ';
            if (expression == '\n') break; // 输入结束
        }
        if (expression == '(') {
            PushChar(S, '(');
        } 
        else if (expression == ')') {
            while (S->top != NULL && S->top->data != '(') {
                postfix[i++] = PopChar(S);
                postfix[i++] = ' ';
            }
            if (S->top == NULL) {
                printf("括号不匹配！\n");
                exit(1);
            }
            PopChar(S); // 弹出左括号
        } 
        else if (expression == '+' || expression == '-' || expression == '*' || expression == '/') {
            while (S->top != NULL && S->top->data != '(' && 
                   getPriority(S->top->data) >= getPriority(expression)) {
                postfix[i++] = PopChar(S);
                postfix[i++] = ' ';
            }
            PushChar(S, expression);
        }
    }
    // 弹出栈中剩余运算符
    while (S->top != NULL) {
        if (S->top->data == '(') {
            printf("括号不匹配！\n");
            exit(1);
        }
        postfix[i++] = PopChar(S);
        postfix[i++] = ' ';
    }
    postfix[i] = '\0'; // 字符串结束符
}

// 整数栈定义
typedef struct IntStackNode {
    int data;
    struct IntStackNode *next;
} IntStackNode, *IntLinkStackPtr;

typedef struct IntLinkStack {
    IntLinkStackPtr top;
    int count;
} IntLinkStack;

// 初始化整数栈
IntLinkStack* InitIntStack() {
    IntLinkStack *S = (IntLinkStack*)malloc(sizeof(IntLinkStack));
    S->top = NULL;
    S->count = 0;
    return S;
}

// 整数入栈
void PushInt(IntLinkStack *S, int e) {
    IntStackNode *newnode = (IntStackNode*)malloc(sizeof(IntStackNode));
    newnode->data = e;
    newnode->next = S->top;
    S->top = newnode;
    S->count++;
}

// 整数出栈
int PopInt(IntLinkStack *S) {
    if (S->top == NULL) {
        printf("栈空，无法计算\n");
        exit(1);
    }
    IntStackNode *temp = S->top;
    int data = temp->data;
    S->top = temp->next;
    S->count--;
    free(temp);
    return data;
}

// 计算后缀表达式
int evaluatePostfix(const char *postfix) {
    IntLinkStack *stack = InitIntStack();
    char *token;
    char *input = strdup(postfix); // 复制字符串避免修改原数据

    token = strtok(input, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            PushInt(stack, atoi(token));
        } else {
            int b = PopInt(stack);
            int a = PopInt(stack);
            switch (token[0]) {
                case '+': PushInt(stack, a + b); break;
                case '-': PushInt(stack, a - b); break;
                case '*': PushInt(stack, a * b); break;
                case '/': 
                    if (b == 0) {
                        printf("除零错误\n");
                        exit(1);
                    }
                    PushInt(stack, a / b);
                    break;
                default:
                    printf("无效运算符: %c\n", token[0]);
                    exit(1);
            }
        }
        token = strtok(NULL, " ");
    }

    free(input);
    if (stack->count != 1) {
        printf("无效表达式\n");
        exit(1);
    }

    int result = PopInt(stack);
    free(stack);
    return result;
}

// 主函数
int main() {
    LinkStack *charStack = InitCharStack();
    char postfix[1000];
    Infix_To_Postfix(charStack, postfix);
    printf("后缀表达式: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("计算结果: %d\n", result);

    free(charStack);
    return 0;
}