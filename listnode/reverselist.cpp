#include <iostream>
#include <stack>

using namespace std;

class ListNode
{
public:
	int val;
	ListNode* next;
};

class sloution
{
public:
	// 辅助栈，利用栈的先进后出特点时间O(n)，空间O(n)
	ListNode* reverseList1(ListNode* head)
	{
		// 空链表
		if (!head)
		{
			return head;
		}
		// 辅助栈
		stack<ListNode*> list;
		// 遍历结点压栈
		while (head)
		{
			list.emplace(head);
			head = head->next;
		}
		// 弹栈
		head = list.top();
		list.pop();
		ListNode* cur = head;
		while (!list.empty())
		{
			cur->next = list.top();
			list.pop();
			cur = cur->next;
		}
		cur->next = nullptr;
		return head;
	}
	// 原地迭代,时间O(n),空间O(1)
	// 记录当前指针，前指针和后指针，将当前指针的next指针指向前指针
	ListNode* reverseList2(ListNode* head)
	{
		ListNode* prev = nullptr;
		ListNode* cur = head;
		// 遍历链表
		while (cur)
		{
			ListNode* next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		return prev;
	}
	// 递归时间O(n),空间O(n)
	ListNode* reverseList3(ListNode* head)
	{
		if (!head || !head->next)
		{
			return head;
		}
		ListNode* newhead = reverseList3(head->next);
		head->next->next = head;
		head->next = nullptr;
		return newhead;
	}
};
