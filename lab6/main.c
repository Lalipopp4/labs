#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10
#define M 14

void wave(int pitch[N][M], int x, int y, int n){
	if ((x >= 0 && x < N && y >= 0 && y < M && (pitch[x][y] == 0 || pitch[x][y] > n)) || n == -2){
		pitch[x][y] = n;
		if (n == -2) n = 0;
		n++;
		wave(pitch, x, y + 1, n);
		wave(pitch, x, y - 1, n);
		wave(pitch, x - 1, y, n);
		wave(pitch, x + 1, y, n);
		
		
	}
}

int find_path(int pitch[N][M], int path[N * M][2], int x, int y, int i){
	if (pitch[x][y] == -2) return 0;
	if (y >= 1 && pitch[x][y - 1] + 1 == pitch[x][y]){
		path[i][0] = x;
		path[i][1] = y - 1;
		i++;
		find_path(pitch, path, x, y - 1, i);
	}
	else if (y < M - 1 && pitch[x][y + 1] + 1 == pitch[x][y]){
		path[i][0] = x;
		path[i][1] = y + 1;
		i++;
		find_path(pitch, path, x, y + 1, i);
	}
	else if (x >= 1 && pitch[x - 1][y] + 1 == pitch[x][y]){
		path[i][0] = x - 1;
		path[i][1] = y;
		i++;
		find_path(pitch, path, x - 1, y, i);
	}
	else if (x < N - 1 && pitch[x + 1][y] + 1 == pitch[x][y]){
		path[i][0] = x + 1;
		path[i][1] = y;
		i++;
		find_path(pitch, path, x + 1, y, i);
	}
	return 0;
}

int main(){
	srand(time(NULL));
	int pitch[N][M];
	int h;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			pitch[i][j] = (rand() % 3 + 1) / 2 - 1;
		}
	}
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			printf("%3d", pitch[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	int x = rand() % N;
	int y = rand() % M;
	pitch[x][y] = -2;
	printf("%d %d\n", x, y);
	int n = -2;
	int* qn = &n;
	wave(pitch, x, y, n);
	printf("\n");
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			printf("%3d", pitch[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	int x1 = rand() % N;
	int y1 = rand() % M;
	printf("%d %d\n", x1, y1);
	printf("\n");

	if (pitch[x1][y1] <= 0) return 0;
	
	int path[pitch[x1][y1]][2];
	int i = 1, j = 0;
	path[0][0] = x1;
	path[0][1] = y1;
	find_path(pitch, path, x1, y1, i);
	path[pitch[x1][y1]][0] = x;
	path[pitch[x1][y1]][1] = y;
	printf("Distance is %d.\n", pitch[x1][y1]);
	printf("Path:\n");
	for (int j = 0; j < pitch[x1][y1] + 1; j++){
		printf("%d %d\n", path[j][0], path[j][1]);
	}
	return 0;
}