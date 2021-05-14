#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "functions.h"

#define FLT_MAX 10.0

void create_graph(Graph* graph){
	graph->size = int_data("Enter size of graph: ");
	graph->node = (Node*)calloc(graph->size, sizeof(Node));
	graph->cap = 0;
	graph->names = (char **)calloc(graph->size, sizeof(char *));
}

int compare(Coords c1, Coords c2){
	return c1.x == c2.x && c1.y == c2.y;
}

int insert_node(Graph* graph, Coords c){
	int index = -1;
	int i = 0;
	for(; i < graph->size && graph->node[i].busy; i++){
		if(graph->node[i].busy == 1 && compare(graph->node[i].coords, c)){
			return -1;
		}
		if(index < 0 && graph->node[i].busy != 1){
			index = i;
		}	
	}

	if(index < 0){
		index = i;
	}

	int n = 0;
	char* g = NULL;
	do{
		n = 0;
		g = str_data("Enter name of node: ");
		for (int j = 0; j < graph->cap; j ++){
			if (graph->names[j] && strcmp(graph->names[j], g) == 0){
				n = 1;
				printf("Name is already taken.\n");
				break;
			}
		}
	}while(n);
	graph->names[graph->cap] = g;
	graph->node[index].name = g;
	graph->node[index].busy = 1;
	graph->node[index].coords = c;
	graph->node[index].first = NULL;
	graph->cap += 1;
	if(index + 1 == graph->size){
		graph->node = realloc(graph->node, (graph->size + 1) * sizeof(Node));
		memset(&graph->node[graph->size], 0, sizeof(Node));
		graph->size += 1;
		graph->names = (char **)realloc(graph->names, (graph->size + 1) * sizeof(char *));
	}
	return 0;
}

void prepend_item(Item** head, int index, float weight){
	Item* ptr = (Item*)malloc(sizeof(Item));
	ptr->index = index;
	ptr->weight = weight;
	ptr->next = *head;
	*head = ptr;
}

int in_list(Item* head, int index){
	for(Item* ptr = head; ptr; ptr = ptr->next){
		if(ptr->index == index){
			return 1;
		}
	}
	return 0;
}

int insert_link(Graph* graph, Coords c1, Coords c2, float weight){
	int index1 = -1, index2 = -1;
	for(int i = 0; graph->node[i].busy; i++){
		if(compare(graph->node[i].coords,c1)){
			index1 = i;
		}
		if(compare(graph->node[i].coords,c2)){
			index2 = i;
		}

		if(index1 > 0 && index2 > 0) break;
	}

	if(index1 < 0 || index2 < 0){
		return -1;
	}

	if(!in_list(graph->node[index1].first, index2)){
		prepend_item(&graph->node[index1].first, index2, weight);
	}
	return 0;
}

void delete_item(Item** head, int index){
	Item *ptr, *prev;
	for(ptr = *head, prev = NULL; ptr && ptr->index != index; prev = ptr, ptr = ptr->next){}
	if(!ptr) return;
	if(ptr == *head) *head = ptr->next;
	if(prev) prev->next = ptr->next;
	free(ptr);
}

void delete_list(Item** head){
	Item* ptr = *head, *prev;
    	while(ptr){
        	prev = ptr;
        	ptr = ptr->next;
        	free(prev);
    	}
    	*head = NULL;
}

int delete_node(Graph* graph, Coords c){
	int index = -1;
	for(int i = 0; i < graph->size && graph->node[i].busy; i++){
		if(graph->node[i].busy == 1 && compare(graph->node[i].coords, c)){
			index = i;
			break;
		}	
	}

	if(index < 0){
		return -1;
	}

	for(int i = 0; i < graph->size && graph->node[i].busy; i++){
		if(graph->node[i].busy == 1 && i != index){
			delete_item(&graph->node[i].first, index);
		}
	}

	graph->node[index].busy = -1;
	delete_list(&graph->node[index].first);
	free(graph->node[index].name);
	return 0;
}

int delete_link(Graph* graph, Coords c1, Coords c2){
	int index1 = -1, index2 = -1;
	for(int i = 0; graph->node[i].busy; i++){
		if(compare(graph->node[i].coords,c1)){
			index1 = i;
		}
		if(compare(graph->node[i].coords,c2)){
			index2 = i;
		}

		if(index1 > 0 && index2 > 0) break;
	}

	if(index1 < 0 || index2 < 0){
		return -1;
	}

	delete_item(&graph->node[index1].first, index2);

	return 0;
}

