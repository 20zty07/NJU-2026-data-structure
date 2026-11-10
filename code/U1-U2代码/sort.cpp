//给定n个输入，按照非递减顺序排序，O(n²)

#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int  elem[100005];

int max_elem(int end)
{
    int ans = 0;
    for(int i = 0;i <= end;i++)
    {
        if(elem[ans] < elem[i])
        {
            ans = i;
        }
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0;i < n;i++)
    {
        cin >> elem[i];
    }
    for(int i = n - 1;i >= 0;i--)
    {
        int j = max_elem(i);
        if(j != i)
        {
            int temp = elem[j];
            elem[j] = elem[i];
            elem[i] = temp;
        }
    }
    for(int i = 0;i < n;i++)
    {
        cout << elem[i]<< ' ';
    }
    return 0;
}