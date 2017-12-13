/*
* breeze License
* Copyright (C) 2014-2017 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


//! 测试

#include <common.h>
#include <utls.h>
#include <balance.h>
using namespace zsummer::log4z;
using namespace zsummer::mysql;

template<class T>
inline void quick_sort(std::vector<T> &arr, int begin, int end)
{
    T mid = arr[end];
    int left = begin;
    int right = end;
    while (left < right)
    {
        while (arr[left] <= mid && left < right)
        {
            left++;
        }
        while (arr[right] > mid && left < right)
        {
            right--;
        }
        if (left >= right)
        {
            break;
        }
        std::swap(arr[left], arr[right]);
    }
    if (left > begin)
    {
        quick_sort(arr, begin, left -1);
    }
    if (right < end)
    {
        quick_sort(arr, right+1, end);
    }
}

template<class T>
struct ListNode
{
    T val = 0;
    ListNode * next = nullptr;
};


template<class T>
inline ListNode<T> * merge_sorted(ListNode<T> * left, ListNode<T> * right)
{
    ListNode<T> head;
    ListNode<T>* cur = &head;

    while (left  || right )
    {
        if (!right)
        {
            cur->next = left;
            return head.next;
        }
        if (!left)
        {
            cur->next = right;
            return head.next;
        }
        if (left->val <= right->val)
        {
            cur->next = left;
            left = left->next;
            cur = cur->next;
            cur->next = nullptr;

            continue;
        }
        cur->next = right;
        right = right->next;
        cur = cur->next;
        cur->next = nullptr;
    }
    return head.next;
}


template<class T>
inline ListNode<T> * split_list(ListNode<T> * head)
{
    ListNode<T> * right = head;
    while (right->next && right->val <= right->next->val)
    {
        right = right->next;
    }
    if (right->next)
    {
        auto next = right->next;
        right->next = nullptr;
        return merge_sorted(head, split_list(next));
    }
    return head;
}

template<class T>
inline ListNode<T> * split_list_2(ListNode<T> * head)
{
    if (!head->next)
    {
        return head;
    }
    ListNode<T> * fast = head;
    ListNode<T> * slow = head;
    while (fast->next && fast->next->next && slow->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = nullptr;
    slow = fast;
    fast = split_list_2(head);
    slow = split_list_2(slow);
    return merge_sorted(fast, slow);
}


inline void arith_log_sort(ListNode<int> * right)
{
    while (right)
    {
        LOGD(right->val);
        right = right->next;
    }
}
inline void arith_sort()
{
    std::vector<int> a = { 5,2,3,5,6 };
    quick_sort(a, 0, 4);
    LOGD(a);

    ListNode<int> * head = new ListNode<int>();
    auto right = head;
    right->val = rand() % 2000;
    for (size_t i = 0; i < 1000; i++)
    {
        right->next = new ListNode<int>();
        right->next->val = rand() % 2000;
        right = right->next;
    }
    double now = getFloatNowTime();
    right = split_list_2(head);
    LOGD("arith_sort 2 used " << getFloatNowTime() - now);
    while (head)
    {
        right = head->next;
        delete head;
        head = right;
    }

    head = new ListNode<int>();
    right = head;
    right->val = rand() % 2000;
    for (size_t i = 0; i < 1000; i++)
    {
        right->next = new ListNode<int>();
        right->next->val = rand() % 2000;
        right = right->next;
    }
    now = getFloatNowTime();
    right = split_list(head);
    LOGD("arith_sort used " << getFloatNowTime() - now);
    //arith_log_sort(right);
    while (head)
    {
        right = head->next;
        delete head;
        head = right;
    }

}
