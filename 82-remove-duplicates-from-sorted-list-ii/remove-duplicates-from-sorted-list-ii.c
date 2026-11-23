#include <stddef.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = head;

    struct ListNode* prev = &dummy;
    struct ListNode* curr = head;

    while (curr != NULL) {
        // Check if current value has duplicates
        if (curr->next != NULL && curr->val == curr->next->val) {
            int dupVal = curr->val;
            // Skip all nodes with dupVal
            while (curr != NULL && curr->val == dupVal) {
                curr = curr->next;
            }
            prev->next = curr;
        } else {
            // Current node is unique; advance prev
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}
