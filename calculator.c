#include<stdio.h>

int main(){
    double num1, num2, result;
    char op;
    char count = 'y';

    while (count == 'y' || count == 'Y'){

    printf("\n\n A SIMPLE CALCULATOR PROGRAM ...\n\n");

    printf("Enter first number: ");
    scanf("%lf", &num1);

    printf("Enter operator: ('+','-', '*', '/' ): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%lf", &num2);

    if(op == '+'){
        result = num1 + num2;
        printf("%.3lf + %.3lf = %.3lf", num1, num2, result);

    }
    else if(op == '-'){
       result = num1 - num2;
       printf("%.3lf - %.3lf = %.3lf", num1, num2, result);
    }
    
    else if(op == '/'){
        if(num2 == 0){
            
            printf("UNDEFINED");
        }
        else{
        result = num1 / num2;
        printf("%.3lf / %.3lf = %.3lf", num1, num2, result);
        }

    }
    else if(op == '*'){
       result = num1 * num2;
       printf("%.3lf * %.3lf = %.3lf", num1, num2, result);
    }
    else{
        printf("INVALID OPERATOR");
    }

    printf("\n\n Do you want to continue? (y/n): ");
    scanf(" %c", &count);
    }
   
    return 0;
}