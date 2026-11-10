//静态链表的建立与插入

#include<cstdio>
#include<iostream>
using namespace std;
struct snode
{
    int data;
    int next;
};
snode node[100005];
int head = 0;
int top = 1;;

void insert(int id, int val)
{
    if(id == 1)
    {
        node[top].data = val;
        node[top].next = node[head].next;
        node[head].next = top;
        top++;
        return;
    }
    node[top].data = val;
    int prev = head;
    for(int i = 1;i < id;i++)
    {
        prev = node[prev].next;
    }
    node[top].next = node[prev].next;
    node[prev].next = top;
    top++;
}

int main()
{
    int n;
    cin >> n;
    node[0].next = 1;
    for(int i = 1;i <= n;i++)
    {
        cin >> node[top].data;
        if(i == n)
        {
            node[top].next = -1;
            top++;
            break;
        }
        node[top].next = top + 1;
        top++;
    }
    int id, val;
    cin >> id >> val;
    insert(id, val);
    for(int i = 1;i != -1;i = node[i].next)
    {
        cout << node[i].data<<' ';
    }

    return 0;
}