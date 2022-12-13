#include <iostream>
#include <unordered_set>

using namespace std;

/* 
判断一个链表是否有环，方法1，借助hashset记录遍历过的每一个结点，如果再次遇到set中的结点，则有环
方法2，快慢指针，第一次遍历快指针走两步，慢指针走一步，如果fast为终点结点，则无环，如果fast和slow相遇则有环
第二次遍历时，fast重置为head结点，fast和slow每次都只走一步，再次相遇时为第一个入环结点
*/

class ListNode
{
public:
	int val;
	ListNode* next;
public:
	ListNode(int val)
	{
		this->val = val;
		this->next = nullptr;
	}
};

class sloution
{
public:
	// hashset辅助，一次循环，时间O(n)空间O(n)
	ListNode* isloop(ListNode* head, ListNode* tail) // 返回值为入环结点，head为头结点，tail为链表判断的终止结点，无特殊要求是tail为nullptr
	{
		if (!head || !head->next || !head->next->next)
		{
			return nullptr;
		}
		unordered_set<ListNode*> hashset;
		// 遍历链表
		ListNode* cur = head;
		while (cur != tail)
		{
			if (hashset.find(cur) == hashset.end()) // set中无当前结点
			{
				hashset.emplace(cur);
				cur = cur->next;
			}
			else // hashset中存在当前结点
			{
				return cur;
			}
		}
		// 遍历到结尾结点时，未发现入环结点，表示无环
		return nullptr;
	}
	// 快慢指针，两次循环，时间O(n),空间O(1)
	ListNode* hasloop(ListNode* head, ListNode* tail)
	{
		if (!head || !head->next || !head->next->next)
		{
			reutrn nullptr;
		}
		// 快慢指针初始都指向完成一轮循环后的位置，方便遍历的循环条件，优化代码
		ListNode* fast = head->next->next;
		ListNode* slow = head->next;
		// 第一次遍历，快走2，慢走1
		while (fast != slow)
		{
			// 如果fast走到结尾结点，表示无环
			if (fast->next == tail || fast->next->next == tail)
			{
				return nullptr;
			}
			fast = fast->next->next;
			slow = slow->next;
		}
		// 此时slow == fast，重置fast至head位置
		fast = head;
		// 第二次遍历，快慢各走一步
		while (fast != slow)
		{
			fast = fast->next;
			slow = slow->next;
		}
		// 两者相等时相遇，为第一个入环结点
		return fast;
	}
};
