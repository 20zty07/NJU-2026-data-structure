//双栈共享一个栈空间的判满、判空、入栈、出栈

#include<cstdio>
#include<iostream>
#include<cassert>
using namespace std;
#define max_size 100
int stack[100005];
int b[2] = {-1, max_size};
int t[2] = {-1, max_size};
int is_single_empty(int stack_num)
{
    return t[stack_num] == max_size;

}
int is_all_empty()
{
    return is_single_empty(0) && is_single_empty(1);
}
int is_full()
{
    return t[0] + 1 == t[1];
}
void push(int stack_num, int val)  //opposite
{
    assert(!is_full());
    if(stack_num)
    {
        t[stack_num]--;
    }
    else
    {
        t[stack_num]++;
    }
    stack[t[stack_num]] = val;
}
int pop(int stack_num)  //opposite
{
    assert(!is_single_empty(stack_num));
    int record = stack[t[stack_num]];
    if(stack_num)
    {
        t[stack_num]++;
    }
    else
    {
        t[stack_num]--;
    }
    return record;
}
int main()
{


    return 0;
}