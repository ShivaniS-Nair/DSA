/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

static struct ListNode* getKthNode(struct ListNode* curr, int k) {
    while (curr != NULL && k > 0) {
        curr = curr->next;
        k--;
    }
    return curr;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (head == NULL || k <= 1) {
        return head;
    }

    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = head;

    struct ListNode* groupPrev = &dummy;

    while (1) {
        struct ListNode* kth = getKthNode(groupPrev, k);
        if (kth == NULL) {
            break; // Fewer than k nodes remain; leave them untouched
        }

        struct ListNode* groupNext = kth->next;

        // Reverse the k nodes in the current group
        struct ListNode* prev = groupNext;
        struct ListNode* curr = groupPrev->next;

        while (curr != groupNext) {
            struct ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        // Reconnect the reversed group and advance groupPrev to the new group tail
        struct ListNode* oldGroupHead = groupPrev->next;
        groupPrev->next = kth;
        groupPrev = oldGroupHead;
    }

    return dummy.next;
}
