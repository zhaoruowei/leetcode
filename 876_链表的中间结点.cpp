class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // 快慢指针，快指针为null时，慢指针到中点
        ListNode* slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
