#include<stdio.h>
#include<string.h>

char number1[1000000] = {0};
char number2[1000000] = {0};
char subtemp[1000000]={0};
int addnumber1[1000000] = {0};
int addnumber2[1000000] = {0};
int addanswer[1000000] = {0};
int subnumber1[1000000]={0};
int subnumber2[1000000]={0};
int subanswer[1000000]={0};
 
int main() {
    scanf("%s %s", number1, number2);
   
    int len1 = strlen(number1);
    int len2 = strlen(number2);
    
    for (int i=0; i<len1; i++) {
        addnumber1[i] = number1[len1-i-1] - '0';
    }
 
    for (int i=0; i<len2; i++) {
        addnumber2[i] = number2[len2-i-1] - '0';
    }
 
    int carry=0;
    int max=len1;
    if(len2>len1){
        max=len2;
    }
    
    int addlen=max+1;
    
    for (int i=0; i<addlen; i++) {
        addanswer[i] = addnumber1[i] + addnumber2[i] + carry;
        carry = addanswer[i] / 10;
        addanswer[i] %= 10;
    }
 
    for (int i=addlen-1; i>=0; i--) {
        if (0==addanswer[i] && addlen>1) {
            addlen--;
        } else {
            break;
        }
    }
 
    for (int i=addlen-1; i>=0; i--) {
        printf("%d", addanswer[i]);
    }
    printf("\n");    
    

    if ((len1<len2) || (len1==len2 && strcmp(number1,number2)<0)) {
        printf("-");
        strcpy(subtemp, number1);
        strcpy(number1, number2);
        strcpy(number2, subtemp);
        len1 = strlen(number1);
        len2 = strlen(number2);
    }
    for (int i=0; i<len1; i++) {
        subnumber1[i] = number1[len1-i-1] - '0';
    }
    for (int i=0; i<len2; i++) {
        subnumber2[i] = number2[len2-i-1] - '0';
    }
    for (int i=0; i<len1; i++) {
        if (subnumber1[i]<subnumber2[i]) {
            subnumber1[i+1]--;
            subnumber1[i] += 10;
        }
        subanswer[i] = subnumber1[i] - subnumber2[i];
    }
    for (int i=len1-1; i>=0; i--) {
        if (0==subanswer[i] && len1>1) {
            len1--;
        } else {
            break;
        }
    }
    for (int i=len1-1; i>=0; i--) {
        printf("%d", subanswer[i]);
    }
    printf("\n");
 
    return 0;
}
