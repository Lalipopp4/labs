#include <stdio.h>

#include "deque.h"

int info(){
	int g, n = 1;
	char* buf[] = {"\nChoose any  option.\n", "0) Push in front.\n", "1) Push in back.\n", "2) Pop in front.\n", "3) Pop in back.\n", "4) Read deque from front.\n", "5) Read deque from back.\n", "6) Leave...\n", "Your choice: "};
	do{
		if (n != 1) scanf("%*s");
		for (int i = 0; i < 9; i++){
			printf("%s", buf[i]);
		}
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 6 || n != 1);
	return g;
}

int main() {
	Deque* deque = create_deque();
	void (*actions[7])(Deque* deque) = {&push_front, &push_back, &pop_front, &pop_back, &read_deque_front, &read_deque_back, NULL};
	int h;
	do{
		h = info();
		if (actions[h])
			actions[h](deque);
	}while (h < 6); 
	delete_deque(&deque);
	printf("Bye bye!\n");
	return 0;
}