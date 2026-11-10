#include<iostream>
#include<stdio.h>
#include<cassert>
using namespace std;
//队列数组表示
//按照教材，push和pop操作的返回值都是bool，这里用assert防止false情况发生

int queue[100005];
#define max_size 100
int front;
int rear;
int is_queue_empty()
{
    return front == rear;
}
int is_full()
{
    return rear == max_size - 1;
}
int pop_front()
{
    assert(!is_queue_empty());
    int record = queue[front];
    front++;
    return record;
}
void push_rear(int val)
{
    assert(!is_full());
    queue[rear] = val;
    rear++;
}
void pascal_triangle(int n)
{
    push_rear(1);
    push_rear(1);
    int s = 0;
    int t = pop_front();
    for(int i = 2;i <= n;i++) //从第二行开始
    {
        push_rear(0);
        for(int j = 1;j <= i + 1;j++)   //第i行有i+1个数字
        {
            push_rear(s + t);
            s = t;
            t = pop_front();
        }
    }
    int top = 0;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= i+2;j++)
        {
            cout << queue[top] << ' ';
            top++;
        }
        cout << '\n';
    }
}



int loop_queue[100005];
#define max_size 100
int loop_front;
int loop_rear;
int is_loop_empty()
{
    return front == rear;
}
int is_loop_full()
{
    return (rear + 1) % max_size == front;
}
int pop_loop_front()
{
    assert(!is_loop_empty());
    int record = queue[front];
    front = (front + 1) % max_size;
    return record;
}
int get_size()
{
    return (rear - front + max_size) % max_size;
}

void push_loop_rear(int val)
{
    assert(!is_full());
    queue[rear] = val;
    rear = (rear + 1) % max_size;
}

struct node
{
    int val;
    node* next;
};
node* nfront;
node* nrear;
int is_link_empty()
{
    return nfront == nrear;
}
int pop_link_front()
{
    assert(!is_link_empty());
    int record = nfront->val;
    node* temp = nfront;
    nfront = nfront->next;
    delete temp;
    return record;
}
void push_link_record(int val)
{
    node* temp = new node;
    temp->val = val;
    temp->next = nullptr;
    nrear->next = temp;
    nrear = nrear->next;
}

int main()
{
    pascal_triangle(5);
    return 0;
}