//约瑟夫问题：从1开始报数，报到m就删除

#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
struct node
{
    int val;
    node* next;
    node* prev;
};
node* head;
void count_and_delete(int m)
{
    node* curr = head;
    for(int i = 1;i < m;i++)
    {
        curr = curr->next;
    }
    head = curr->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
}

int main()
{
    int n, m;
    cin >> n >> m;
    node* former;
    int first = 1;
    for(int i = 0;i < n;i++)
    {
        node* curr = new node;
        curr->val = i + 1;
        if(first)
        {
            first = 0;
            curr->next = curr;
            curr->prev = curr;
            head = curr;
            former = curr;
        }
        else
        {
            former->next->prev = curr;
            curr->next = former->next;
            former->next = curr;
            curr->prev = former;
            former = curr;
        }
    }
    while(head->next != head)
    {
        count_and_delete(m);
    }
    cout << head->val<<'\n';
    delete head;
    return 0;
}