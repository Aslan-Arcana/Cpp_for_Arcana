#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义操作符栈
typedef struct{
    char data[100];
    int top;
} OperatorStack;

OperatorStack s;

// 初始化栈
void initStack(){
    s.top = 0;
}

// 入栈
int Push(char opt){
    if ( s.top == 100 ) {
        return -1;
    }
    s.data[s.top] = opt;
    s.top++;

    return 1;
}

// 出栈
int Pop(){
    if ( s.top == 0 ) {
        return -1;
    }

    s.data[s.top - 1] = '\0';
    s.top--;
    return 1;
}

// 获取栈顶元素，将栈顶元素出栈
char Peek(){
    if ( s.top == 0 ) {
        return '\0';
    }

    char e = s.data[s.top - 1];
    s.data[s.top - 1] = '\0';
    s.top--;
    return e;
}

// 获取栈顶元素但不进行出栈
char getEleTop(){
    if ( s.top == 0 ) {
        return '\0';
    }

    char e = s.data[s.top - 1];
    return e;
}

// 判断栈是否为空
int isEmpty(){
    if ( s.top > 0 ) {
        return 0;
    }

    return 1;
}

// 判断运算符优先级
int opt(char signal){
    if ( signal == '+' || signal == '-' ) {
        return 1;
    } else if ( signal == '*' || signal == '/' ) {
        return 2;
    }
    return 0;
}

// 定义链式存储结构栈
typedef struct Node{
    int data;
    struct Node * next;
} Node;

// 定义指针类型链表
typedef struct Node * LinkList;

// 定义一个指向栈顶元素指针
LinkList top;

// 初始化指针变量
void initNumStack(){
    top = (LinkList)(malloc(sizeof(Node)));
    top -> next = NULL;
}

// 数字入栈
void PushNum(int data){
    LinkList node = (LinkList)(malloc(sizeof(Node)));
    node -> data = data;
    node -> next = top -> next;
    top -> next = node;
}

// 数字获取栈顶元素并出栈
int PeekNum(){
     LinkList topEle = top -> next;
     int data = topEle -> data;
     top -> next = topEle -> next;
     free(topEle);
     return data;
}

// 判断该栈是否为空
int isEmptyNum(){
    if (top -> next == NULL ) {
        return 1;
    }
    return 0;
}

// 栈顶元素进行操作符运算
int caculateTopTwoEle(int firstValue, int secondValue, char signal){
    if ( signal == '+' ) {
        return secondValue + firstValue;
    } else if ( signal == '-' ) {
        return secondValue - firstValue;
    } else if ( signal == '*' ) {
        return secondValue * firstValue;
    } else if ( signal == '/' ) {
        return secondValue / firstValue;
    }

    return 0;
}

// 判断输入是否合法
int isValid(char express[]){
    initStack();
    for ( int i = 0; i < strlen(express); i++ ) {
        char c = express[i];
        if ( !(c >= '0' && c <= '9' || c == '(' || c == ')' 
        || c == '+' || c == '-' || c == '*' || c == '/' )) {
            return 0;
        }
        
        if ( express[i] == '(' ) {
            Push('(');
        } else if ( express[i] == ')' ) {
            if ( isEmpty() ) {
                return 0;
            }
            Pop();
        }
    }
    if ( !isEmpty() ) {
        return 0;
    }
    
    return 1;
}

int main(){
    initNumStack();
    char express[10000];
    printf("输入：");
    scanf("%s", express);
    int valid = isValid(express);
    if ( valid == 0 ) {
        printf("输入不合法");
        return 0;
    }
    int i;
    for ( i = 0; i < strlen(express); i++ ) {
        
        if ( express[i] == '+' 
            || express[i] == '-' && i != 0 && express[i - 1] >= '0' && express[i - 1] <= '9'    //使负数运算成立
            || express[i] == '*' || express[i] == '/' ) {
            if ( isEmpty() ) {
                Push(express[i]);
                continue;
            }

            char topEle = getEleTop();
            if ( topEle == '(' ) {
                Push(express[i]);
                continue;
            }

            while ( opt(topEle) >= opt(express[i]) ) {
                printf("%c ", Peek());
                int firstValue = PeekNum();
                int secondValue = PeekNum();
                int result = caculateTopTwoEle(firstValue, secondValue, topEle);
                PushNum(result);
                topEle = getEleTop();
            }

            Push(express[i]);
        } else if ( express[i] == '(' ) {
            Push(express[i]);
        } else if ( express[i] == ')' ) {
            char topEle = Peek();
            while ( topEle != '(' ) {
                printf("%c ", topEle);
                int firstValue = PeekNum();
                int secondValue = PeekNum();
                int result = caculateTopTwoEle(firstValue, secondValue, topEle);
                PushNum(result);
                topEle = Peek();
            }
        } else {
            char num[100];
            int index = 0;
            printf("%c", express[i]);
            num[index++] = express[i];
            int j;
            int isEnd = 0;
            for ( j = 1; i + j < strlen(express); j++ ) {
                if ( express[i + j] >= '0' && express[i + j] <= '9' || express[i + j] == '.' ) {    //此处注释部分实际上采用了浮点数运算，但实验未涉及
                    printf("%c", express[i + j]);
                    num[index++] = express[i + j];
                    if ( i + j == strlen(express) - 1 ) {
                        isEnd = 1;
                    }
                } else {
                    i = i + j - 1;
                    printf(" ");
                    break;
                }
            }
            num[index++] = '\0';
            int value = atoi(num);  //此处可以通过将atoi()函数改为atof()函数从而实现浮点数的运算，但实验要求未做浮点数，故仅添加了这一功能做调用，未实际采用
            PushNum(value);
            if ( isEnd ) {
                break;
            }
        }
    }

    while ( !isEmpty() ) {
        char topEle = Peek();
        int firstValue = PeekNum();
        int secondValue = PeekNum();
        int result = caculateTopTwoEle(firstValue, secondValue, topEle);
        PushNum(result);
        printf("%c ", topEle);
    }

    printf("=%d", PeekNum());

    return 0;
}