#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Listdata {
	char name[30];
	int id;
} listData;

typedef struct Listnode {
	listData data;
	struct ListNode* link;
} listNode;

typedef struct LinkedList {
	listNode* head;
	int length;
} linkedList;


void insertLast(linkedList* L, listData item) {
	listNode* newNode, * temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = item;
	newNode->link = NULL;
	if (L->head == NULL)
		L->head = newNode;
	else {
		temp = L->head;
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = newNode;
	}
	L->length++;
}

void printList(linkedList* L) {
	listNode* p;
	int i=1;
	p = L->head;
	printf("현재 리스트 내용 출력\n");
	while (p != NULL) {
		printf("%d번 리스트 : %s %d\n", i, p->data.name, p->data.id);
		p = p->link;
		i++;
	}
	printf("\n");
}

listNode* search(linkedList* L, int x) {
	listNode* p;
	p = L->head;
	x = atoi(gets(x));
	while (p != NULL) {
		if (p->data.id == x) {
			return p->data.name;
		}
		else {
			p = p->link;
		}
	}

	printf("해당 학생에 대한 정보를 찾을 수 없습니다.\n");
	return NULL;

}

int insert(linkedList* L, listNode* pre, listData item) {
	
	listNode* newNode;
	char insertNAME[30];
	int a=0, insertID[20], preID[20];
	
	printf("추가할 내용 (이름) : ");
	gets(insertNAME);
	strcpy(item.name, insertNAME);

	printf("추가할 내용 (학번) : ");
	gets(insertID);
	a = atoi(insertID);
	item.id = a;

	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = item;

	printf("추가할 내용의 앞 학생의 학번 : ");
	pre= search(L, preID);
	
	if (pre != NULL) {
		
		newNode->link = pre->link;
		pre->link = newNode;
		L->length++;
		printList(L);
	}
	else {
		printf("삽입을 실패했습니다.\n\n");
		return -1;
	}
	return 0;

}
	
	
int delete(linkedList* L, int x) {
	listNode* pre, *p;
	pre = (linkedList*)malloc(sizeof(linkedList));
	p = (linkedList*)malloc(sizeof(linkedList));

	p = search(L, x);
	if (p != NULL) {
		if (L->head == NULL) exit(0);
		if (p == NULL) exit(0);
		if (L->head == p) {
			L->head = p->link;

		}
		else {
			pre = L->head;
			while (pre->link != p) {
				pre = pre->link;
			}
			pre->link = p->link;

		}
		L->length--;
		printList(L);
	}
	else {
		printf("삭제를 실패했습니다.\n\n");
		return -1;
	}
	return 0;
}

void reverse(linkedList* L) {
	listNode* p, * q, * r;
	p = L->head;
	q = NULL;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
		
	}
	L->head = q;
	printList(L);
	
}

int getLength(linkedList* L) {
	return L->length;
}

int main() {
	linkedList* L, *pre;
	listData d;
	FILE* student;
	char searchID[20], deleteID[20];

	L = (linkedList*)malloc(sizeof(linkedList));
	pre = (linkedList*)malloc(sizeof(linkedList));

	L->head = NULL;
	L->length = 0;
	
	if ((student = fopen("student.txt", "r")) == NULL) {
		printf("파일열기 실패\n");
	}

	while (!feof(student)) {
		fscanf(student, "%s %d", d.name, &d.id);
		insertLast(L, d);
	}

	printList(L);

	printf("리스트 내용 탐색\n");
	printf("탐색할 학생의 학번 : ");
	printf("탐색 결과 : %s\n\n", search(L, searchID));

	printf("리스트 내용 추가\n");
	insert(L, pre, d);

	printf("리스트 내용 삭제\n");
	printf("삭제할 학생의 학번 : ");
	delete(L,deleteID);
	
	printf("리스트 내용 역순으로 출력\n");
	reverse(L);
	
	printf("리스트 노드 개수 % d",getLength(L));
	
	return 0;
}