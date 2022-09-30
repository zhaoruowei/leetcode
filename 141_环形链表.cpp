class Solution {
public:
    bool hasCycle(ListNode *head) {
        int pos = -1;
        // 快慢指针
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            cout << pos << endl;
            return false;
        }
        ListNode *slow = head->next, *fast = head->next->next;
        // 第一次遍历，快指针一次两个结点，慢指针一次一个结点,两者在环中相遇
        while (slow != fast)
        {
            // 不确定是否有环
            if (fast->next == nullptr || fast->next->next == nullptr)
            {
                cout << pos << endl;
                return false;
            }
            fast = fast->next->next;
            slow = slow->next;
        }

        // 第一次相遇后快指针返回head
        fast = head;

        // 第二次遍历，fast，slow每次都移动一个结点，再次相遇时，即为第一个入环结点
        pos = 0;
        while (fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
            ++pos;
        }
        cout << pos << endl;
        return true;
    }
};
