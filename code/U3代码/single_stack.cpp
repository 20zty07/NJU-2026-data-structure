//单个栈一个栈空间的判满、判空、入栈、出栈

#include<cstdio>
#include<iostream>
#include<cassert>
using namespace std;
#define max_size 100
int stack[100005];
int top;
int is_empty()
{
    return top == 0;
}
int is_full()
{
    return top == max_size;
}
void push(int val)
{
    assert(!is_full());
    stack[top] = val;
    top++;
}
int pop()
{
    assert(!is_empty());
    int record = stack[top - 1];
    top--;
    return record;
}
int main()
{
    int n;
    cin >> n;
    for(int i = 0;i < n;i++)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int val;
            cin >> val;
            push(val);
        }
        else
        {
            cout << pop();
        }
    }

    return 0;
}