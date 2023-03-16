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
	printf("���� ����Ʈ ���� ���\n");
	while (p != NULL) {
		printf("%d�� ����Ʈ : %s %d\n", i, p->data.name, p->data.id);
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

	printf("�ش� �л��� ���� ������ ã�� �� �����ϴ�.\n");
	return NULL;

}

int insert(linkedList* L, listNode* pre, listData item) {
	
	listNode* newNode;
	char insertNAME[30];
	int a=0, insertID[20], preID[20];
	
	printf("�߰��� ���� (�̸�) : ");
	gets(insertNAME);
	strcpy(item.name, insertNAME);

	printf("�߰��� ���� (�й�) : ");
	gets(insertID);
	a = atoi(insertID);
	item.id = a;

	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = item;

	printf("�߰��� ������ �� �л��� �й� : ");
	pre= search(L, preID);
	
	if (pre != NULL) {
		
		newNode->link = pre->link;
		pre->link = newNode;
		L->length++;
		printList(L);
	}
	else {
		printf("������ �����߽��ϴ�.\n\n");
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
		printf("������ �����߽��ϴ�.\n\n");
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
		printf("���Ͽ��� ����\n");
	}

	while (!feof(student)) {
		fscanf(student, "%s %d", d.name, &d.id);
		insertLast(L, d);
	}

	printList(L);

	printf("����Ʈ ���� Ž��\n");
	printf("Ž���� �л��� �й� : ");
	printf("Ž�� ��� : %s\n\n", search(L, searchID));

	printf("����Ʈ ���� �߰�\n");
	insert(L, pre, d);

	printf("����Ʈ ���� ����\n");
	printf("������ �л��� �й� : ");
	delete(L,deleteID);
	
	printf("����Ʈ ���� �������� ���\n");
	reverse(L);
	
	printf("����Ʈ ��� ���� % d",getLength(L));
	
	return 0;
}