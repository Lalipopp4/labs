#ifndef s2_l2_vector_h
#define s2_l2_vector_h

typedef struct pass{
	char* id;
	int ta;
	int ts;
}vpas;

int do_everything_vector(vpas** vect, list* l, int g);

void delete_vector(vpas** vect, int g, int* ptime, int* lengh);

void pop_vector(vpas** vect, int time, int g, int* lengh, int* ptime);

int push_vector(vpas** vect, lpas* pq, int time, int g, int* lengh, int* ptime);

void read_vector(vpas** vect, int time, int* lengh, int g);

#endif //s2_l2_vector_h
