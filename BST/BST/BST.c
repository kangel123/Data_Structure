#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_CODE_LENGTH 7												// 관리번호 길이 정의

typedef int itemStock;
typedef struct {
	char itemCode[MAX_CODE_LENGTH];										//관리번호
	itemStock stock;													//재고
} item;

typedef struct treeNode {
	item key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* root = NULL;


void BST_print(treeNode* root) {										//출력
	if (root == NULL)return;

	BST_print(root->left);
	printf("관리번호: %s, 재고: %d \n", root->key.itemCode, root->key.stock);
	BST_print(root->right);
}

struct treeNode* BST_Insert(struct treeNode* root, item data) {			//삽입

	if (data.stock <= 0) {												//입고 수량 0개이면 예외 코드
		printf("입고 수량이 0입니다.\n");
		return root;
	}

	if (root == NULL)													//비어있는 트리
	{
		root = (treeNode*)malloc(sizeof(treeNode));
		root->key = data;
		root->left = root->right = NULL;
		return root;
	}
	else {
		if (strcmp(root->key.itemCode, data.itemCode) == 0) {			//관리번호가 같을 시
			root->key.stock = root->key.stock + data.stock;
			printf("존재하는 상품코드입니다.\n");
			printf("상품코드 %s의 재고는 %d개 입니다.\n", root->key.itemCode, root->key.stock);
		}
		else if (strcmp(root->key.itemCode, data.itemCode) == 1)						//왼쪽 서브트리로 이동
			root->left = BST_Insert(root->left, data);
		else															//오른쪽 서브트리로 이동 
			root->right = BST_Insert(root->right, data);
	}

	return root;
}

struct treeNode* BST_delete(treeNode* root, item data) {

	treeNode* del = root;			//삭제할 노드
	treeNode* parent = NULL;		//삭제할 노드의 부모노드
	treeNode* successor = NULL;    // 삭제할 노드의 왼쪽 서브트리에서 가장 큰 노드 
	treeNode* predecessor = NULL;    // successor의 부모노드 
	treeNode* child = NULL;        // 삭제할 노드의 자식 노드 

	int num;

	while (del != NULL) {		//탐색
		if (strcmp(del->key.itemCode, data.itemCode) == 0)
			break;
		parent = del;
		if (strcmp(del->key.itemCode, data.itemCode) == 1)
			del = del->left;
		else
			del = del->right;
	}

	if (del == NULL) {			//해당 관리번호를 찾지못하면
		printf("없는 관리번호입니다.\n");
		return root;
	}
	else {						//해당 관리번호를 찾으면			
		printf("상품코드 %s의 재고는 %d개 입니다.\n", del->key.itemCode, del->key.stock);
		printf("\n[출고] 출고 수량을 입력하세요. : ");
		scanf_s("%d", &num);	//출고할 수량
		data.stock = del->key.stock;
		del->key.stock -= num;

		if (del->key.stock <= 0) {
			printf("재고가 모두 소진되어 %d만 출력합니다.\n", data.stock);

			// 삭제할 노드의 자식노드가 없는 경우 
			if (del->left == NULL && del->right == NULL) {
				if (parent != NULL) {    // 부모노드가 있는 경우 
					if (parent->left == del) {    // 부모노드의 왼쪽노드가 삭제할 노드일 때 
						parent->left = NULL;
					}
					else {							// 오른쪽 일 때 
						parent->right = NULL;
					}
				}
				else {					// 삭제할 노드가 root 노드일때(노드 하나뿐)
					root = NULL;
				}
			}

			// 삭제할 노드의 자식 노드가 2개인 경우 
			else if (del->left != NULL && del->right != NULL) {
				predecessor = del;
				successor = del->left;

				while (successor->right != NULL) {    // 왼쪽 서브트리에서 가장 큰 값 찾기 
					predecessor = successor;
					successor = successor->right;
				}

				predecessor->right = successor->left;						//옮길 노드 준비
				successor->left = del->left;
				successor->right = del->right;

				if (parent != NULL) {    // 삭제할 노드의 부모노드가 있을 때 
					if (parent->left == del) {
						parent->left = successor;
					}
					else {
						parent->right = successor;
					}
				}
				else {					//삭제할 노드 root일 때
					root = successor;
				}
			}

			//     삭제할 노드의 자식 노드가 1개인 경우 
			else {  
				if (del->left != NULL) {    // 왼쪽 노드 
					child = del->left;
				}
				else {    // 오른쪽 노드 
					child = del->right;
				}

				if (parent != NULL) {    // 부모노드가 있는 경우 
					if (parent->left == del) {    // 부모노드의 왼쪽 노드로 삭제할 노드의 자식노드 연결 
						parent->left = child;
					}
					else {    // 부모노드의 오른쪽 노드로 삭제할 노드의 자식노드 연결  
						parent->right = child;
					}
				}
				else {
					root = child;
				}
			}

			free(del);
		}

	}

	return root;
}


struct treeNode* BST_search(treeNode* root, item data) {
	if (root == NULL) {
		printf("상품을 찾을 수 없습니다.\n");
		return NULL;
	}
	if (strcmp(root->key.itemCode, data.itemCode) == 0) {
		printf("상품코드 %s의 재고는 %d개 입니다.\n", root->key.itemCode, root->key.stock);
		return root;
	}
	else if (strcmp(root->key.itemCode, data.itemCode) == 1)
		return BST_search(root->left, data);
	else
		return BST_search(root->right, data);
}

int main() {
	int i, num;
	item data;
	char ID[7];

	while (1) {
		printf("*=== S E L E C T  M E N U ===*\n\n");
		printf("	1 :	재고확인\n" "	2 :	입고\n" "	3 :	출고\n ""	4 :	검색\n""	5 :	종료\n\n");
		printf("*============================*\n");

		scanf_s("%d", &i);
		switch (i) {
		case 1: {
			printf("\n[전체 재고 출력]\n\n");
			BST_print(root);
			printf("[끝]\n");
			break;
		}

		case 2: {

			printf("\n[입고] 관리번호를 입력하세요. : ");
			scanf("%s", &ID);	//입고할 관리번호
			strcpy(data.itemCode, ID);
			printf("\n[입고] 입고 수량을 입력하세요. : ");
			scanf_s("%d", &num);	//입고할 수량
			data.stock = num;
			root = BST_Insert(root, data);
			break;
		}

		case 3: {
			printf("\n[출고] 관리번호를 입력하세요. : ");
			scanf("%s", &ID);	//출고할 관리번호
			strcpy(data.itemCode, ID);
			data.stock = 0;
			root = BST_delete(root, data);
			break;
		}

		case 4: {
			printf("\n[재고 수량 검색] 관리번호를 입력하세요 : ");
			scanf("%s", &ID);
			strcpy(data.itemCode, ID);
			data.stock = 0;
			BST_search(root, data);
			break;
		}

		case 5: {
			printf("\n[종료]");
			return 0;
		}

		default:
			printf("잘못된 입력입니다.\n");
			break;
		}
	}
}