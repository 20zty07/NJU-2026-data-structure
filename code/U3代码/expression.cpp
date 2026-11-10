#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<math.h>
using namespace std;

//优先级表
int priority(char curr)
{
    if(curr == '+' || curr == '-')
    {
        return 1;
    }
    else if(curr == '*' || curr == '/')
    {
        return 2;
    }
    else if(curr == '^') 
    {
        return 3;
    }
    else if(curr == '~')
    {
        return 4;
    }
    else    //左括号调用该函数时一定在栈中
    {
        return 0;
    }
}

//后缀表达式的计算
//表达式中的每个数字均为一位数字，即取值范围为 0 到 9
int calculate_profix(char *s)  //特别要注意，后缀表达式AB-的意思是A-B！不是B-A!
{
    int num[100005] = {0};
    int top = 0;
    int l = strlen(s);
    for(int i = 0;i < l;i++)
    {
        char curr = s[i];
        if(curr >= '0' && curr <= '9')
        {
            num[top] = curr - '0';  //入栈不能写num[i]!
            top++;
        }
        else
        {
            switch (curr)
            {
            case '+':
                num[top - 2] = num[top - 2] + num[top - 1];
                top--;
                break;
            case '-':
                num[top - 2] = num[top - 2] - num[top - 1];
                top--;
                break;
            case '*':
                num[top - 2] = num[top - 2] * num[top - 1];
                top--;
                break;
            case '/':
                num[top - 2] = num[top - 2] / num[top - 1];
                top--;
                break;  
            case '^':
                num[top - 2] = pow(num[top - 2], num[top - 1]);
                top--;
                break; 
            case '~':
                num[top - 1] = -num[top - 1];
                break;                                          
            default:
                break;
            }
        }
    }
    return num[0];
}

//中缀表达是转化为后缀表达式
//表达式中的每个数字均为一位数字，即取值范围为 0 到 9
//输入示例：1/(2+3)  输出示例：123+/
char postfix[100005];
char infix[100005];
void infix_to_postfix()
{
    int i = 0;
    int top = 0;
    int post = 0;
    char stack[100005];
    int l = strlen(infix);
    while(i < l)
    {
        char curr = infix[i];
        if(curr >= '0' && curr <= '9')
        {
            while(infix[i] != ' ' && infix[i] >= '0' && infix[i] <= '9')
            {
                postfix[post] = infix[i];
                post++;
                i++;
            }
        }
        else if(curr == '(')
        {
            stack[top] = curr;
            top++;
            i++;
        }  
        else if(curr == ')')
        {
            while(top && stack[top - 1] != '(')
            {
                postfix[post] = stack[top - 1];
                post++;
                top--;
            }
            top--;  //跳过左括号
            i++;
        }
        else if(curr == '~')
        {
            stack[top] = curr;
            top++;
            i++;
        }
        else    //输入操作符
        {
            if(!top)
            {
                stack[top] = curr;
                top++;
            }
            else    //栈顶有操作符
            {
                int curr_op = priority(curr);
                while(top && ((priority(stack[top - 1]) > curr_op) || (curr != '^' && priority(stack[top - 1]) == curr_op)))
                //如果当前是^，只有遇到~才弹栈
                {
                    postfix[post] = stack[top - 1];
                    top--;
                    post++;
                }
                stack[top] = curr;
                top++;
            }
            i++;//从下一个数开始
        }
    }
    while(top)
    {
        postfix[post] = stack[top - 1];
        top--;
        post++;
    }
    postfix[post] = '\0';
    cout << postfix; //后缀表达式不含空格
}

//中缀表达式的计算：括号表达式 > ~ > ^ > * = / > + = -
//表达式中的每个数字均为一位数字，即取值范围为 0 到 9
char op[100005];
int num[100005];
int op_top = 0;
int num_top = 0;
void helper_pop_single()
{
    op_top--;
    char curr_op = op[op_top];
    if(curr_op == '~')
    {
        num_top--;
        long long int temp = num[num_top];
        num[num_top] = -temp;
        num_top++;
    }
    else
    {
        num_top--;
        long long int latter = num[num_top];
        num_top--;
        long long int former = num[num_top];
        if(curr_op == '+')
        {
            num[num_top] = former + latter;
        }
        else if(curr_op == '-')
        {
            num[num_top] = former - latter;
        }
        else if(curr_op == '*')
        {
            num[num_top] = former * latter;
        }
        else if(curr_op == '/')
        {
            num[num_top] = former / latter;
        }
        else
        {
            num[num_top] = pow(former,latter);
        }
        num_top++;
    }
}

int calculate_infix(char* s)
{
    int l = strlen(s);
    for(int i = 0;i < l;i++)
    {
        if(s[i] >='0' && s[i] <= '9')
        {
            num[num_top] = s[i] - '0';
            num_top++;
        }
        else
        {
            if(s[i] == '(')
            {
                op[op_top] = '(';
                op_top++;
            }
            else if(s[i] == ')')
            {
                while(op[op_top - 1] != '(')
                {
                    helper_pop_single();
                }
                op_top--;
            }
            else if(s[i] == '~')
            {
                op[op_top] = '~';
                op_top++;
            }
            else
            {
                while(op_top > 0 && op[op_top - 1] != '(')
                {
                    op_top--;
                    char top = op[op_top];
                    char curr = s[i];
                    int top_prior = priority(top);
                    int curr_prior = priority(curr);
                    op_top++;
                    if(top_prior > curr_prior || (top_prior == curr_prior && curr != '^'))
                    {
                        helper_pop_single();
                    }
                    else
                    {
                        break;
                    }
                }
                op[op_top] = s[i];
                op_top++;
            }
        }
    }
    while(op_top > 0)
    {
        helper_pop_single();
    }
    return num[0];
}
