#ifndef graph_h
#define graph_h

typedef struct coordinate{
	float x, y;
}Coords;

typedef struct item{
	int index;
	float weight;
	struct item* next;
}Item;

typedef struct item_e{
	int index;
	struct item_e* next;
}Item_e;

typedef struct route{
	float distance;
	Item_e* path;
}Route;

typedef struct link{
	int i1;
	int i2;
}Link;

typedef struct node{
	int busy;
	char* name;
	Item* first;
	Coords coords;
}Node;

typedef struct graph{
	Node* node;
	int cap;
	int size;
	char** names;
}Graph;

void create_graph(Graph* graph);

int insert_node(Graph* graph, Coords c);

int insert_link(Graph* graph, Coords c1, Coords c2, float weight);

void delete_queue(Item_e** list);

int delete_node(Graph* graph, Coords c);

int delete_link(Graph* graph, Coords c1, Coords c2);

void print_path(Item_e* path, Graph graph);

Route search_BF(Graph graph, Coords c1, Coords c2);

void delete_list(Item** head);

Route search_Deikstra(Graph graph, Coords c1, Coords c2);

void write_to_file(Graph graph, FILE* file);

void read_from_file(Graph* graph, FILE* file);

void delete_graph(Graph* graph);

void read_graph(Graph graph);

#endif // graph_h