int graph_size(Graph graph){
	int size = 0;
	for(int i = 0;i < graph.size && graph.node[i].busy; i++, size += 1){}
	return size;
}

void insert_list(Item_e** list, int index){
	Item_e* ptr = (Item_e *)malloc(sizeof(Item_e));
	ptr->index = index;
	ptr->next = *list;
	*list = ptr;
}

int remove_list(Item_e** list){
	Item_e *ptr, *prev;
	if(!list) return -1;

	for(ptr = *list, prev = NULL; ptr && ptr->next; prev = ptr, ptr = ptr->next){}

	if(ptr == *list) *list = NULL;
	if(prev) prev->next = NULL;
	int index = ptr->index;
	free(ptr);
	return index;
}

void delete_queue(Item_e** list){
	Item_e* ptr = *list, *prev;
    	while(ptr){
    	    prev = ptr;
    	    ptr = ptr->next;
    	    free(prev);
    	}
    	*list = NULL;
}

void print_path(Item_e* path, Graph graph){
	int j = 0;
	for(Item_e* ptr = path; ptr; ptr = ptr->next){
		printf("%d: %s (%.4f %.4f)\n", j++, graph.node[ptr->index].name, graph.node[ptr->index].coords.x, graph.node[ptr->index].coords.y);
	}
	printf("\n");
}

void find_path(Graph graph, int size, int parents[size], int index1, int index2, Item_e** path){
	if(index1 == index2){
		insert_list(path, index1);
	}
	else{
		if(parents[index2] == -1){
			delete_queue(path);
		}else{
			insert_list(path, index2);
			find_path(graph, size, parents, index1, parents[index2], path);
		}
	}
}

Route search_BF(Graph graph, Coords c1, Coords c2){
	int index1 = -1, index2 = -1;
	for(int i = 0; i < graph.size && graph.node[i].busy; i++){
		if(graph.node[i].busy == 1 && compare(graph.node[i].coords, c1)){
			index1 = i;
		}
		if(graph.node[i].busy == 1 && compare(graph.node[i].coords, c2)){
			index2 = i;
		}
		if(index1 != -1 && index2 != -1){
			break;
		}
	}
	
	if(index1 < 0 || index2 < 0){
		Route route;
		route.distance = -1;
		return route;
	}

	int size = graph_size(graph);
	char visited[size];
	memset(visited, 0, size * sizeof(char));
	int parents[size];
	memset(parents, -1, size * sizeof(int));
	float distance[size];
	for(int i = 0; i < size; i++){
		distance[i] = FLT_MAX;
	}

	Item_e* list = NULL;
	insert_list(&list, index1);
	visited[index1] = 1;
	distance[index1] = 0;


	while(list){
		int cur_index = remove_list(&list);
		for(Item* ptr = graph.node[cur_index].first; ptr; ptr = ptr->next){
			if(!visited[ptr->index]){
				visited[ptr->index] = 1;
				parents[ptr->index] = cur_index;
				distance[ptr->index] = distance[cur_index] + ptr->weight;
				insert_list(&list, ptr->index);
			}
		}
		visited[cur_index] = 1;
		if(cur_index == index2) break;
	}
	if(list) delete_queue(&list);

	Item_e* path = NULL;
	find_path(graph, size, parents, index1, index2, &path);
	Route route = {distance[index2], path};

	return route;
}

int find_min(Graph graph, int size, char visited[size], float distance[size]){
	int index = -1;
	float min = FLT_MAX;
	for(int i = 0; i < size; i++){
		if(!visited[i] && distance[i] < min && graph.node[i].busy == 1){
			min = distance[i];
			index = i;
		}
	}
	return index;
}

