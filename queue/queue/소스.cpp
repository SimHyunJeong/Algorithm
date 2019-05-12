#include <iostream>

using namespace std;

struct Node {
	int data;
	struct Node* next;
};


int main()
{
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = 10;
	head->next = NULL;


	Node* node1 = (Node*)malloc(sizeof(Node));
	node1->data = 20;
	node1->next = NULL;
	head->next = node1;
	
	Node* curr = head; //순회용 노드 생성

	while (curr != NULL) {
		printf("%d\n", curr->data);
		curr = curr->next;
	}

	free(head);
	free(node1);

}