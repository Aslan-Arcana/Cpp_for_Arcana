#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ���������ջ
typedef struct{
    char data[100];
    int top;
} OperatorStack;

OperatorStack s;

// ��ʼ��ջ
void initStack(){
    s.top = 0;
}

// ��ջ
int Push(char opt){
    if ( s.top == 100 ) {
        return -1;
    }
    s.data[s.top] = opt;
    s.top++;

    return 1;
}

// ��ջ
int Pop(){
    if ( s.top == 0 ) {
        return -1;
    }

    s.data[s.top - 1] = '\0';
    s.top--;
    return 1;
}

// ��ȡջ��Ԫ�أ���ջ��Ԫ�س�ջ
char Peek(){
    if ( s.top == 0 ) {
        return '\0';
    }

    char e = s.data[s.top - 1];
    s.data[s.top - 1] = '\0';
    s.top--;
    return e;
}

// ��ȡջ��Ԫ�ص������г�ջ
char getEleTop(){
    if ( s.top == 0 ) {
        return '\0';
    }

    char e = s.data[s.top - 1];
    return e;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(){
    if ( s.top > 0 ) {
        return 0;
    }

    return 1;
}

// �ж���������ȼ�
int opt(char signal){
    if ( signal == '+' || signal == '-' ) {
        return 1;
    } else if ( signal == '*' || signal == '/' ) {
        return 2;
    }
    return 0;
}

// ������ʽ�洢�ṹջ
typedef struct Node{
    int data;
    struct Node * next;
} Node;

// ����ָ����������
typedef struct Node * LinkList;

// ����һ��ָ��ջ��Ԫ��ָ��
LinkList top;

// ��ʼ��ָ�����
void initNumStack(){
    top = (LinkList)(malloc(sizeof(Node)));
    top -> next = NULL;
}

// ������ջ
void PushNum(int data){
    LinkList node = (LinkList)(malloc(sizeof(Node)));
    node -> data = data;
    node -> next = top -> next;
    top -> next = node;
}

// ���ֻ�ȡջ��Ԫ�ز���ջ
int PeekNum(){
     LinkList topEle = top -> next;
     int data = topEle -> data;
     top -> next = topEle -> next;
     free(topEle);
     return data;
}

// �жϸ�ջ�Ƿ�Ϊ��
int isEmptyNum(){
    if (top -> next == NULL ) {
        return 1;
    }
    return 0;
}

// ջ��Ԫ�ؽ��в���������
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

// �ж������Ƿ�Ϸ�
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
    printf("���룺");
    scanf("%s", express);
    int valid = isValid(express);
    if ( valid == 0 ) {
        printf("���벻�Ϸ�");
        return 0;
    }
    int i;
    for ( i = 0; i < strlen(express); i++ ) {
        
        if ( express[i] == '+' 
            || express[i] == '-' && i != 0 && express[i - 1] >= '0' && express[i - 1] <= '9'    //ʹ�����������
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
                if ( express[i + j] >= '0' && express[i + j] <= '9' || express[i + j] == '.' ) {    //�˴�ע�Ͳ���ʵ���ϲ����˸��������㣬��ʵ��δ�漰
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
            int value = atoi(num);  //�˴�����ͨ����atoi()������Ϊatof()�����Ӷ�ʵ�ָ����������㣬��ʵ��Ҫ��δ�����������ʽ��������һ���������ã�δʵ�ʲ���
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