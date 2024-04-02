#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct linestack{		// linestack这中类型的结构体就构成了组成栈的基本单位 
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
    linestack *line=(linestack*)malloc(sizeof(linestack));		// 因为要入栈, 所以给新入栈的元素要分配一个新的内存空间；
    //line是新创建的空间的名字，类型为 linestack*, 说明这块空间存储的是类型为linestack 的地址（linkstack类型的变量里面才有具体的值)  
    line->data=a;		//linestack 是结构体指针, 所以要用 -> 而不用 . 
    line->next=stack;		// 第一次执行时 stack 的初始值为 NULL, line 是此时的栈顶元素, line->next=stack 就是把栈顶元素的指针设为 NULL,  	 
    stack=line;			// stack 是头指针，用来存储 NULL(栈内没有元素时)或者下一个结构体指针的地址(栈内有元素时) 
    printf("The current stack is:");
    displaystack(stack);
    return stack;
}
linestack* outofstack(linestack*stack){
    if(stack!=NULL){	// 判断头指针指向的是否为空 
       printf("The element that was pushed is %d\n", stack->data);
       stack=stack->next;
       if(stack!=NULL){		// 判断弹出元素后头指针指向的是否就变为空了  
            printf("The current stack is:");
            displaystack(stack);
       }else{		// 弹出元素后头指针指向的为空
            printf("The stack is empty stack now!\n");
       }
    }else{		// 头指针指向的为空 
        printf("The stack is empty stack!\n");
    }
    return stack;
}
void viewtopelem(linestack*stack){		
    if(stack!=NULL){	// 首先头指针要保存有地址才可能输出元素 
       printf("The top element of the stack is %d\n", stack->data);
    }else{
        printf("The stack is empty stack!\n");
    }
}

int main(){
    linestack *stack=NULL;
    printf("There are four kinds of command(exit,push,pop,top).\n");	// 提示词 便于用户知道操作栈的具体方法 
    while(1){
        char command[10];
        int elem;
        printf("Please input the command:");
        scanf("%s",command);
        if(strcmp(command,"exit")==0){		//退出程序 
            break;
        }
        if(strcmp(command,"push")==0){		// 入栈 
            scanf("%d",&elem);
            stack=intostack(stack,elem);
        }
        if(strcmp(command,"pop")==0){		// 出栈 
            stack=outofstack(stack);
        }
        if(strcmp(command,"top")==0){		// 查看栈顶元素 
            viewtopelem(stack);
        }

    }
    return 0;
}
