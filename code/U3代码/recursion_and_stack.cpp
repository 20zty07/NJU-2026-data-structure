/*  递归与栈
    Procedure <name> ( <parameter list> ) 
    {
       if ( < initial condition> )    //递归结束条件
         return ( initial value );    
       else                                      //递归
         return (<name> ( parameter exchange ));
    }
*/

#include<cstdio>
#include<iostream>
#include<cassert>  
using namespace std;

struct node
{
    node* next;
    int val;
};
void print_last_node(node* curr)
{
    assert(curr != nullptr);
    if(curr->next)
    {
        print_last_node(curr->next);
    }
    else
    {
        cout << curr->val <<'\n';
    }
}
//将cnt各盘子从a借助b移动到c
void tower_of_hanoi(int cnt, int a, int b, int c)
{
    if(cnt == 1)
    {
        cout << "move "<< a << " to " << c << '\n';
        return;
    }
    tower_of_hanoi(cnt - 1, a, c, b);
    cout << "move "<< a << " to " << c << '\n';
    tower_of_hanoi(cnt - 1, b, a, c);
}

int fib(int n)
{
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}
int fib_while(int n)
{
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    int n_1 = 1;
    int n_2 = 0;
    int ans;
    for(int i = 2;i <= n;i++)
    {
        ans = n_1 + n_2;
        n_2 = n_1;
        n_1 = ans;
    }
    return ans;
}

//输入n，意思是按照a_1 a_2 a_3……a_n入栈，有几种出栈方式？
int pop_cnt(int n)
{
    if(n == 0)
    {
        return 1;
    }
    int ans = 0;
    for(int i = 0;i < n;i++)
    {
        ans += pop_cnt(i) * pop_cnt(n - 1 - i);
        //以第一个元素为参考，后面n-1个元素如何划分出栈
    }
    return ans;
}

long long record[36] = {1}; //36是为了防止超出long long
long long int pop_cnt_cache(int n)
{
    if(record[n])
    {
        return record[n];
    }
    for(int i = 0;i < n;i++)
    {
        if(!record[i])
        {
            record[i] = pop_cnt_cache(i);
        }
        if(!record[n - 1 - i])
        {
            record[n - 1 - i] = pop_cnt_cache(n - 1 - i);
        }
        record[n] += record[i] * record[n - 1 - i];
    }
    return record[n];
}