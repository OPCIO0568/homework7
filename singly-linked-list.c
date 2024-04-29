/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [KIM GEON WOO] [2021041010] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	if(h == NULL) {
		printf("\"z\" first\n"); // 리스트가 초기화되지 않았을 때 출력
		return 0;
	}

	listNode* p;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key; // 새로운 노드에 key값 저장

    if(h->first == NULL || h->first->key > key) { // 처음노드가 비어있거나 key값이 처음노드의 key값보다 작을 때
        node->link = h->first; // 새로운 노드의 link를 처음노드로 설정하고
        h->first = node; 		// 처음노드를 새로운 노드로 설정
        return 0;
    }

	p = h->first; // 앞에 두개가 해당되지 않으면 p를 처음노드로 설정

	while(p->link != NULL && p->link->key < key) { // p의 다음노드가 NULL이거나 다음노드의 key값이 입력받은 key값보다 작을 때까지 반복
		p = p->link; //위에 조건이 만족할때까지 p를 다음노드로 이동
	}

    node->link = p->link; // 위에 조건이 만족되면 새로운 노드의 link를 p의 link로 설정
    p->link = node; // p의 link를 새로운 노드로 설정

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	if(h == NULL) { // 리스트가 초기화되지 않았을 때 출력
		printf("\"z\" first\n");
		return 0;
	}

	listNode* p;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key; // 새로운 노드에 key값 저장

    if(h->first == NULL) {
        node->link = h->first; // 처음노드가 비어있을 때 새로운 노드의 link를 처음노드로 설정
        h->first = node;
        return 0;
    }

	p = h->first;

	while(p->link != NULL) { // p의 다음노드가 NULL일때까지 반복
		p = p->link;
	}

    node->link = NULL; // 마지막 노드이므로 새로운 노드의 link를 NULL로 설정
    p->link = node; // p의 link를 새로운 노드로 설정

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h == NULL) { // 리스트가 초기화되지 않았을 때 출력
		printf("\"z\" first\n");
		return 0;
	}

	listNode* node = h->first; // node를 처음노드로 설정

	if(node == NULL) { // 처음노드가 비어있을 때 출력
		printf("Can't delete.\n");
		return 0;
	}

	h->first = node->link;	// 처음노드를 다음노드로 설정
	free(node); // 처음노드 메모리 해제

	return 0;


}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if(h == NULL) { // 리스트가 초기화되지 않았을 때 출력
		printf("\"z\" first\n");
		return 0;
	}

	listNode* node = h->first; // node를 처음노드로 설정

	if(node == NULL) { // 처음노드가 비어있을 때 출력
		printf("Can't delete.\n");
		return 0;
	}

	if(node->key == key) { // 처음노드의 key값이 입력받은 key값과 같을 때
		h->first = node->link; // 처음노드를 다음노드로 설정하고
		free(node); // 처음노드 메모리 해제
		return 0;
	}

	while(node->link != NULL) { 
		if(node->link->key == key) { // node의 다음노드의 key값이 입력받은 key값과 같을 때
			listNode* temp = node->link; // 다음 노드를 temp로 설정
			node->link = node->link->link; // 지금 노드의 링크를 다다음 노드로 설정한다
			free(temp); //다음 노드인 temp를 메모리 해제
			return 0;
		}
		node = node->link; // 위에 조건이 만족하지 않으면 node를 다음노드로 이동
	}



	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if(h == NULL) { // 리스트가 초기화되지 않았을 때 출력
		printf("\"z\" first\n");
		return 0;
	}

	listNode* node = h->first; // node를 처음노드로 설정

	if(node == NULL) { // 처음노드가 비어있을 때 출력
		printf("Can't delete.\n");
		return 0;
	}

	if(node->link == NULL) { // 처음노드의 다음노드가 비어있을 때
		h->first = NULL; // 처음노드를 NULL로 설정
		free(node); // 처음노드 메모리 해제
		return 0;
	}

	while(node->link->link != NULL) {
		node = node->link; // 다음노드의 다음노드가 NULL일때까지 반복
	}

	node->link = NULL; // 다음 노드가 사라지면 마지막 노드이므로 node의 링크를 NULL로 설정
	free(node->link);  // 다음 노드 메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

		if(h == NULL) { // 리스트가 초기화되지 않았을 때 출력
		printf("\"z\" first\n");
		return 0;
	}

	listNode* node = h->first; // node를 처음노드로 설정

	if(node == NULL) { // 처음노드가 비어있을 때 출력
		printf("Can't invert.\n");
		return 0;
	}

	listNode* prev = NULL; // 이전 노드를 NULL로 설정
	listNode* next = NULL; // 다음 노드를 NULL로 설정

	while(node != NULL) {
		next = node->link; // 다음 노드를 다음노드로 설정
		node->link = prev; // 현재 노드의 링크를 이전 노드로 설정
		prev = node; // 이전 노드를 현재 노드로 설정
		node = next; // 현재 노드를 다음 노드로 설정
	}

	h->first = prev; // 처음노드를 이전 노드로 설정

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

