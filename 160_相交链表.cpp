class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr)
        {
            return nullptr;
        }

        // 判断两个链表是否有环(本题不需要判断)
        ListNode *loop1 = isLoop(headA);
        ListNode *loop2 = isLoop(headB);

        // 情况1，如果两个结点都无环
        if (loop1 == nullptr && loop2 == nullptr)
        {
            // 找到相交结点
            ListNode *ans = intersect(headA, headB, nullptr);
            return ans;
        }

        // 情况2，两个结点都有环
        if (loop1 != nullptr && loop2 != nullptr)
        {
            // 情况3.1，两个链表第一个入环结点相同
            if (loop1 == loop2)
            {
                // 方法与情况2.2相同
                // 找到相交结点,终止条件为入环的第一个结点
                ListNode *ans = intersect(headA, headB, loop1);
                return ans;
            }
            else
            {
                // 情况3.2，两个链表第一个入环结点不同，且共环
                // loop2不动，loop1继续遍历，并记录loop1位置，如果共环，则在下一次遇见loop1时，会遇见loop2
                // 否则是情况3.3，两个链表不共环，loop1在下次遇到loop1之前，未遇到loop2
                ListNode *start = loop1->next;
                while (start != loop1)
                {
                    if (start == loop2)
                    {
                        return start;
                    }
                    start = start->next;
                }
            }
        }
        
        // 情况3，如果两个结点，一个有环，一个无环，则两者不相交
        return nullptr;
    }
    // 返回链表第一个入环结点
    ListNode *isLoop(ListNode *head)
    {
        // 快慢指针判断是否有环
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return nullptr;
        }
        // 第一次遍历，快指针一次两个结点，慢指针一次一个结点
        ListNode *fast = head->next->next;
        ListNode *slow = head->next;
        while (fast != slow)
        {
            if (fast->next == nullptr || fast->next->next == nullptr)
            {
                return nullptr;
            }
            fast = fast->next->next;
            slow = slow->next;
        }
        // 快指针返回头结点
        fast = head;

        // 第二次遍历，快慢指针每次一个结点
        while (fast != slow)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return fast;
    }
    // 返回第一个相交结点
    ListNode *intersect(ListNode *headA, ListNode* headB, ListNode *end)
    {
        if (headA == nullptr || headB == nullptr)
        {
            return nullptr;
        }
        // 遍历两个链表，找到各自的最后一个结点，并返回链表长度
        ListNode *curA = headA, *curB = headB;
        int n = 0;
        // 遍历链表A，统计长度n，curA指向最后一个结点
        while (curA->next != end)
        {
            curA = curA->next;
            ++n;
        }
        // 遍历链表B，统计与A的结点差值，curB指向B最后一个结点
        while (curB->next != end)
        {
            curB = curB->next;
            --n;
        }
        // 情况2.1，如果A的最后一个结点与B的最后一个结点不相等，则两链表不相交
        if (curA != curB)
        {
            return nullptr;
        }
        // 情况2.2，A的end结点与B相同，找到第一个相交的结点
        // A指向长链表的头，B指向短链表的头
        curA = n > 0?headA:headB;
        curB = curA == headA?headB:headA;
        // 长链表先走长度差值n个结点
        n = abs(n);
        while (n != 0)
        {
            curA = curA->next;
            --n;
        }
        // 长短链表同时移动，相等时，即为第一个相交结点
        while (curA != curB)
        {
            curA = curA->next;
            curB = curB->next;
        }

        return curA;
    }
};
