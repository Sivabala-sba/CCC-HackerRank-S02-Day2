#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct LinkedListNode {
    int val;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* insertAtBeginning(LinkedListNode* head, int val) {
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->val = val;
    newNode->next = head;
    return newNode;
}

LinkedListNode* insertAtEnd(LinkedListNode* head, int val) {
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->val = val;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    LinkedListNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return head;
}

LinkedListNode* insertAtPosition(LinkedListNode* head, int val, int pos) {
    if (pos <= 0) {
        return head;
    }

    if (pos == 1) {
        LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        newNode->val = val;
        newNode->next = head;
        return newNode;
    }

    LinkedListNode* current = head;
    for (int i = 1; i < pos - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return head; // Invalid position
    }

    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->val = val;
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

LinkedListNode* deleteAtBeginning(LinkedListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    LinkedListNode* newHead = head->next;
    free(head);
    return newHead;
}

LinkedListNode* deleteAtEnd(LinkedListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    LinkedListNode* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;

    return head;
}

LinkedListNode* deleteAtPosition(LinkedListNode* head, int pos) {
    if (head == NULL || pos <= 0) {
        return head;
    }

    if (pos == 1) {
        LinkedListNode* newHead = head->next;
        free(head);
        return newHead;
    }

    LinkedListNode* current = head;
    for (int i = 1; i < pos - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return head; // Invalid position
    }

    LinkedListNode* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    free(nodeToDelete);

    return head;
}

int rng(int lim) {
    if (lim == 0) return 0;
    return rand() % lim;
}

int a[1005], sz = 0;

void insertt(int val, int pos) {
    if (pos < 0) return;
    if (pos > sz + 1) return;
    sz += 1;
    for (int i = sz; i > pos; i--)
        a[i] = a[i - 1];
    a[pos] = val;
}

void erasee(int pos) {
    if (pos > sz) return;
    if (pos < 1) return;
    sz--;
    for (int i = pos; i <= sz; i++)
        a[i] = a[i + 1];
}

int check(LinkedListNode* head) {
    for (int i = 1; i <= sz; i++) {
        if (head == NULL) return 0;
        if (head->val != a[i]) return 0;
        head = head->next;
    }
    if (head != NULL) return 0;
    return 1;
}

int main() {
    srand(time(NULL));
    int t, n;
    scanf("%d %d", &t, &n);
    while (t--) {
        LinkedListNode* head = NULL;
        sz = 0;
        for (int i = 0; i < n; i++) {
            int type = rng(6);
            if (type == 0) {
                int val = rng(1000);
                head = insertAtBeginning(head, val);
                insertt(val, 1);
                if (!check(head)) {
                    printf("incorrect insertAtBeginning");
                    return 0;
                }
            }
            if (type == 1) {
                int val = rng(1000);
                head = insertAtEnd(head, val);
                insertt(val, sz + 1);
                if (!check(head)) {
                    printf("incorrect insertAtEnd");
                    return 0;
                }
            }
            if (type == 2) {
                int val = rng(1000);
                int pos = rng(sz + 1) + 1;
                head = insertAtPosition(head, val, pos);
                insertt(val, pos);
                if (!check(head)) {
                    printf("incorrect insertAtPosition");
                    return 0;
                }
            }
            if (type == 3) {
                head = deleteAtBeginning(head);
                erasee(1);
                if (!check(head)) {
                    printf("incorrect deleteAtBeginning");
                    return 0;
                }
            }
            if (type == 4) {
                head = deleteAtEnd(head);
                erasee(sz);
                if (!check(head)) {
                    printf("incorrect deleteAtEnd");
                    return 0;
                }
            }
            if (type == 5) {
                int pos = rng(sz) + 1;
                head = deleteAtPosition(head, pos);
                erasee(pos);
                if (!check(head)) {
                    printf("incorrect deleteAtPosition");
                    return 0;
                }
            }
        }
    }
    printf("correct");
    return 0;
}
