// ���� Ž�� Ʈ���� ����� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];		// Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
} element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// ���� e1 > e2 -> -1 ��ȯ e1�� e2���� ŭ
// ���� e1 == e2 -> 0  ��ȯ �� String�� �Ϻ��� ��ġ��
// ���� e1 < e2 -> 1 ��ȯ e1�� e2���� ����
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// ���� Ž�� Ʈ�� ��� �Լ�
void display(TreeNode *p)
{
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s", p->key.word);
		display(p->right);
		printf(")");
	}
}
// ���� Ž�� Ʈ�� Ž�� �Լ�
TreeNode *search(TreeNode *root, element key)
{
	TreeNode *p = root;
	while (p != NULL) {
		switch (compare(key, p->key)) {
		case -1:
			p = p->left;
			break;
		case 0:
			return p;
			break;
		case 1:
			p = p->right;
			break;
		}

	}
	return p; 	// Ž���� �������� ��� NULL ��ȯ
}
// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�. 
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.

void insert_node(TreeNode **root, element key)
{
	TreeNode *p, *t; // p�� �θ� ���, t�� �ڽ� ��� 
	TreeNode *n;	 // n�� ���ο� ���

	t = *root;
	p = NULL;
	// Ž���� ���� ���� 
	while (t != NULL) {
		if (compare(key, t->key) == 0) return;
		p = t;
		if (compare(key, t->key)<0) t = t->left;
		else t = t->right;
	}

	// item�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	// ������ ����
	n->key = key;
	n->left = n->right = NULL;

	// �θ� ���� ��ũ ����
	if (p != NULL)
		if (compare(key, p->key) < 0)
			p->left = n;
		else p->right = n;
	else *root = n;
}
// ���� �Լ�
void delete_node(TreeNode **root, element key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = *root;
	while (t != NULL && compare(t->key, key) != 0) {
		p = t;
		t = (compare(key, t->key)<0) ? t->left : t->right;
	}
	if (t == NULL) { 	// Ž��Ʈ���� ���� Ű
		printf("key is not in the tree");
		return;
	}
	// �ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else   p->right = NULL;
		}
		else					// �θ��尡 ������ ��Ʈ
			*root = NULL;
	}
	// �ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)	// �θ��带 �ڽĳ��� ���� 
				p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}
	else {		// �ΰ��� �ڽ��� ������ ���
		succ_p = t;
		succ = t->right;						// ������ ���� Ʈ������ �ļ��ڸ� ã�´�.

												// �ļ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		// �ļ����� �θ�� �ڽ��� ����
		if (p != NULL) {
			if (compare(succ->key, p->key) < 0) {
				p->left = succ;
			}
			else if (compare(succ->key, p->key) > 0) {
				p->right = succ;
			}
		}

		//�ļ��ڸ� ���� ���� �̵��Ѵ�.
		t->key = succ->key;
		t = succ;
	}
	free(t);
}

void inorder(TreeNode *root) {
	if (root != NULL) {
		inorder(root->left);
		insert_node(root, root->key);
		inorder(root->right);
	}
}

void preorder(TreeNode *root) {
	if (root != NULL) {
		insert_node(root, root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(TreeNode *root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		insert_node(root, root->key);
	}
}

void file_open(TreeNode *root, char input) {
	FILE *fp;
	fp = fopen(input, "r");
	int userInput;

	if (fp == NULL) {
		printf("���� ����\n");
	}
	printf("���� ��ȸ: 1\n");
	printf("���� ��ȸ: 2\n");
	printf("���� ��ȸ: 3\n");
	scanf("%d", &userInput);

	switch (userInput) {
	case 1:
		inorder(root);
		break;
	case 2:
		preorder(root);
		break;
	case 3:
		postorder(root);
		break;
	}
}

void preorder_traversal(TreeNode *root, FILE *file) {
	TreeNode *tmp;
	tmp = root;

	if (tmp != NULL) {
		if (tmp->left != NULL) {
			preorder_traversal(tmp->left, file);
		}
		fprintf(file, "%s %s\n", &tmp->key.word, &tmp->key.meaning);
		if (tmp->right != NULL) {
			preorder_traversal(tmp->right, file);
		}
	}
	if (fwrite != -1) {
		printf("�����\n");
	}
}

void save_file(TreeNode *root) {
	FILE *fp;
	char userInput[MAX_WORD_SIZE];
	TreeNode *tmp = root;

	printf("���� �̸� �Է�: ");
	while (getchar() != '\n');
	gets(userInput);


	fp = fopen(userInput, "w");
	preorder_traversal(tmp, fp);

	fclose(fp);

}

void help()
{
	printf("**************\n");
	printf("i: �Է�\n");
	printf("d: ����\n");
	printf("s: Ž��\n");
	printf("p: ���\n");
	printf("o: ���� ����\n");
	printf("v: ���� ����\n");
	printf("q: ����\n");
	printf("**************\n");
}
// ���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷� 
void main()
{
	char command;
	element e;
	TreeNode *root = NULL;
	TreeNode *tmp;
	char file_name[MAX_MEANING_SIZE];

	do {
		help();
		command = getchar();
		fflush(stdin);
		switch (command) {
		case 'i':
			printf("�ܾ�: ");
			while (getchar() != '\n');
			gets(e.word);

			printf("�ǹ�: ");
			gets(e.meaning);

			insert_node(&root, e);
			break;

		case 'd':
			printf("�ܾ�: ");
			while (getchar() != '\n');
			gets(e.word);

			delete_node(&root, e);
			break;

		case 'p':
			display(root);
			while (getchar() != '\n');
			printf("\n");
			break;

		case 's':
			printf("ã�� �ܾ�: ");
			while (getchar() != '\n');
			gets(e.word);

			tmp = search(root, e);
			if (tmp != NULL) {
				printf("�ǹ�: %s\n", tmp->key.meaning);
			}
			else {
				printf("�ش� �ܾ�� Ʈ���� �����ϴ�.\n");
			}
			break;

		case 'o':
			printf("�ҷ��� ���� �Է�(Ȯ���ڸ����): ");
			while (getchar() != '\n');
			gets(file_name);
			file_open(root, file_name);
			break;

		case 'v':
			save_file(root);
		}



	} while (command != 'q');
}
