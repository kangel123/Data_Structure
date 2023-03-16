#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_CODE_LENGTH 7												// ������ȣ ���� ����

typedef int itemStock;
typedef struct {
	char itemCode[MAX_CODE_LENGTH];										//������ȣ
	itemStock stock;													//���
} item;

typedef struct treeNode {
	item key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* root = NULL;


void BST_print(treeNode* root) {										//���
	if (root == NULL)return;

	BST_print(root->left);
	printf("������ȣ: %s, ���: %d \n", root->key.itemCode, root->key.stock);
	BST_print(root->right);
}

struct treeNode* BST_Insert(struct treeNode* root, item data) {			//����

	if (data.stock <= 0) {												//�԰� ���� 0���̸� ���� �ڵ�
		printf("�԰� ������ 0�Դϴ�.\n");
		return root;
	}

	if (root == NULL)													//����ִ� Ʈ��
	{
		root = (treeNode*)malloc(sizeof(treeNode));
		root->key = data;
		root->left = root->right = NULL;
		return root;
	}
	else {
		if (strcmp(root->key.itemCode, data.itemCode) == 0) {			//������ȣ�� ���� ��
			root->key.stock = root->key.stock + data.stock;
			printf("�����ϴ� ��ǰ�ڵ��Դϴ�.\n");
			printf("��ǰ�ڵ� %s�� ���� %d�� �Դϴ�.\n", root->key.itemCode, root->key.stock);
		}
		else if (strcmp(root->key.itemCode, data.itemCode) == 1)						//���� ����Ʈ���� �̵�
			root->left = BST_Insert(root->left, data);
		else															//������ ����Ʈ���� �̵� 
			root->right = BST_Insert(root->right, data);
	}

	return root;
}

struct treeNode* BST_delete(treeNode* root, item data) {

	treeNode* del = root;			//������ ���
	treeNode* parent = NULL;		//������ ����� �θ���
	treeNode* successor = NULL;    // ������ ����� ���� ����Ʈ������ ���� ū ��� 
	treeNode* predecessor = NULL;    // successor�� �θ��� 
	treeNode* child = NULL;        // ������ ����� �ڽ� ��� 

	int num;

	while (del != NULL) {		//Ž��
		if (strcmp(del->key.itemCode, data.itemCode) == 0)
			break;
		parent = del;
		if (strcmp(del->key.itemCode, data.itemCode) == 1)
			del = del->left;
		else
			del = del->right;
	}

	if (del == NULL) {			//�ش� ������ȣ�� ã�����ϸ�
		printf("���� ������ȣ�Դϴ�.\n");
		return root;
	}
	else {						//�ش� ������ȣ�� ã����			
		printf("��ǰ�ڵ� %s�� ���� %d�� �Դϴ�.\n", del->key.itemCode, del->key.stock);
		printf("\n[���] ��� ������ �Է��ϼ���. : ");
		scanf_s("%d", &num);	//����� ����
		data.stock = del->key.stock;
		del->key.stock -= num;

		if (del->key.stock <= 0) {
			printf("��� ��� �����Ǿ� %d�� ����մϴ�.\n", data.stock);

			// ������ ����� �ڽĳ�尡 ���� ��� 
			if (del->left == NULL && del->right == NULL) {
				if (parent != NULL) {    // �θ��尡 �ִ� ��� 
					if (parent->left == del) {    // �θ����� ���ʳ�尡 ������ ����� �� 
						parent->left = NULL;
					}
					else {							// ������ �� �� 
						parent->right = NULL;
					}
				}
				else {					// ������ ��尡 root ����϶�(��� �ϳ���)
					root = NULL;
				}
			}

			// ������ ����� �ڽ� ��尡 2���� ��� 
			else if (del->left != NULL && del->right != NULL) {
				predecessor = del;
				successor = del->left;

				while (successor->right != NULL) {    // ���� ����Ʈ������ ���� ū �� ã�� 
					predecessor = successor;
					successor = successor->right;
				}

				predecessor->right = successor->left;						//�ű� ��� �غ�
				successor->left = del->left;
				successor->right = del->right;

				if (parent != NULL) {    // ������ ����� �θ��尡 ���� �� 
					if (parent->left == del) {
						parent->left = successor;
					}
					else {
						parent->right = successor;
					}
				}
				else {					//������ ��� root�� ��
					root = successor;
				}
			}

			//     ������ ����� �ڽ� ��尡 1���� ��� 
			else {  
				if (del->left != NULL) {    // ���� ��� 
					child = del->left;
				}
				else {    // ������ ��� 
					child = del->right;
				}

				if (parent != NULL) {    // �θ��尡 �ִ� ��� 
					if (parent->left == del) {    // �θ����� ���� ���� ������ ����� �ڽĳ�� ���� 
						parent->left = child;
					}
					else {    // �θ����� ������ ���� ������ ����� �ڽĳ�� ����  
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
		printf("��ǰ�� ã�� �� �����ϴ�.\n");
		return NULL;
	}
	if (strcmp(root->key.itemCode, data.itemCode) == 0) {
		printf("��ǰ�ڵ� %s�� ���� %d�� �Դϴ�.\n", root->key.itemCode, root->key.stock);
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
		printf("	1 :	���Ȯ��\n" "	2 :	�԰�\n" "	3 :	���\n ""	4 :	�˻�\n""	5 :	����\n\n");
		printf("*============================*\n");

		scanf_s("%d", &i);
		switch (i) {
		case 1: {
			printf("\n[��ü ��� ���]\n\n");
			BST_print(root);
			printf("[��]\n");
			break;
		}

		case 2: {

			printf("\n[�԰�] ������ȣ�� �Է��ϼ���. : ");
			scanf("%s", &ID);	//�԰��� ������ȣ
			strcpy(data.itemCode, ID);
			printf("\n[�԰�] �԰� ������ �Է��ϼ���. : ");
			scanf_s("%d", &num);	//�԰��� ����
			data.stock = num;
			root = BST_Insert(root, data);
			break;
		}

		case 3: {
			printf("\n[���] ������ȣ�� �Է��ϼ���. : ");
			scanf("%s", &ID);	//����� ������ȣ
			strcpy(data.itemCode, ID);
			data.stock = 0;
			root = BST_delete(root, data);
			break;
		}

		case 4: {
			printf("\n[��� ���� �˻�] ������ȣ�� �Է��ϼ��� : ");
			scanf("%s", &ID);
			strcpy(data.itemCode, ID);
			data.stock = 0;
			BST_search(root, data);
			break;
		}

		case 5: {
			printf("\n[����]");
			return 0;
		}

		default:
			printf("�߸��� �Է��Դϴ�.\n");
			break;
		}
	}
}