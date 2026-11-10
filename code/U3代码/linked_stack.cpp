#include<cstdio>
#include<iostream>
#include<cassert>  
using namespace std;
struct  node
{
    int val;
    node*next;
};
node* top;

int is_empty()
{
    return top == nullptr;
}
void push(int val)
{
    node* temp = new node;
    temp->val = val;
    temp->next = top;
    top = temp;
}
void pop()
{
    assert(!is_empty());
    node* record = top;
    top = top->next;
    cout << record->val;
    delete record;
}

void make_empty()
{
    while(top)
    {
        node* temp = top;
        top = top->next;
        delete temp;
    }
}
int main()
{


    return 0;
}