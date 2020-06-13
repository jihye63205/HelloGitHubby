#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define MAX_ELEMENTS 10000
#define HEAP_FULL(n) (n == MAX_ELEMENTS -1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int u;
	int v;
	int cost;
}set;

set* minheap(set* heap,int,int,int);
set print(set* heap);
int find(int parent[],int c);
void uni(int parent[],int,int);

int i = 0,min = 0;
int *parent;

int main(int argc, char *argv[]) {
	int cnt = 0,sum = 0, c = 0,v1, v2, e,x,y,ver,edg;

	FILE *ipf, *opf;
	set* span;
	set dd;

	ipf = fopen(argv[1], "r");
	opf = fopen("fp1_result.txt", "w");

	clock_t start = clock();

	if (argc != 2) {
		printf("usage: ./mp2 input_filename\n");
		exit(1);
	}
	if (ipf == NULL) {
		printf("The input file does not exist.\n");
		exit(1);
	}

	fscanf(ipf, "%d", &ver);
	fscanf(ipf, "%d", &edg);

	span = (set*)malloc(sizeof(set)*edg);
	parent  = (int*)malloc(sizeof(int)*edg);

	while(i<edg) {
		fscanf(ipf, "%d %d %d", &v1, &v2, &e);
		parent[i] = 0;
		minheap(span, v1, v2, e);
		i++;
	}

	while (cnt != ver - 1) {
		dd = print(span);
		x = find(parent,dd.u);
		y = find(parent,dd.v);
		if(c == edg) break;
		if (x != y) {
			cnt++;
			fprintf(opf,"%d %d %d\n", dd.u, dd.v, dd.cost);
			sum+=dd.cost;
			uni(parent,dd.u, dd.v);
		}
		c++;

	}
	fprintf(opf,"%d\n", sum);

	if (cnt != ver - 1) {
		fprintf(opf,"DISCONNECTED\n");
	}
	else {
		fprintf(opf,"CONNECTED\n");
	}
	clock_t end = clock();
	printf("output written to fp1_result.txt\n");
	printf("running time: %lf seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
	fclose(ipf);
	fclose(opf);
	return 0;
}

set* minheap(set* heap, int n1,int n2,int n3) {
	int i = 0;
	if (HEAP_FULL(min)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}
	i = ++(min);
	while ((i != 1) && (n3 < heap[i / 2].cost)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].u = n1;
	heap[i].v = n2;
	heap[i].cost = n3;
	return heap;
}

set print(set *heap) {
	int parent, child,x = 1;
	set item, tmp;
	item.u = heap[x].u;
	item.v = heap[x].v;

	tmp.u = heap[min].u;
	tmp.v = heap[min].v;

	if (HEAP_EMPTY(min)) {
		return item;
	}

	item.cost = heap[x].cost;
	tmp.cost = heap[(min)--].cost;
	parent = 1;
	child = 2;
	while (child <= min) {
		if ((child < min) && (heap[child + 1].cost < heap[child].cost)) {
			child++;
		}
		if (tmp.cost <= heap[child].cost)break;
		heap[parent] = heap[child];
		parent = child;
		child = child * 2;
	}
	heap[parent] = tmp;
	return item;
}

int find(int parent[],int x) {
	if (parent[x] == 0) {
		return x;
	}
	else {
		while (parent[x] != 0) {
			x = parent[x];
		}
	}
	return x;
}

void uni(int parent[],int a, int b) {
	int x,y;

	x = find(parent,a);
	y = find(parent,b);

	if (x != y) {
		parent[x] = y;
	}

}
