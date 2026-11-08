#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // A dummy head node simplifies managing the list's front end
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = NULL;
    
    struct ListNode* current = &dummy;
    int carry = 0;
    
    // Continue loop as long as there are digits left or a remaining carry
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        // Calculate new carry and the digit value for the new node
        carry = sum / 10;
        
        // Allocate space for the new digit node
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = sum % 10;
        newNode->next = NULL;
        
        // Attach the new node to our result list and move current forward
        current->next = newNode;
        current = current->next;
    }
    
    // The actual head of the result list is the node right after the dummy
    return dummy.next;
}
