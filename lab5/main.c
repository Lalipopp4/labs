#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "functions.h"

int G_insert_node(Graph* graph){
	Coords c;
	float n = float_data("Enter x coord: ");

	if(n) c.x = n;
	else return -1;

	n = float_data("Enter y coord: ");

	if(n) c.y = n;
	else return -1;

	int a = insert_node(graph,c);
	if(a) printf("You are goddamn wrong!\n");

	return 0;
}

int G_insert_link(Graph* graph){
	float n;
	Coords c1, c2;
	float weight;

	n = float_data("Enter x1 coord: ");

	if(n) c1.x = n;
	else return -1;

	n = float_data("Enter y1 coord: ");

	if(n) c1.y = n;
	else return -1;

	n = float_data("Enter x2 coord: ");

	if(n) c2.x = n;
	else return -1;

	n = float_data("Enter y2 coord: ");

	if(n) c2.y = n;
	else return -1;

	weight = float_data("Enter weight: ");

	if(!weight) return -1;

	int a = insert_link(graph, c1, c2, weight);
	if(a) printf("You are goddamn wrong!\n");
	return 0;
}

int G_search_BF(Graph* graph){
	float n;
	Coords c1, c2;
	
	n = float_data("Enter x1 coord: ");

	if(n) c1.x = n;
	else return -1;

	n = float_data("Enter y1 coord: ");

	if(n) c1.y = n;
	else return -1;
	
	n = float_data("Enter x2 coord: ");

	if(n) c2.x = n;
	else return -1;

	n = float_data("Enter y2 coord: ");

	if(n) c2.y = n;
	else return -1;

	Route r = search_BF(*graph, c1, c2);

	if(r.distance == -1){
		printf("No pair.\n");
	}else if(r.path){
		print_path(r.path, *graph);
		printf("Distance is %.4f.\n", r.distance);
		delete_queue(&r.path);
	}else printf("No way.\n");

	return 0;
}

int G_search_Deikstra(Graph* graph){
	float n;
	Coords c1, c2;
	
	n = float_data("Enter x1 coord: ");

	if(n) c1.x = n;
	else return -1;

	n = float_data("Enter y1 coord: ");

	if(n) c1.y = n;
	else return -1;

	n = float_data("Enter x2 coord: ");

	if(n) c2.x = n;
	else return -1;

	n = float_data("Enter y2 coord: ");

	if(n) c2.y = n;
	else return -1;

	Route r = search_Deikstra(*graph, c1, c2);

	if(r.distance == -1){
		printf("No pair.\n");
	}else if(r.path){
		print_path(r.path, *graph);
		printf("Distance is  %.4f.\n", r.distance);
		delete_queue(&r.path);
	}else printf("No way.\n");

	return 0;
}

int G_delete_node(Graph* graph){
	float n;
	Coords c;

	n = float_data("Enter x coord: ");
	if(n) c.x = n;
	else return -1;

	n = float_data("Enter y coord: ");

	if(n) c.y = n;
	else return -1;

	int a = delete_node(graph, c);
	if(a) printf("Error!\n");
	return 0;
}

int G_delete_link(Graph* graph){
	float n;
	Coords c1, c2;

	n = float_data("Enter x1 coord: ");

	if(n) c1.x = n;
	else return -1;

	n = float_data("Enter y1 coord: ");

	if(n) c1.y = n;
	else return -1;

	n = float_data("Enter x2 coord: ");

	if(n) c2.x = n;
	else return -1;

	n = float_data("Enter y2 coord: ");

	if(n) c2.y = n;
	else return -1;

	int a = delete_link(graph, c1, c2);
	if(a) printf("Error!\n");
	return 0;
}

int G_clear(Graph* graph){
	delete_graph(graph);
	create_graph(graph);
	return 0;
}

int G_read_graph(Graph* graph){
	if (graph) read_graph(*graph);
	else printf("No graph in memory.\n");
	return 0;
}

int info(){
	int g, n = 1;
	char* buf[] = {"\nChoose any  option.\n", "0) Insert node.\n", "1) Insert link.\n", "2) Read graph.\n", "3) Delete node.\n", "4) Delete link.\n", "5) Search using Deikstra.\n", "6) Search with Bellman - Ford.\n", "7) Clear graph.\n", "8 or Ctrl+D) Leave...\n", "Your choice: "};
	do{
		if (n != 1) scanf("%*s");
		for (int i = 0; i < 11; i++){
			printf("%s", buf[i]);
		}
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 8 || n != 1);
	return g;
}

int main(int argc, char const *argv[]){
	Graph graph;
	create_graph(&graph);
	FILE* file = fopen("graph.bin", "rb");
	read_from_file(&graph, file);
	fclose(file);
	puts("VV");
	int h;

	int (*actions[9])(Graph* graph) = {&G_insert_node, &G_insert_link, &G_read_graph, &G_delete_node, &G_delete_link, &G_search_Deikstra, &G_search_BF, &G_clear, NULL};

	do{
		h = info();
		if (*actions[h]) actions[h](&graph);
	}while (h < 8);

	file = fopen("graph.bin", "wb");
	write_to_file(graph, file);
	fclose(file);

	delete_graph(&graph);

	printf("GGWPBB\n");
	return 0;
}