//单链表的多项式
#include<iostream>
#include<cstdio>
#include<cassert>
using namespace std;
struct node
{
    int coef;
    int exp;
    node* next;
};
node* create_node(int coef, int exp, node* prev)
{
    node* temp = new node;
    temp->exp = exp;
    temp->coef = coef;
    temp->next = nullptr;
    prev->next = temp;
    return temp;
}
void delete_list(node* dummy)
{
    while(dummy->next)
    {
        node* temp = dummy->next;
        dummy->next = dummy->next->next;
        delete temp;
    }
}
int main()
{

    int n, m;
    cin >> n >> m;
    node x;
    x.next = nullptr;
    node* a = &x;
    node* prev = a;
    for(int i = 0; i < n;i++)
    {
        node* temp = new node;
        cin >> temp->coef >> temp->exp;
        temp->next = nullptr;
        prev->next = temp;
        prev = temp;
    }
    node y;
    y.next = nullptr;
    node* b = &y;
    prev = b;
    for(int i = 0; i < m;i++)
    {
        node* temp = new node;
        cin >> temp->coef >> temp->exp;
        temp->next = nullptr;
        prev->next = temp;
        prev = temp;
    }
    node* a_head = a;
    node* b_head = b;
    node z;
    z.next = nullptr;
    node* c = &z;
    node* c_head = c;
    prev = c;
    a = a->next;
    b = b->next;
    while(a && b)
    {
        if(a->exp < b->exp)
        {
            prev = create_node(a->coef, a->exp, prev);
            a = a->next;
        }
        else if(a->exp == b->exp)
        {
            int coef_sum = a->coef + b->coef;
            if(!coef_sum)
            {
                a = a->next;
                b = b->next;
                continue;
            }
            prev = create_node(coef_sum, a->exp, prev);
            a = a->next;
            b = b->next;
        }
        else
        {
            prev = create_node(b->coef, b->exp, prev);
            b = b->next;
        }
    }
    while(a)
    {
        prev = create_node(a->coef, a->exp, prev);
        a = a->next;
    }
    while(b)
    {
        prev = create_node(b->coef, b->exp, prev);
        b = b->next;
    }
    while(c->next)
    {
        cout << c->next->coef << ' ' << c->next->exp << '\n';
        c = c->next;
    }
    delete_list(a_head);
    delete_list(b_head);
    delete_list(c_head);


    return 0;
}