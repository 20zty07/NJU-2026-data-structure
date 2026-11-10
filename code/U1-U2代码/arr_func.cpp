//数组的查找、插入、删除、交集、并集
#include<iostream>
#include<cstdio>
#include<cassert>
using namespace std;
int find(int *arr, int elem,int n)
{
    for(int i = 0;i < n;i++)
    {
        if(arr[i] == elem)
        {
            flag = 1;
            return i;
        }
    }
    return -1;
}
void insert(int *arr, int id, int elem, int n)
{
    for(int i = n - 1;i >= id;i--)
    {
        arr[i + 1] = arr[i];
    }
    arr[id] = elem;
}
void delete_arr(int *arr, int id, int n)
{
    for(int i = id + 1;i < n;i++)
    {
        arr[i - 1] = arr[i];
    }
}
void union_arr(int *arr, int *other, int& arr_l, int other_l)
{
    for(int other_ptr = 0;other_ptr < other_l;other_ptr++)
    {
        if(find(arr, other[other_ptr], arr_l) == -1)
        {
            insert(arr, arr_l, other[other_ptr], arr_l);
            arr_l++;
        }  
    }
}
void intersect_arr(int *arr, int *other, int& arr_l, int other_l)
{
    for(int arr_ptr = 0;arr_ptr < arr_l;arr_ptr++)
    {
        int id = find(other, arr[arr_ptr], other_l);
        if(id == -1)
        {
            delete_arr(arr, arr_ptr, arr_l);
            arr_l--;
            arr_ptr--;
        }
    }
}