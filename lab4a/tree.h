#ifndef tree_h
#define tree_h

typedef struct item{
	char* one;
	char* two;
	struct item* next;
}Item;

typedef struct node{
	Item* first;
	unsigned int key;
  	struct node* left;
  	struct node* right;
	struct node* prev;
	struct node* root;
	struct node* next;
}Node;

typedef struct tree{
	Node* root;
	int size;
	char* file;
}Tree;

Tree* create_tree();

void read_tree(Node* node, int key);

Item* search_tree(Node* node);

void search_near_key_tree(Node* node, int key, int* qn, Item* it);

void file_tree(Tree* tree);

void clear_tree(Tree* tree);

void clear_node(Node* node);

void insert_tree(Tree* tree);

void delete_tree(Node* node);

Node* delete_node(Tree* tree, Node* node, int key);

#endif //tree_h