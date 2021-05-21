#ifndef deque_h
#define deque_h

typedef struct node {
    char* value;
    struct node *next;
    struct node *prev; 
} Node;

typedef struct deque{
    int size;
    Node *head;
    Node *tail;
} Deque;

void pop_back(Deque* deque);

void pop_front(Deque* deque);

void push_back(Deque* deque);

void push_front(Deque* deque);

Deque* create_deque();

void delete_deque(Deque** deque);

void read_deque_front(Deque* deque);

void read_deque_back(Deque* deque);

#endif //deque_h