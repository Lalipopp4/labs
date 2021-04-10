#ifndef tree_h
#define tree_h

typedef struct item{
	char* one;
	char* two;
	struct item* next;
}Item;

typedef struct node{
	Item* item;
	Item* first;
	unsigned int key;
  	struct node* left;
  	struct node* right;
	struct node* prev;
	struct node* root;
}Node;

typedef struct tree{
	Node* root;
	int size;
}Tree;

Tree* create_tree(Tree* tree);

void insert_tree(Node* node, Node* prev_node, int key);

void read_tree(Node* node);

void search_tree(Node* node);

void search_near_key_tree(Node* node, int key, int* qn, Item* it);

#endif //tree_h