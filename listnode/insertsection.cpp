#include <iostream>

using namespace std;

/* 
判断两链表是否相交, 并返回相交结点 
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

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB)
        {
            return nullptr;
        }
        // 判断两个链表是否有环,并取得入环结点
        ListNode* loopA = getLoopNode(headA);
        ListNode* loopB = getLoopNode(headB);

        // 都无环
        if (!loopA && !loopB)
        {
            return getFirstNode(headA, headB, nullptr);
        }
        else if (loopA && loopB) // 都有环
        {
            // 入环结点相同
            if (loopA == loopB)
            {
                return getFirstNode(headA, headB, loopA);
            }
            else // 入环结点不同
            {
                // 让某一入环结点转圈，在下一次遇到本身之前遇到另一入环节点则共环，否则不共环
                ListNode* cur = loopA->next;
                while (cur != loopA)
                {
                    // 共环，返回任意入环结点
                    if (cur == loopB) return cur;
                    cur = cur->next;
                }
                // 不共环说明不相交
                return nullptr;
            }
        }
        else // 一个有环一个无环
        {
            return nullptr;
        }
    }
public:
    ListNode* getLoopNode(ListNode* head)
    {
        if (!head || !head->next || !head->next->next)
        {
            return nullptr;
        }
        ListNode* fast = head->next->next;
        ListNode* slow = head->next;
        while (fast != slow)
        {
            if (!fast->next || !fast->next->next)
            {
                return nullptr;
            }
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = head;
        while (fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
public:
    // 返回两个链表A,B从头到tail位置的第一个相交结点，不相交返回nullptr
    // tail一定在链表中,tail
    ListNode* getFirstNode(ListNode* headA, ListNode*headB, ListNode* tail)
    {
        if (!headA || !headB)
        {
            return nullptr;
        }

        int n = 0;
        ListNode* curA = headA;
        while (curA->next != tail)
        {
            curA = curA->next;
            n++;
        }

        ListNode* curB = headB;
        while (curB->next != tail)
        {
            curB = curB->next;
            n--;
        }

        if (curA != curB)
        {
            return nullptr;
        }

        curA = n > 0 ? headA : headB;
        curB = curA == headA ? headB : headA;
        n = abs(n);
        
        while (n--)
        {
            curA = curA->next;
        }

        while (curA != curB)
        {
            curA = curA->next;
            curB = curB->next;
        }

        return curA;
    }
};
