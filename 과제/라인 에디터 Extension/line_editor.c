//
//	라인 에디터 프로그램
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 1000
#define MAX_NAME 256
void warning(char *);
void error(char *);

#define FALSE 0
#define TRUE 1

typedef struct {
	char a[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;
typedef struct {
	ListNode *head;     // 헤드 포인터
	int length;		// 노드의 개수
} ListType;

//
void insert_node(ListNode **phead, ListNode *p,
	ListNode *new_node)
{
	if (*phead == NULL) {	// 공백리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else {			 // p 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}
//
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}
// 리스트를 초기화한다.
void init(ListType *list)
{
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}
// 특정 부분 문자열 탐색
void find_line(ListType *buffer, char *value) {
	ListNode *tmp;
	tmp = buffer->head;
	int i;
	char *p;

	for (i = 0; i < buffer->length; i++) {
		p = strstr(tmp->data.a, value);
		if (p != NULL) {
			printf("해당 문자열을 찾음: %d번에 위치함\n", i + 1);
			printf("해당되는 문자열: %s", p);
		}
		tmp = tmp->link;
	}


}
// 리스트 변경
void change_line(ListType *list, element value, int position) {
	if (position < 0 || position >(list->length)) {
		printf("Position Out of Bound\n");
		return;
	}

	ListNode *tmp = list->head;
	int i;
	for (i = 0; i < position; i++) {
		tmp = tmp->link;
	}
	tmp->data = value;
}

// 리스트 리버스 기능
void reverse_lines(ListNode **phead) {
	if (*phead == NULL) {
		printf("노드가 없습니다.\n");
		return;
	}
	struct ListNode *p, *q, *r;

	p = q = r = *phead;
	p = p->link->link;
	q = q->link;
	r->link = NULL;
	q->link = r;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	*phead = q;
}
// 리스트안에서 pos 위치의 노드를 반환한다.
ListNode *get_node_at(ListType *list, int pos)
{
	int i;
	ListNode *tmp_node = list->head;
	if (pos < 0) return NULL;
	for (i = 0; i<pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}
// 리스트의 항목의 개수를 반환한다.
int get_length(ListType *list)
{
	return list->length;
}

// 주어진 위치에 데이터를 삽입한다.
void add(ListType *list, int position, element data)
{
	ListNode *p;
	if ((position >= 0) && (position <= list->length)) {
		ListNode*node = (ListNode *)malloc(sizeof(ListNode));
		if (node == NULL) error("메모리 할당에러");
		node->data = data;
		p = get_node_at(list, position - 1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}
// 리스트의 끝에 데이터를 삽입한다.
void add_last(ListType *list, element data)
{
	add(list, get_length(list), data);
}
// 리스트의 끝에 데이터를 삽입한다.
void add_first(ListType *list, element data)
{
	add(list, 0, data);
}
//
int is_empty(ListType *list)
{
	if (list->head == NULL) return 1;
	else return 0;
}
// 주어진 위치의 데이터를 삭제한다.
void delete(ListType *list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {
		ListNode *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}
//
element get_entry(ListType *list, int pos)
{
	ListNode *p;
	if (pos >= list->length) error("위치 오류");
	p = get_node_at(list, pos);
	return p->data;
}
//
void clear(ListType *list)
{
	int i;
	for (i = 0; i<list->length; i++)
		delete(list, i);
}
// 버퍼의 내용을 출력한다.
void display(ListType *buffer)
{
	int i;
	ListNode *tmp_node;
	tmp_node = buffer->head;

	printf("**************\n");
	for (i = 0; i<buffer->length; i++) {
		printf("%s", tmp_node->data.a);
		tmp_node = tmp_node->link;
	}
	printf("**************\n");
}
//
void warning(char *message)
{
	fprintf(stderr, "%s\n", message);
}
//
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//
void help()
{
	printf("**************\n");
	printf("i: 입력\n");
	printf("d: 삭제\n");
	printf("r: 파일읽기\n");
	printf("w: 파일쓰기\n");
	printf("v: 노드 역순\n");
	printf("f: 특정 부분을 포함하는 라인 검색\n");
	printf("c: 노드 데이터 변경\n");
	printf("q: 종료\n");
	printf("**************\n");
}

// 디스크 파일로부터 데이터를 읽는다.
void read_file(ListType *buffer)
{
	char fname[MAX_NAME];
	FILE *fd;
	element p;

	if (!is_empty(buffer)) {
		clear(buffer);
	}
	init(buffer);

	printf("파일 이름: ");
	scanf("%s", fname);
	if ((fd = fopen(fname, "r")) == NULL) {
		warning("파일을 열 수 없습니다.");
		return;
	}

	while (fgets(p.a, MAX_CHAR_PER_LINE, fd)) {
		add_last(buffer, p);
	}

	display(buffer);
	fclose(fd);

}
// 버퍼에 있는 데이터를 디스크 파일에 쓴다.
void write_file(ListType *buffer)
{
	FILE *fd;
	char fname[MAX_NAME];
	element p;
	int i;

	printf("파일 이름: ");
	scanf("%s", fname);
	if ((fd = fopen(fname, "w")) == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return;
	}
	for (i = 0; i < get_length(buffer); i++) {
		p = get_entry(buffer, i);
		fputs(p.a, fd);
	}
	fclose(fd);
	// ** 코드작성 ** //

	display(buffer);
}
// 하나의 라인을 지운다
void delete_line(ListType *buffer)
{

	int position;

	if (is_empty(buffer))
		printf("지울 라인이 없습니다.\n");
	else
	{
		printf("지우고 싶은 라인번호를 입력하세요: ");
		scanf("%d", &position);
		delete(buffer, position);

		// ** 코드작성 ** //
	}
	display(buffer);
}
// 하나의 라인을 삽입한다.
void insert_line(ListType *buffer)
{
	int position;
	char line[MAX_CHAR_PER_LINE];
	element p;

	printf("입력행번호를 입력하세요 (1부터): \n");
	scanf("%d", &position);
	position -= 1;
	printf("내용을 입력하세요: \n");
	gets(stdin);
	fflush(stdin);
	fgets(line, MAX_CHAR_PER_LINE, stdin);
	strcpy(p.a, line);
	add(buffer, position, p);

	display(buffer);
	// ** 코드작성 ** //

}
//
void do_command(ListType *buffer, char command)
{
	char line[MAX_CHAR_PER_LINE];
	char input[MAX_CHAR_PER_LINE];
	int n;
	element p;

	switch (command) {
	case 'd':
		delete_line(buffer);
		break;
	case 'f':
		printf("특정 문자열 입력: ");
		scanf("%s", &input);
		find_line(buffer, input);
		break;
	case 'i':
		insert_line(buffer);
		break;
	case 'r':
		read_file(buffer);
		break;
	case 'w':
		write_file(buffer);
		break;
	case 'v':
		reverse_lines(buffer);
		display(buffer);
		break;
	case 'c':
		printf("번호 입력: ");
		scanf("%d", &n);

		printf("새로 기입할 내용: ");
		gets(stdin);
		fflush(stdin);
		fgets(line, MAX_CHAR_PER_LINE, stdin);
		strcpy(p.a, line);
		change_line(buffer, p, n);
		display(buffer);
		break;
	case 'q':
		break;
	}
	// ** 코드작성 ** //

}

// 라인 에디터 메인 프로그램
void main()
{
	char command;
	ListType buffer;

	init(&buffer);
	do {
		help();
		command = getchar();
		do_command(&buffer, command);
		fflush(stdin);
	} while (command != 'q');
}
