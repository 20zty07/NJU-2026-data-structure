//子女-兄弟表示法
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
node* find_parent(node* child, node* root)
{
    if(!root || !child || child == root)
    {
        return nullptr;
    }
    node* bro = root->left;
    while(bro)
    {
        if(bro == child)
        {
            return root;
        }
        bro = bro->right;
    }
    node* ans;
    bro = root->left;
    while(bro)
    {
        ans = find_parent(child, bro);
        if(ans)return ans;
        bro = bro->right;
    }
    return nullptr;
}
//深度优先：
//先根遍历：根、左子树、右子树，在子女兄弟表示法中是前序遍历
void root_first_visit(node* root)
{
    if(!root)return;
    cout << root->val << ' ';
    root_first_visit(root->left);
    root_first_visit(root->right);
}
//后根遍历：左子树、根、右子树，在子女兄弟表示法中是中序遍历
void leaf_first_visit(node* root)
{
    if(!root)return;
    leaf_first_visit(root->left);
    cout << root->val << ' ';
    leaf_first_visit(root->right);
}
//广度优先；根、右子树、左子树
node* bstack[100005];
int start;
int end;
int is_empty()
{
    return end == start;
}
void bfs(node* root)
{
    if(!root)return;
    bstack[end] = root;
    end++;
    while(!is_empty())
    {
        node* curr = bstack[start];
        start++;
        cout << curr->val << ' ';
        node* child = curr->left;
        while(child)
        {
            bstack[end] = child;
            end++;
            child = child->right;
        }
    }
}
