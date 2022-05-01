/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

#define IS_EMPTY(h) ((h)->rlink) == (h)		// 공백 리스트인지 확인하는 매크로 함수

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

/* ----------- 개인 정의 함수 -----------*/
int IsInitialized(listNode* h);
int Scanf(int* k);

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("[----- [정준호]    [2020069046] -----]\n");
	
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));	// 실질적인 데이터는 갖지않는 헤드노드
	(*h)->rlink = *h;							//  이전까지의 선형 리스트에서는
	(*h)->llink = *h;							//  헤드노드라는 이름의 포인터로 첫 노드부터 이용했지만
	(*h)->key = -9999;							//  원형 리스트에서는
	return 1;									//  첫 노드가 될 수 있는 후보가, 정방향과 역방향으로 구분되어, 두 개다.
}												//  때문에 헤드노드도 쌍방향의 원래 노드 형태를 빌리되,
												//  그것은 데이터는 갖지 않는다.
												//  주의할 것으로, 앞으로 첫 노드는 h가 아닌 h->rlink

/* 메모리 해제 */
int freeList(listNode* h){
	if (IsInitialized(h)) return 1;

	listNode *goodBye = NULL;

	h->llink->rlink = NULL;			// 마지막 노드를 먼저 건드려 놓는다.

	while (h) {						// 헤드노드부터 마지막 노드까지 삭제되고
		goodBye = h;				//   h가 (이전)마지막 노드의 rlink, 즉 NULL을 이어받으면 종료.
		h = h->rlink;
		free(goodBye);
	}

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*) malloc(sizeof(listNode));
	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	/* 링크 설정. 마지막 노드의 rlink와
		헤드노드의 llink가 newNode를 가리킨다. */
	newNode->rlink = h;
	newNode->llink = h->llink;
	h->llink->rlink = newNode;
	h->llink = newNode;


	// return 1;
	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트라면, 지울 것 없음 */
	if (IS_EMPTY(h)) {
		printf("Nothing to delete.\n");
		return 1;
	}

	/* 헤드노드의 llink가 마지막 노드의 이전 노드를 가리키고,
		그것의 rlink는 헤드노드를 가리킨다. */
	h->llink = h->llink->llink;
	free(h->llink->rlink);
	h->llink->rlink = h;


	// return 1;
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*) malloc(sizeof(listNode));
	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;


	/* 링크 설정. 첫 노드의 llink와
		헤드노드의 rlink가 newNode를 가리킨다. */
	newNode->rlink = h->rlink;
	newNode->llink = h;
	h->rlink->llink = newNode;
	h->rlink = newNode;
	// 이를테면, insertFirst와 데칼코마니(좌우 대칭)

	// return 1;
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트라면, 지울 것 없음 */
	if (IS_EMPTY(h)) {
		printf("Nothing to delete.\n");
		return 1;
	}

	/* 헤드노드의 rlink가 첫 노드의 이후 노드를 가리키고,
		그것의 llink는 헤드노드를 가리킨다. */
	h->rlink = h->rlink->rlink;
	free(h->rlink->llink);
	h->rlink->llink = h;
	// 이를테면, deleteLast 와 데칼코마니(좌우 대칭)

	// return 1;
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트라면, 수행할 것 없음. */
	if (IS_EMPTY(h)) {
		printf("Nothing to invert.\n");
		return 1;
	}

	/* 모든 화살표의 방향이 반대가 되면 invert 된 것이다.
		즉, 모든 노드의 rlink, llink 를 교환한다. */
	listNode* p = h;
	listNode* temp = NULL;
	do
	{
		temp = p->rlink;
		p->rlink = p->llink;
		p->llink = temp;

		p = p->llink;
	} while (p != h);
	// 헤드노드가 움직일 필요는 없다. 다만 그것의 rlink, llink도 교환이 이루어진다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트라면, 첫 노드로 삽입 */
	if (IS_EMPTY(h)) {
		insertFirst(h, key);
		return 0;
	}

	listNode* newNode = (listNode*) malloc(sizeof(listNode));
	newNode->key = key;
	newNode->llink = NULL;
	newNode->rlink = NULL;



	listNode* searchKey = h->rlink;
	while (searchKey != h) {						// 한 바퀴 돌때 까지
		if (searchKey->key > key) {					//  더 큰 key값을 가진 노드가 발견되면
			newNode->rlink = searchKey;				//  그 노드의 llink와 그 이전 노드의 rlink가
			newNode->llink = searchKey->llink;		//  newNode를 가리키게 하며 삽입.
			searchKey->llink->rlink = newNode;		//  삽입이 이루어지면 리턴.
			searchKey->llink = newNode;

			return 0;
		}
		else
			searchKey = searchKey->rlink;
	}

	// 마지막까지 더 큰 key의 노드를 발견하지 못하면, 마지막 노드로 삽입.
	newNode->rlink = h;
	newNode->llink = h->llink;
	h->llink->rlink = newNode;
	h->llink = newNode;

	/* circular-linked-list 같은 순환 구조는, 모든 노드에서 구조적 상황이 같다.
		예를 들어, 이전까지의 선형 구조는 첫 노드, 마지막 노드에서 구조가 특수했다.
		때문에 특수한 경우의 수를 고려해야 했지만,
		순환 구조는 특수한 상황이 적다고 가정하고 일반적인 알고리즘으로 문제를 해결할 수도 있다. */

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트라면, 지울 것 없음 */
	if (IS_EMPTY(h)) {
		printf("Nothing to delete.\n");
		return 1;
	}

	listNode* searchKey = h->rlink;
	while (searchKey != h) {								// 한 바퀴 돌때 까지,
		if (searchKey->key == key) {						//  key를 갖고 있는 노드들을 제거하며,
			searchKey->rlink->llink = searchKey->llink;		//  리턴하지 않고 계속 탐색
			searchKey = searchKey->rlink;					//  key를 가진 모든 노드가 제거된다.
			free(searchKey->llink->rlink);
			searchKey->llink->rlink = searchKey;
		}
		else
			searchKey = searchKey->rlink;
	}

	return 0;
}


/*-------------- 개인 정의 함수 --------------*/

/* initialize 안하고 insert나 delete의 command를 입력하면 Segmentation fault.
	각 기능을 수행하기 전에 initialized 됐는지 확인하는 전처리용 함수. */
int IsInitialized(listNode* h) {
	if (h == NULL) return 1;
	else return 0;
}

/* main의 scanf("%d", &key)를 대체하는 함수. key에 정수를 입력 받는다 */
 /* 기존에서는 'Your key = '에 정수가 아닌 문자 등 다른 값을 입력하면
 	다음 프로그램 진행에 장애가 생긴다. 정수가 아닌 값을 입력 받으면 insert, delete 등
	수행을 하지 않고 버퍼를 비우도록 하여 문제를 해결하였다. */
int Scanf(int* k) {
	if (scanf("%d", k) == 1) {			// 제대로 정수를 입력 받으면 scanf의 반환값은 1(읽은 항목의 개수)
		while (getchar() != '\n');
		return 0;
	}
	else {
		printf("Not appropriate input. Input must be an integer. Try again.\n");
		while (getchar() != '\n');
		return 1;
	}
}