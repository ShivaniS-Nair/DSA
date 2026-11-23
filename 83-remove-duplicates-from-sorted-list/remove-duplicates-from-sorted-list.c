#include <stddef.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* curr = head;

    while (curr != NULL && curr->next != NULL) {
        if (curr->val == curr->next->val) {
            // Skip the duplicate node
            curr->next = curr->next->next;
        } else {
            // Move to the next distinct value
            curr = curr->next;
        }
    }

    return head;
}
