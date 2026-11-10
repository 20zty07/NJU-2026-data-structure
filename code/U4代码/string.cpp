#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
using namespace std;
char pattern[100005];
char target[100005];
int nxt[100005];
void get_next()
{
    int len = strlen(pattern);
    nxt[0] = -1;
    int i = 0;//当前下标
    int j = -1;//当前next[i]，即match长度。此时下标从0开始与下一次匹配需+1抵消
    while(i < len)
    {
        if(j == -1 || pattern[i] == pattern[j])
        {
            i++;
            j++;
            nxt[i] = j;
        }
        else
        {
            j = nxt[j];
        }
    }
}
int get_first_matched_index()
{
    int m = strlen(pattern);
    int n = strlen(target);
    int top = 0;
    int i = 0;
    int has_matched = 0;
    int ans = -1;
    while(top < n)
    {
        if(i == -1)
        {
            i++;
            top++;
            //has_matched = 0;    
        }
        else if(pattern[i] == target[top])
        {
            i++;
            top++;
            //has_matched++;
        }
        else
        {
            i = nxt[i];
        }
        if(i == m/*has_matched == m*/)
        {
            ans = top - m;
            break;
            //如果要统计所有匹配的下标，那么应改为：
            //matched_index[id_top] = top - m;
            //id_top++;
            //此处无需回退，也不能回退。原因是next数组事实上在最后多求了一次
            //并且i = next[i]是第i处失配，但是此处已经匹配
            //i = nxt[i];
            //matched_cnt++;
        }
    }
    if(ans == -1)
    {
        cout << "failure\n";
    }
    return ans;
}

/*
ppt写法：
    void AString::getNext(int next[]) {
        int j = 0, k = -1,  lengthP = curLength;
        next[0] = -1;
        while (j < lengthP) 		//计算next[j]
            if ( k == -1 || ch[j] == ch[k]) {
                j++;  k++;
                next[j] = k;
            }
            else k = next[k];
    }; 

    int AString::fastFind(AString& pat, int k, 
            int next[]) const {
    //从 k 开始寻找 pat 在 this 串中匹配的位置。若找
    //到，函数返回 pat 在 this 串中开始位置，否则函
    //数返回-1。数组next[ ] 存放 pat 的next[j] 值。
        int posP = 0,  posT = k;	//两个串的扫描指针
        int lengthP = pat.curLength;         //模式串长度
        int lengthT = curLength;               //目标串长度
        while (posP < lengthP && posT < lengthT)	
            if (posP == -1 || pat.ch[posP] == ch[posT]) 
            { posP++;  posT++; }          //对应字符匹配
            else posP = next[posP];   //求pat下趟比较位置
        if (posP < lengthP) return -1;	//匹配失败
        else return posT-lengthP;		//匹配成功
};



*/
int main()
{
    cin >> pattern >> target;
    get_next();
    int i = get_first_matched_index();
    if(i != -1)
    {
        cout << i << '\n';
    }
    return 0;
}