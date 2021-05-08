#ifndef kdtree_h
#define kdtree_h

typedef struct item{
	float num;
	char* data;
	struct item* next;
}Item;

typedef struct node{
	int key[2];
	struct node* left;
	struct node* right;
	Item* item;
}Node;

typedef struct tree{
	Node* root;
	int n;
	char* file;
}Tree;

Tree* create_tree(Tree* tree);

void insert_tree();

void delete_tree();

void search_tree();

void search_nearest_tree();

void read_tree(Node* node, int x1, int x2, int y1, int y2);

#endif //kdtree_h