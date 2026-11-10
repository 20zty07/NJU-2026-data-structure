#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
#include<cassert>
using namespace std;
//给定节点id（从0开始），它的左孩子是2*id+1，右孩子是2*id+2，
//父节点是（id - 1） >> 1
struct node
{
    char val;
    node* left;
    node* right;
};
node* heap[100005];
int top;
int left_le_right(int left, int right)
{
    return heap[left]->val <= heap[right]->val;
}
void sift_down(int start, int end)  //[start,n]
{
    int child = start * 2 + 1;
    while(child <= end)
    {
        if(child + 1 <= end)
        {
            child = left_le_right(child, child + 1)? child: child + 1;
        }
        if(left_le_right(start, child))
        {
            break;
        }
        else
        {
            node* temp = heap[start];
            heap[start] = heap[child];
            heap[child] = temp;
        }
        start = child;
        child = start * 2 + 1;
    }
}
void sift_up(int end, int start)    //[end,0]
{
    int parent = (end - 1) >> 1;
    while(end > start)
    {
        if(left_le_right(parent, end))
        {
            break;
        }
        else
        {
            node* temp = heap[parent];
            heap[parent] = heap[end];
            heap[end] = temp;            
        }
        end = parent;
        parent = (end - 1) >> 1;
    }
}
void insert_and_adjust(node* new_node)  //插入到最后一个节点
{
    heap[top] = new_node;
    top++;
    sift_up(top - 1, 0);
}
void delete_and_adjust() //删去第一个节点
{
    assert(top > 0);
    node* temp = heap[0];
    heap[0] = heap[top - 1];
    top--;
    delete temp;
    if(!top)
    {
        return;
    }
    sift_down(0, top - 1);
}

//哈夫曼树：在单调栈中，弹出n个元素构成n叉子树，再压入栈
//小蓝鲸的nju量子密信：
/*
题目描述
在南京大学庆祝建校的保密通信演练中，小蓝鲸负责设计一套基于量子纠缠的三进制变长前缀编码系统。

通信字符集由 空格 ' ' 和 26 个小写英文字母 'a' $\sim$ 'z' 共 27 种字符构成。量子信道仅支持三态调制，因此编码符号由三个大写字母 'N'、'J'、'U' 组成。为了让传输的总码长最短，小蓝鲸采用三进制哈夫曼树进行编码与解码。

1. 字符集与建树规则
通信系统给出了这 27 种字符的频次（权重）。输入首先给出空格 ' ' 的频次，随后依次给出 'a' 到 'z' 的频次。

只有频次大于 $0$ 的字符才会作为叶子结点参与建树。设频次大于 $0$ 的字符共有 $M$ 个，保证 $M \ge 3$ 且 $M$ 为奇数。

三进制哈夫曼树的自底向上合并规则如下：

每个结点维护两个属性：权重 与 该结点子树中包含的所有字符的最小 ASCII 码。 字符的字典序比较严格按标准 ASCII 码进行，即空格 ' ' (ASCII 32) 严格小于 'a' (ASCII 97) $\dots$ 小于 'z' (ASCII 122)。 若两个结点的权重不同，权重较小者优先；若权重相同，子树最小字符的 ASCII 码较小者优先。
只要候选结点集合中的结点数大于 $1$，每次取出键值最小的三个结点 $A, B, C$（满足键值 $A < B < C$）：
最小结点 $A$ 作为新父结点的 'N' 孩子；
次小结点 $B$ 作为新父结点的 'J' 孩子；
最大结点 $C$ 作为新父结点的 'U' 孩子；
合成的新父结点的权重为三者权重之和（即 $weight(A) + weight(B) + weight(C)$），其子树最小字符为三者子树最小字符的最小值（即 $\min(min\_char(A), min\_char(B), min\_char(C))$）；
将新父结点加入候选结点集合中。
重复以上合并，直到集合中只剩下一个结点，该结点即为三进制哈夫曼树的根结点。由于初始非 $0$ 结点数 $M$ 为奇数，每次合并减少 $2$ 个候选结点，最终必然恰好合并至剩余 $1$ 个根结点，形成一棵内部结点度数均为 3 的满三叉树。
2. 密信解码规则
小蓝鲸截获了一段仅由大写字母 'N'、'J'、'U' 组成的密文串 $S$。解码流程如下：

从树的根结点出发，依次读取密文串中的字符：遇到 'N' 走向 'N' 孩子，遇到 'J' 走向 'J' 孩子，遇到 'U' 走向 'U' 孩子；
当走向某个叶子结点时，成功解析出一个字符，将其拼入明文，然后立即重置指针回到根结点，继续处理下一个密文字符；
合法性校验：当密文串全部读取完毕时，指针未能停留在根结点（说明密文前缀不完整，在某个字符的编码中间被意外截断），则判定该密文非法，输出一行 INVALID。若全部密文顺利解码完毕且最终指针停留在根结点，输出解码后的明文字符串。
输入格式
第一行包含 27 个非负整数，依次表示空格 ' ' 以及 'a' 到 'z' 的出现频次。

第二行包含一个非空字符串 $S$，表示待解码的密文字符串，保证 $S$ 仅由大写字母 'N', 'J', 'U' 组成。

输出格式
若密文合法，输出一行解码后的明文字符串（明文中可能包含空格）；若密文非法，输出一行 INVALID。
*/
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cassert>
using namespace std;

