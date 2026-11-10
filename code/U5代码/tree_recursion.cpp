#include<iostream>
#include<stdio.h>
using namespace std;
//二叉链表表示二叉树
struct node
{
    char val;
    node* left;
    node* right;
};
node* create_prefix_tree()
{
    char v;
    cin >> v;
    if(v == '@')
    {
        return nullptr;
    }
    node* temp = new node;
    temp->val = v;
    temp->left = create_prefix_tree();
    temp->right = create_prefix_tree();
    return temp;
}
//node* create_infix_tree() 一般不能中序确定二叉树
//后序建树可通过读完所有字符，从结尾按照“根右左”建树
node* find_parent(node* child, node* root)  //输入不是nullptr
{
    if(!root)
    {
        return nullptr;
    }
    if(root->left == child || root->right == child)
    {
        return root;
    }
    node* left_candidate = find_parent(child, root->left);
    if(left_candidate)return left_candidate;
    else return find_parent(child, root->right);
}
void pre_visit(node* root)
{
    if(!root)return;
    cout << root->val << ' ';
    pre_visit(root->left);
    pre_visit(root->right);
}
void in_visit(node* root)
{
    if(!root)return;
    in_visit(root->left);
    cout << root->val << ' ';
    in_visit(root->right);
}
void post_visit(node* root)
{
    if(!root)return;
    post_visit(root->left);
    post_visit(root->right);
    cout << root->val << ' ';
}
void delete_tree(node* root) 
{
    if(!root)return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}
int get_depth(node* root)
{
    if(!root)
    {
        return 0;
    }
    int left_val = get_depth(root->left);
    int right_val = get_depth(root->right);
    return left_val >= right_val? left_val + 1: right_val + 1;
}

