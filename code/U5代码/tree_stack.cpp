//树的函数非递归写法
//可用nullptr放在栈开头表示停止（不推荐）
//可用 curr||top 表示循环结束

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
using namespace std;
struct node
{
    char val;
    node* left;
    node* right;
};
node* stack[100005];
int top;
node* create_prefix() //空结点当成‘@’节点
{
    char val;
    cin >> val;
    if(val == '@')
    {
        return nullptr;
    }
    node* root = new node;
    root->val = val;
    root->left = nullptr;
    root->right = nullptr;
    stack[top] = root;
    top++;
    node* curr = root;
    while(top)
    {
        char v;
        cin >> v;
        node* temp = new node;
        temp->val = v;
        temp->left = nullptr;
        temp->right = nullptr;
        if(!stack[top - 1]->left)
        {
            stack[top - 1]->left = temp;
        }
        else
        {
            stack[top - 1]->right = temp;
            top--;
        }
        if(v != '@')
        {
            stack[top] = temp;
            top++;
        }
    }
    return root;
}
void visit_prefix(node* root)
{
    if(!root)
    {
        return;
    }
    stack[top] = nullptr;
    top++;
    node* curr = root;
    while(curr)
    {
        cout << curr->val << ' ';
        if(curr->right)
        {
            stack[top] = curr->right;
            top++;
        }
        if(curr->left)
        {
            curr = curr->left;
        }
        else
        {
            curr = stack[top - 1];
            top--;
        }
    }
}
void infix_visit(node* root)
{
    node* curr = root;
    while(curr || top)
    {
        if(curr)
        {
            stack[top] = curr;
            top++;
            curr = curr->left;
        }
        else
        {
            curr = stack[top - 1];
            top--;
            cout << curr->val << ' ';
            curr = curr->right;
        }
    }
}
struct snode
{
    node* curr;
    int is_right; 
};
snode s_stack[100005];
int s_top = 0;
void post_visit(node* root)
{
    node* t = root;
    snode s;
    while(t || s_top)
    {
        while(t)
        {
            s.curr = t;
            s.is_right = 0;
            s_stack[s_top] = s;
            s_top++;
            t = t->left;
        }
        while(s_top)
        {
            if(!s_stack[s_top - 1].is_right)
            {
                s_stack[s_top - 1].is_right = 1;
                t = s_stack[s_top - 1].curr->right;
                break;
            }
            else
            {
                cout << s_stack[s_top - 1].curr->val << ' ';
                s_top--;
            }
        }
    }   
}
node* queue[100005];
int start;
int stop;
int is_empty()
{
    return start == stop;
}
void push_queue(node* temp)
{
    queue[stop] = temp;
    stop++;
}
node* pop_queue()
{
    node* record = queue[start];
    start++;
    return record;
}
void bfs_visit(node* root)
{
    if(!root)return;
    push_queue(root);
    while(!is_empty())
    {
        node* curr = pop_queue();
        cout << curr->val << ' ';
        if(curr->left)push_queue(curr->left);
        if(curr->right)push_queue(curr->right);
    }
}
//结点名称互不相同，val是int类型
int prefix_stack[100005];
int infix_stack[100005];
int prefix_num_for_infix_index[100005];
int p_top;
void count_root_id(int n)
{
    for(int i = 0;i < n;i++)
    {
        prefix_num_for_infix_index[infix_stack[i]] = i;
    }
}

node* create_infix_and_prefix(int start_id, int end_id)//前序为主（root），中序为辅（定位子树范围）
{
    if(start_id > end_id)
    {
        return nullptr;
    }
    node* temp = new node;
    temp->val = prefix_stack[p_top];
    p_top++;
    if(start_id == end_id)
    {
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }
    int root_id = prefix_num_for_infix_index[temp->val];
    temp->left = create_infix_and_prefix(start_id, root_id - 1);
    temp->right = create_infix_and_prefix(root_id+1, end_id);
    return temp;
}