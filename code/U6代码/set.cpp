#include<cstdio>
#include<iostream>
#include<cassert>
#include<cstring>
using namespace std;

int arr[100005];    //子女-双亲表示法表示树，下标为子女的内容存父节点的下标，下标为根节点的内容存-（树的大小）
int height[100005];
//给定二维数组src，在arr中创建树
int src[100005][2];
void initialize_arr(int length)
{
    for(int i = 0;i < length;i++)
    {
        arr[i] = -1;
        height[i] = 1;
    }
}
//给定元素elem，找到他的根结点
int find(int elem)  
{
    int result = elem;
    while(arr[result] >= 0)
    {
        result = arr[result];
    }
    return result;
}




void union_sequence(int self, int elem)  //找到elem的根结点，将他加入含有self的子树
{
    self = find(self);
    int other = find(elem);
    if (self == other) return;
    arr[self] += arr[other];
    arr[other] = self;
}
void union_weight(int self, int elem)   //按树的结点个数合并改进的算法
{
    self = find(self);
    int other = find(elem);
    if (self == other) return;
    int temp = arr[self] + arr[other];
    if(arr[self] <= arr[other])
    {
        arr[self] = temp;
        arr[other] = self;
    }
    else
    {
        arr[other] = temp;
        arr[self] = other;        
    }
}
void union_height(int self, int elem)   //按照树的高度合并改进的算法
{
    self = find(self);
    int other = find(elem);
    if (self == other) return;
    int temp = arr[self] + arr[other];
    if(height[self] >= height[other])
    {
        arr[self] = temp;
        arr[other] = self;
        height[self] = height[self] >= height[other] + 1? height[self]: height[other] + 1;
    }
    else
    {
        arr[other] = temp;
        arr[self] = other;
        height[other] = height[other] >= height[self] + 1? height[other]: height[self] + 1;        
    }
}
void build(int length)
{
    initialize_arr(length);

    for (int i = 0; i < length; i++)
    {
        int root1 = find(src[i][0]);
        int root2 = find(src[i][1]);

        union_height(root1, root2);
    }
}
void compress_path(int elem)    //将含有elem的树进行压缩路径
{
    int root = find(elem);
    while(arr[elem] >= 0)
    {
        int temp = arr[elem];
        arr[elem] = root;
        elem = temp;
    }
}

int d[100005];
int addr[100005];
int is_used[100005];
int hash_func(int x)
{
    return x;
}
void build_hash(int n, int m)
{
    for(int i = 0;i < n;i++)
    {
        int temp = hash_func(d[i]);
        if(is_used[temp])
        {
            while(is_used[temp])temp = (temp + 1) % m;
            is_used[temp] = 1;
            addr[temp] = d[i];
        } 
    }
}

/*
实现下面这样一个函数：

```cpp
int insert(const char *str, unsigned int hash) {
    //TODO
}
```

其中 `str` 是一个字符串，`hash` 是与之对应的一个整数。这个函数会被调用若干次，保证对于任意两次调用 `insert(str_a, hash_a)` 和 `insert(str_b, hash_b)`，若 `strcmp(str_a, str_b) == 0`，则一定有 `hash_a == hash_b`，但反之不然。保证每次调用中 `hash` 不超过 `255`。保证总调用次数不超过 `255`。`insert` 的返回值受先前调用历史的影响，若 `str` 与先前某一次调用重复，则返回 `1`，否则返回 `0`。保证 `str` 可以安全地保存指针，不需要拷贝字符串。

例如

int main() {
    insert("Alice", 0);   // returns 0
    insert("Bob", 1);     // returns 0
    insert("Alice", 0);   // returns 1
    insert("Charlie", 0); // returns 0
    
    // insert("Alice", 1); is not possible
}
*/
struct node
{
    const char* val;
    node* nxt;
};
node* pool[256];
int insert(const char *str, unsigned int hash) 
{
    node* curr = pool[hash];
    while(curr)
    {
        if(!strcmp(curr->val, str))
        {
            return 1;
        }
        curr = curr->nxt;
    }
    node* temp = new node;
    temp->val = str;
    temp->nxt = pool[hash];
    pool[hash] = temp;
    return 0;
}
void delete_list(int i)
{
    node* curr = pool[i];
    assert(curr != nullptr);
    while(curr)
    {
        node* temp = curr;
        curr = curr->nxt;
        delete temp;
    }
}
void delete_all()
{
    for(int i = 0;i < 256;i++)
    {
        if(pool[i])delete_list(i);
    }
}
struct node2
{
    int is_used;
    const char* val;
};
node2 pool2[256];
int insert2(const char *str, unsigned int hash)
{
    while(pool2[hash].is_used)
    {
        if(!strcmp(pool2[hash].val, str))
        {
            return 1;
        }
        hash = (hash + 1) % 256;
    }
    pool2[hash].is_used = 1;
    pool2[hash].val = str;
    return 0;
}

int main() {
    cout << insert2("Alice", 0);   // returns 0
    cout << insert2("Bob", 1);     // returns 0
    cout << insert2("Alice", 0);   // returns 1
    cout << insert2("Charlie", 0); // returns 0
    
    // insert("Alice", 1); is not possible
}