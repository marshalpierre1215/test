#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct linestack{		// linestack�������͵Ľṹ��͹��������ջ�Ļ�����λ 
        int data;
        struct linestack *next;
}linestack;

void displaystack(linestack*stack){
    linestack*p=stack;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

linestack* intostack(linestack* stack,int a){
    linestack *line=(linestack*)malloc(sizeof(linestack));		// ��ΪҪ��ջ, ���Ը�����ջ��Ԫ��Ҫ����һ���µ��ڴ�ռ䣻
    //line���´����Ŀռ�����֣�����Ϊ linestack*, ˵�����ռ�洢��������Ϊlinestack �ĵ�ַ��linkstack���͵ı���������о����ֵ)  
    line->data=a;		//linestack �ǽṹ��ָ��, ����Ҫ�� -> ������ . 
    line->next=stack;		// ��һ��ִ��ʱ stack �ĳ�ʼֵΪ NULL, line �Ǵ�ʱ��ջ��Ԫ��, line->next=stack ���ǰ�ջ��Ԫ�ص�ָ����Ϊ NULL,  	 
    stack=line;			// stack ��ͷָ�룬�����洢 NULL(ջ��û��Ԫ��ʱ)������һ���ṹ��ָ��ĵ�ַ(ջ����Ԫ��ʱ) 
    printf("The current stack is:");
    displaystack(stack);
    return stack;
}
linestack* outofstack(linestack*stack){
    if(stack!=NULL){	// �ж�ͷָ��ָ����Ƿ�Ϊ�� 
       printf("The element that was pushed is %d\n", stack->data);
       stack=stack->next;
       if(stack!=NULL){		// �жϵ���Ԫ�غ�ͷָ��ָ����Ƿ�ͱ�Ϊ����  
            printf("The current stack is:");
            displaystack(stack);
       }else{		// ����Ԫ�غ�ͷָ��ָ���Ϊ��
            printf("The stack is empty stack now!\n");
       }
    }else{		// ͷָ��ָ���Ϊ�� 
        printf("The stack is empty stack!\n");
    }
    return stack;
}
void viewtopelem(linestack*stack){		
    if(stack!=NULL){	// ����ͷָ��Ҫ�����е�ַ�ſ������Ԫ�� 
       printf("The top element of the stack is %d\n", stack->data);
    }else{
        printf("The stack is empty stack!\n");
    }
}

int main(){
    linestack *stack=NULL;
    printf("There are four kinds of command(exit,push,pop,top).\n");	// ��ʾ�� �����û�֪������ջ�ľ��巽�� 
    while(1){
        char command[10];
        int elem;
        printf("Please input the command:");
        scanf("%s",command);
        if(strcmp(command,"exit")==0){		//�˳����� 
            break;
        }
        if(strcmp(command,"push")==0){		// ��ջ 
            scanf("%d",&elem);
            stack=intostack(stack,elem);
        }
        if(strcmp(command,"pop")==0){		// ��ջ 
            stack=outofstack(stack);
        }
        if(strcmp(command,"top")==0){		// �鿴ջ��Ԫ�� 
            viewtopelem(stack);
        }

    }
    return 0;
}
