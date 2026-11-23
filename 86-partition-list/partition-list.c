#include <stddef.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode beforeDummy = {0, NULL};
    struct ListNode afterDummy = {0, NULL};

    struct ListNode* before = &beforeDummy;
    struct ListNode* after = &afterDummy;

    while (head != NULL) {
        if (head->val < x) {
            before->next = head;
            before = before->next;
        } else {
            after->next = head;
            after = after->next;
        }
        head = head->next;
    }

    // Terminate the second list to avoid cycles
    after->next = NULL;
    // Connect the two partitions
    before->next = afterDummy.next;

    return beforeDummy.next;
}

