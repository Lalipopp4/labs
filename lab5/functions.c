#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

unsigned int int_data(char* k){
	int n = 1, g;
	do{
		if (n != 1) scanf("%*s");
		printf("%s", k);
		n = scanf("%d%*c", &g);
	}while (g <= 0 || n != 1);
	return g;
}

float float_data(char d[]){
	float n;
	int h;
	do{
		printf("%s", d);
		h = scanf("%f%*c", &n);
	}while(h != 1);
	return n;
}

char* str_data(char d[]){
	printf("%s", d);
	char buf[20] = {0};
	char* res = NULL;
	int len = 0;
	int n = 0;
	do{
		n = scanf("%20[^\n]",buf);
		if(n < 0){
			if(!res) return NULL;	
		} else if(n > 0){
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res,str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		} else{
			scanf("%*c");
		}
	}while(n > 0);

	if(len > 0) res[len] = '\0';
	else res = calloc(1,sizeof(char));
	return res;
}