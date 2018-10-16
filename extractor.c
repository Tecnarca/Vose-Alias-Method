#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*example of simple input file:
5 100					//number of probabilities and number of extractions to make
0.1 0.3 0.1 0.15 0.35	//probabilities, must sum up to 1
*/

typedef struct node {
    int val;
    struct node * next;
} node_t;

int pop(node_t ** head);
void append(int val, node_t ** head);
int* vose(double* probabilities, int length, int n);
void prepare_vose(double *probabilities, int length, int *alias, double *prob);
void extract_vose(int *extracted, int *alias, double *prob, int length, int n);


int main(int argc, char** argv){
	FILE *f;
	int length, i, n;
	double *probabilities;
	int* extracted;

	if(argc != 2){
		printf("Usage: %s [File_with_probabilities]\n", argv[0]);
		return -1;
	}

	f = fopen(argv[1], "r");
	
	if(f==NULL){
		printf("Can't open the input file\n");
		return -1;
	}

	srand(time(NULL));

	// reads the input files and prepares the input
	fscanf(f, "%d", &length); //reads the number of probabilities
	fscanf(f, "%d", &n); //reads the number of extractions to make
	probabilities = malloc(sizeof(double)*length);
	for(i=0; i<length; i++)	fscanf(f, "%lf ", &probabilities[i]);

	fclose(f);
	//prepares and execute the vose's alias method
	extracted = vose(probabilities, length, n);

	//prints the results
	printf("Execution completed. Extracted indexes:\n");
	for(i=0;i<n-1;i++) printf("%d, ", extracted[i]);
	printf("%d\n", extracted[i]);
	
	return 0;
}

//for a mathematical explanation and pseudocode of the algorithm, look at http://www.keithschwarz.com/darts-dice-coins/
int* vose(double* probabilities, int length, int n){
	int *extracted = malloc(sizeof(int)*n);

	int *alias = malloc(sizeof(int)*length);
	double *prob = malloc(sizeof(double)*length);

	prepare_vose(probabilities, length, alias, prob); //prepares the arrays, complexity O(length);
	extract_vose(extracted, alias, prob, length, n); //extracts from arrays, complexity O(1) for each extraction

	return extracted;
}

void prepare_vose(double *probabilities, int length, int *alias, double *prob) {
	
	//2
	node_t *small = NULL;
	node_t *large = NULL;
	int l,g;
	int i=0;
	//3, 4

	for(;i<length;i++){
		probabilities[i]*=length;
		if(probabilities[i]<1)
			append(i,&small);
		else append(i,&large);
	}

	//5
	while(small!=NULL && large!=NULL){
		l = pop(&small);
		g = pop(&large);
		
		prob[l] = probabilities[l];
		alias[l] = g;

		probabilities[g]+=probabilities[l]-1;

		if(probabilities[g] < 1) append(g, &small);
		else append(g, &large);
	}

	while(large!=NULL){
		g = pop(&large);
		prob[g]=1;
	}

	while(small!=NULL){
		l = pop(&small);
		prob[l]=1;
		printf("l %d\n",l);
	}

}

void extract_vose(int *extracted, int *alias, double *prob, int length, int n){
	int i,j; //j is extraction number, i is the extracted side of a die, x is the extracted side of a coin
	double x; //n extractions
	for(j=0;j<n;j++){
		//1
		i = rand()%length;

		//2
		x = (double)rand() / (double)RAND_MAX ;

		//3, 4
		if(x<prob[i]) extracted[j]=i;
		else extracted[j]=alias[i];
	}

}


void append(int val, node_t ** head) {
    node_t * current;
    if(*head==NULL) {
	    current = malloc(sizeof(node_t));
	    printf("");
    	current->val = val;
    	current->next = *head;
    	*head = current;
    } else {
    	current = *head;
	    while (current->next != NULL) {
	        current = current->next;
	    }

	    current->next = malloc(sizeof(node_t));
	    current->next->val = val;
	    current->next->next = NULL;
	}
}

int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return retval;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}