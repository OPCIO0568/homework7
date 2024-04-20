/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	printf("[----- [김건우] [2021041010] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear) return 1;   //front와 rear가 같은 위치면 비어있는 상태이다

    else return 0; 

}

/* complete the function */
int isFull(QueueType *cQ)
{	
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) return 1; //rear의 다음 위치가 front에 위치면 꽉 찬 상태이다

	else return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{	
	if(isFull(cQ))	printf("Queue is full\n"); //꽉 차있으면 Queue is full을 출력하고 다른걸 하지 않는다
	else
	{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;  //rear를 다음 위치로 옮긴다
		cQ->queue[cQ->rear] = item; //rear위치에 item을 넣는다
	}

}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ))	printf("Queue is empty\n"); //비어있으면 Queue is empty를 출력하고 다른걸 하지 않는다
	else
	{
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front를 다음 위치로 옮긴다
		*item = cQ->queue[cQ->front]; //front위치의 값을 item에 넣는다 
		//배열에는 data가 남아있지만 front가 다음 위치로 옮겨졌기 때문에 다음번에 enQueue할 때 덮어씌워진다 출력도 front를 기준으로 출력되기에 우리는 공백으로 보인다.
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


