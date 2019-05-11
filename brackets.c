/*
	TASK: given a code with brackets ( "{", "}", "[", "]", "(", ")" ) and other symbols. 
	Check if the brackets are correctly placed in this code. 

	Input: program source code.
	Output: Check if the brackets are placed correctly. If not, give the index of the first error.

	Example:
		Input: {}[]
		Output: Success
	Example:
		Input: fun(var[i);
		Output: 10
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char c;
	struct node* next;
	struct node* prev;
	int position;
} node;


typedef struct stack {
	int size;
	node *top;
} stack;


char reversedBracket(char c);
void push(stack *s, char c, int position);
char pop(stack *s);
int isEmpty(stack *s);
stack *newStack();
node *newNode(char c, int position);
void checkString();
void freeStack(stack *s);

int main() {

	stack *s = newStack();
	checkString(s);
	freeStack(s);

	return 0;
	
}

/*
	This function checks string (from stdin) for correct brackets.
	Memory for stack sholud be allocated previously. 

*/
void checkString(stack *s) {
	if (!s)
		exit(1);
	
	char c;
	int n = 0;

	while ((c = getc(stdin)) != '\n') { 
		
		n++;

		if (c == '[' || c == '{' || c == '(') {
			push(s, c, n);
		}

		else if (c == ']' || c == '}' || c == ')') {
			if (isEmpty(s)) {
				printf("%d\n", n);
				return;
			}

			char top = pop(s);
			if (c != reversedBracket(top)) {
				printf("%d\n", n);
				return;
			}
		}
	}

	if (c == '\n' && isEmpty(s))
		printf("Success\n");
	else 
		printf("%d\n", s->top->position);
}


void push(struct stack *s, char c, int position) {
	
	if (!s->top) {  //if stack is empty
		s->top = newNode(c, position);
	}
	else {
		s->top->next = newNode(c, position);
		s->top->next->prev = s->top;
		s->top = s->top->next;
	}

	s->size++;
}

char pop(struct stack *s) {

	if (isEmpty(s)) {
		return -1;
	}

	char c = s->top->c;
	node *n = s->top->prev;
	free(s->top);
	s->top = n;
	s->size--;
	return c;
}

stack *newStack() {
	stack *s = (stack*)malloc(sizeof(stack));
	s->top   = NULL;
	s->size  = 0;

	return s;
}

node *newNode(char c, int position) {
	node *n 	= (node*)malloc(sizeof(node));
	n->next 	= NULL;
	n->prev 	= NULL;
	n->c 		= c;
	n->position = position;
	return n;
}

char reversedBracket(char c) {
	if (c == '{')
		return '}';
	if (c == '(')
		return ')';
	if (c == '[')
		return ']';
	return c;              //if another symbol
}

int isEmpty(stack *s) {
	return !s->top;
}

void freeStack(stack *s) {
	if (!s)
		return;

	while (pop(s) != -1);

	free(s);
}
