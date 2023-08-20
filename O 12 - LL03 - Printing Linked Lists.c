#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode {
    int val;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* _insert_node_into_singlylinkedlist(LinkedListNode* head, LinkedListNode* tail, int val) {
    if (!head) {
        head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        head->val = val;
        head->next = NULL;
        tail = head;
    } else {
        LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        node->val = val;
        node->next = NULL;
        tail->next = node;
        tail = tail->next;
    }
    return tail;
}

void printForward(LinkedListNode* head) {
    if (head == NULL) {
        return;
    }
    printf("%d ", head->val);
    printForward(head->next);
}

void printBackward(LinkedListNode* head) {
    if (head == NULL) {
        return;
    }
    printBackward(head->next);
    printf("%d ", head->val);
}

int main() {
    int head_size;
    scanf("%d", &head_size);

    LinkedListNode* head = NULL;
    LinkedListNode* head_tail = NULL;

    for (int head_i = 0; head_i < head_size; head_i++) {
        int head_item;
        scanf("%d", &head_item);
        head_tail = _insert_node_into_singlylinkedlist(head, head_tail, head_item);

        if (!head_i) {
            head = head_tail;
        }
    }

    printForward(head);
    printf("\n");
    printBackward(head);

    return 0;
}
