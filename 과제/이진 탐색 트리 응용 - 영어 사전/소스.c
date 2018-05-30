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


void preorder_traversal(TreeNode *root, FILE *file) {
	TreeNode *tmp;
	tmp = root;

	fprintf(file, "%s %s\n", &tmp->key.word, &tmp->key.meaning);
	if (tmp != NULL) {
		if (tmp->left != NULL) {
			preorder_traversal(tmp->left, file);
		}
		if (tmp->right != NULL) {
			preorder_traversal(tmp->right, file);
		}
	}
}

void inorder_traversal(TreeNode *root, FILE *file) {
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
}

void postorder_traversal(TreeNode *root, FILE *file) {
	TreeNode *tmp;
	tmp = root;

	if (tmp != NULL) {
		if (tmp->left != NULL) {
			preorder_traversal(tmp->left, file);
		}
		if (tmp->right != NULL) {
			preorder_traversal(tmp->right, file);
		}
		fprintf(file, "%s %s\n", &tmp->key.word, &tmp->key.meaning);
	}
}

TreeNode load_tree(TreeNode *root, FILE *in) {
	TreeNode *tmp;
	tmp = root;
	element fe;
	while (!feof(in)) {
		fscanf(in, "%s %s", &fe.word, &fe.meaning);
		insert_node(tmp, fe);
	}
	return *tmp;
}

void save_file(TreeNode *root) {
	if (root == NULL) {
		printf("Ʈ�� ����\n");
		return;
	}
	FILE *fp;
	int user_input_number;
	char userInput[MAX_WORD_SIZE];
	TreeNode *tmp = root;

	printf("���� �̸� �Է�: ");
	while (getchar() != '\n');
	gets(userInput);


	fp = fopen(userInput, "w");
	printf("1. ���� ��ȸ\n");
	printf("2. ���� ��ȸ\n");
	printf("3. ���� ��ȸ\n");
	scanf("%d", &user_input_number);

	switch (user_input_number) {
	case 1:
		preorder_traversal(tmp, fp);
		break;
	case 2:
		inorder_traversal(tmp, fp);
		break;
	case 3:
		postorder_traversal(tmp, fp);
		break;
	}
	fclose(fp);
}

void travesal_select(TreeNode *root) {
	if (root == NULL) {
		printf("Ʈ�� ����\n");
		return;
	}
	FILE *fp;
	int user_input_number;
	char userInput[MAX_WORD_SIZE];

	fp = fopen("tmp.txt", "w");
	printf("1. ���� ��ȸ\n");
	printf("2. ���� ��ȸ\n");
	printf("3. ���� ��ȸ\n");
	scanf("%d", &user_input_number);

	switch (user_input_number) {
	case 1:
		preorder_traversal(root, fp);
		break;
	case 2:
		inorder_traversal(root, fp);
		break;
	case 3:
		postorder_traversal(root, fp);
		break;
	}
	fclose(fp);
}
void file_open_suc(TreeNode *root) {
	FILE *fp;
	fp = fopen("tmp.txt", "rt");
	TreeNode *tmp;
	tmp = root;
	element fe;
	while (!feof(fp)) {
		fscanf(fp, "%s %s", &fe.word, &fe.meaning);
		insert_node(tmp, fe);
	}
	fclose(fp);

}
void file_open(TreeNode *root) {
	char file_name[MAX_MEANING_SIZE];
	TreeNode *tmp;
	tmp = root;
	FILE *fp;
	printf("�ҷ��� ���� �Է�(Ȯ���ڸ����): ");
	while (getchar() != '\n');
	gets(file_name);

	fp = fopen(file_name, "rt");
	int userInput;

	if (fp == NULL) {
		printf("�ٽ� ���µ� ����\n");
	}
	if (fp == NULL) {
		printf("���� ����\n");
		return;
	}

	load_tree(tmp, fp);
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
			file_open(&root);
			travesal_select(root);
			root = NULL;
			file_open_suc(&root);
			while (getchar() != '\n');
			break;

		case 'v':
			save_file(root);
			while (getchar() != '\n');
			break;
		}



	} while (command != 'q');
}