struct node
{
    int weight;
    char min_val;
    node* child[3];
};

node* pool[55];
int top;
string s;
int s_ptr;
char ans[200005];
int ans_ptr;

int is_latter_bigger(int former, int latter)
{
    if(pool[latter]->weight > pool[former]->weight)
    {
        return 1;
    }
    if(pool[latter]->weight == pool[former]->weight)
    {
        return pool[latter]->min_val > pool[former]->min_val;
    }
    return 0;
}
int is_leaf(node* curr)
{
    return !curr->child[0] && !curr->child[1] && !curr->child[2];
}
void adjust_pool()
{
    if(top <= 1)
    {
        return;
    }
    int new_id = top - 1;
    while(new_id > 0)
    {
        if(is_latter_bigger(new_id - 1, new_id))
        {
            node* temp = pool[new_id];
            pool[new_id] = pool[new_id - 1];
            pool[new_id - 1] = temp;
            new_id--;
        }
        else
        {
            break;
        }
    }
}
char read_one_letter(node* tree_ptr)
{
    while(!is_leaf(tree_ptr))
    {
        if(s_ptr >= s.size())
        {
            return '@';
        }
        if(s[s_ptr] == 'N')
        {
            tree_ptr = tree_ptr->child[0];
        }
        if(s[s_ptr] == 'J')
        {
            tree_ptr = tree_ptr->child[1];
        }
        if(s[s_ptr] == 'U')
        {
            tree_ptr = tree_ptr->child[2];
        }
        s_ptr++;
    }
    return tree_ptr->min_val;
}
void load_one_letter(char curr)
{
    ans[ans_ptr] = curr;
    ans_ptr++;
}
void delete_tree(node* root)
{
    if(root)
    {
        delete_tree(root->child[0]);
        delete_tree(root->child[1]);
        delete_tree(root->child[2]);
        delete root;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int space_freq;
    cin >> space_freq;
    if(space_freq)
    {
        node* temp = new node;
        temp->weight = space_freq;
        temp->min_val = ' ';
        temp->child[0] = nullptr;
        temp->child[1] = nullptr;
        temp->child[2] = nullptr;
        pool[top] = temp;
        top++;
    }
    for(int i = 1;i < 27;i++)
    {
        int freq;
        cin >> freq;
        if(!freq)
        {
            continue;
        }
        node* temp = new node;
        temp->weight = freq;
        temp->min_val = 'a' + i - 1;
        temp->child[0] = nullptr;
        temp->child[1] = nullptr;
        temp->child[2] = nullptr;
        pool[top] = temp;
        top++;
        adjust_pool();
    }
    while(top > 1)
    {
        node* temp = new node;
        temp->weight = pool[top - 1]->weight + pool[top - 2]->weight + pool[top - 3]->weight;
        int candidate = top - 1;
        if(pool[top - 1]->min_val >= pool[top - 2]->min_val)
        {
            candidate = top - 2;
        }
        if(pool[top - 3]->min_val <= pool[candidate]->min_val)
        {
            candidate = top - 3;
        }
        temp -> min_val = pool[candidate]->min_val;
        temp->child[0] = pool[top - 1];
        temp->child[1] = pool[top - 2];
        temp->child[2] = pool[top - 3];
        top -= 3;
        pool[top] = temp;
        top++;
        adjust_pool();
    }
    cin >> s;
    node* tree_ptr;
    while(s_ptr < s.size())
    {
        tree_ptr = pool[0];
        char curr = read_one_letter(tree_ptr);
        if(curr == '@')
        {
            cout << "INVALID\n";
            return 0;
        }
        load_one_letter(curr);
    }
    ans[ans_ptr] = '\0';
    cout << ans << '\n';
    delete_tree(pool[0]);
    return 0;
}