Route search_Deikstra(Graph graph, Coords c1, Coords c2){
	int index1 = -1, index2 = -1;
	for(int i = 0; i < graph.size && graph.node[i].busy; i++){
		if(graph.node[i].busy == 1 && compare(graph.node[i].coords, c1)){
			index1 = i;
		}
		if(graph.node[i].busy == 1 && compare(graph.node[i].coords, c2)){
			index2 = i;
		}
		if(index1 != -1 && index2 != -1){
			break;
		}
	}
	
	if(index1 < 0 || index2 < 0){
		Route route;
		route.distance = -1;
		return route;
	}


	int size = graph_size(graph);
	char visited[size];
	memset(visited, 0, size * sizeof(char));
	int parents[size];
	memset(parents, -1, size * sizeof(int));
	float distance[size];
	for(int i = 0; i < size; i++){
		distance[i] = FLT_MAX;
	}

	distance[index1] = 0;
	Item_e* queue = NULL;

	int count = 0;
	for(int i = 0; i < graph.size && graph.node[i].busy; i++){
		if(graph.node[i].busy == 1){
			count++;
		}
	}

	for(int i = 0; i < count; i++){
		int cur_index = find_min(graph, size, visited, distance);
		if(cur_index == -1){
			break;
		}
		visited[cur_index] = 1;
		for(Item* ptr = graph.node[cur_index].first; ptr; ptr = ptr->next){
			if(distance[ptr->index] > distance[cur_index] + ptr->weight){
				distance[ptr->index] = distance[cur_index] + ptr->weight;
				parents[ptr->index] = cur_index;
			}
		}
	}

	Item_e* path = NULL;;
	find_path(graph, size, parents, index1, index2, &path);
	Route route = {distance[index2], path};

	return route;
}

void write_to_file(Graph graph, FILE* file){
	char cont = 0, end = 1, full_end = 2;
	for(int i = 0; i < graph.size && graph.node[i].busy; i++){
		if(graph.node[i].busy == 1){
			fwrite(&cont, sizeof(char), 1, file);
			fwrite(&graph.node[i].coords.x, sizeof(float), 1, file);
			fwrite(&graph.node[i].coords.y, sizeof(float), 1, file);
		}
	}
	fwrite(&end, sizeof(char), 1, file);
	for(int i = 0; i < graph.size && graph.node[i].busy; i++){
		if(graph.node[i].busy == 1){
			for(Item* ptr = graph.node[i].first; ptr; ptr = ptr->next){
				fwrite(&cont, sizeof(char), 1, file);
				fwrite(&graph.node[ptr->index].coords.x, sizeof(int), 1, file);
				fwrite(&graph.node[ptr->index].coords.y, sizeof(int), 1, file);
				fwrite(&ptr->weight, sizeof(float), 1, file);
			}
			fwrite(&end, sizeof(char), 1, file);
		}
	}
}

void read_from_file(Graph* graph, FILE* file){
	char c;
	for(;;){
		fread(&c, sizeof(char), 1, file);
		if(c == 0){
			Coords c;
			fread(&c.x, sizeof(float), 1, file);
			fread(&c.y, sizeof(float), 1, file);
			insert_node(graph, c);
		}else{
			break;
		}
	}
	for(int i = 0; i < graph->size && graph->node[i].busy; i++){
		for(;;){
			fread(&c, sizeof(char), 1, file);
			if(c == 0){
				Coords c;
				float weight;
				fread(&c.x, sizeof(float), 1, file);
				fread(&c.y, sizeof(float), 1, file);
				fread(&weight, sizeof(float), 1, file);
				insert_link(graph, graph->node[i].coords, c, weight);
			}
			else{
				break;
			}
		}
	}
}

void delete_graph(Graph* graph){
	for(int i = 0; i < graph->size && graph->node[i].busy; i++){
		if(graph->node[i].busy == 1){
			delete_list(&graph->node[i].first);
		}
		free(graph->names[i]);
	}
	free(graph->names);
	free(graph->node);
}

void read_graph(Graph graph){
	for(int i = 0; i < graph.size && graph.node[i].busy; i++){
		if(graph.node[i].busy != 1){
			continue;
		}
		printf("%s (%.4f %.4f): ", graph.node[i].name, graph.node[i].coords.x, graph.node[i].coords.y);
		Item* ptr = graph.node[i].first;
		while(ptr){
			printf("%s (%.4f %.4f %.4f), ", graph.node[ptr->index].name, graph.node[ptr->index].coords.x, graph.node[ptr->index].coords.y, ptr->weight);
			ptr = ptr->next;
		}
		printf("\n");
	}
}