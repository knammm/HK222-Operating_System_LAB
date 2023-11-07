#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char num1[50], operator, num2[50];
    double ans = 0;
    char ans_str[50] = "ANS";
    char store_str[50];
    double store = 0;

    FILE *saveans;
    if ((saveans = fopen("ans.txt", "r")) != NULL) {
        fscanf(saveans, "%s", store_str);
        store = atof(store_str);
        fclose(saveans);
    }

    printf(">> ");
    scanf("%s %c %s", num1, &operator, num2);

    while (strcmp(num1, "EXIT") != 0) {

        if (strcmp(num1, "ANS") == 0 && strcmp(num2, "ANS") == 0) {
            sprintf(num1, "%f", ans);
            sprintf(num2, "%f", ans);
        } else if (strcmp(num1, "ANS") == 0) {
            sprintf(num1, "%f", ans);
        } else if (strcmp(num2, "ANS") == 0) {
            sprintf(num2, "%f", ans);
        }

        if ((atof(num1) == 0 && num1[0] != '0') || (atof(num2) == 0 && num2[0] != '0'|| operator != '+' && operator != '-' && operator != '*' && operator != '/' && operator != '%')) {
            printf("SYNTAX ERROR\n");
        } 
         else if ((operator == '/' || operator == '%') && atof(num2) == 0) {
            printf("MATH ERROR\n");
        } else {
            double num1_val = atof(num1);
            double num2_val = atof(num2);
            double res;
            switch (operator) {
                case '+':
                    res = num1_val + num2_val;
                    break;
                case '-':
                    res = num1_val - num2_val;
                    break;
                case '*':
                    res = num1_val * num2_val;
                    break;
                case '/':
                    res = num1_val / num2_val;
                    break;
                case '%':
                    res = (int)num1_val % (int)num2_val;
                    break;
            }

            printf("%.2f\n", res);
            ans = res;

            saveans = fopen("ans.txt", "w");
            fprintf(saveans, "%.2f", ans);
            fclose(saveans);
        }

        printf(">> ");
        scanf("%s %c %s", num1, &operator, num2);
    }

    return 0;
}