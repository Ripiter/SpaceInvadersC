
#include <string.h>
#include <assert.h>

#include "list.h"

void list_new(list* list, int elementSize, freeFunction freeFn)
{
	assert(elementSize > 0);
	list->logicalLength = 0;
	list->elementSize = elementSize;
	list->head = list->tail = NULL;
	list->freeFn = freeFn;
}

void list_destroy(list* list)
{
	listNode* current;
	while (list->head != NULL) {
		current = list->head;
		list->head = current->next;

		if (list->freeFn)
			list->freeFn(current->data);
		else
			free(current->data);


		free(current);
		current = NULL;
	}
}

void list_prepend(list* list, void* element)
{
	listNode* node = malloc(sizeof(listNode));
	node->data = malloc(list->elementSize);
	node->data = element;

	node->next = list->head;
	list->head = node;

	// first node?
	if (!list->tail) {
		list->tail = list->head;
	}

	list->logicalLength++;
}

void list_append(list* list, void* element)
{
	listNode* node = malloc(sizeof(listNode));
	node->data = malloc(sizeof(element));
	node->next = NULL;

	node->data = element;

	if (list->logicalLength == 0) {
		list->head = list->tail = node;
	}
	else {
		list->tail->next = node;
		list->tail = node;
	}

	list->logicalLength++;
}

void list_for_each(list* list, listIterator iterator)
{
	assert(iterator != NULL);

	listNode* node = list->head;
	bool result = TRUE;
	while (node != NULL && result) {
		result = iterator(node->data);
		node = node->next;
	}
}

void list_head(list* list, void* element, bool removeFromList)
{
	assert(list->head != NULL);

	listNode* node = list->head;
	element = node->data;

	if (removeFromList) {
		list->head = node->next;
		list->logicalLength--;

		free(node->data);
		free(node);
	}
}

void list_tail(list* list, void* element)
{
	assert(list->tail != NULL);
	listNode* node = list->tail;
	element = node->data;
}

void* list_at(list* list, int at) {

	//assert(list->head != NULL);

	void* data = NULL;
	listNode* node = list->head;
	int counter = 0;
	bool done = FALSE;

	while (node != NULL && done == FALSE) {
		if (counter == at) {
			data = node->data;
			done = TRUE;
		}
		node = node->next;
		counter++;
	}
	return data;
}

void list_remove_at(list* list, int at)
{
	assert(list->head != NULL);

	//if (at == 0) {
	//	list_head(list, NULL, TRUE);
	//	return;
	//}

	listNode* node = list->head;
	listNode* nodeLag = node;
	listNode* next = node->next;
	//nodeLag = node;
	//nodeLag->data = node->data;
	//nodeLag->next = node->next;

	int counter = 0;
	bool done = FALSE;

	while (node != NULL && done == FALSE) {
		if (counter == at) {

			next = node->next;

			list->logicalLength--;

			if (list->freeFn)
				list->freeFn(node->data);
			else
				free(node->data);

			//free(node->data);
			//free(node->data);
			free(node);
			//node->data = NULL;
			node = NULL;
			done = TRUE;

			if (list->head->data == 0xdddddddd) {
				if (next != NULL) {
					list->head = next;
				}
				else {
					list->head = NULL;
				}
			}
			else {
				nodeLag->next = next;
			}
		}
		else {

			nodeLag = node;
			node = node->next;
			counter++;
		}
	}
}


int list_size(list* list)
{
	return list->logicalLength;
}

void free_list_data(void* data)
{
	free(data);
}



/*

void list_with_ints()
{
	int numbers = 10;
	printf("Generating list with the first %d positive numbers...\n", numbers);

	int i;
	list *list = malloc(sizeof(list));
	list_new(list, sizeof(int), NULL);

	for (i = 1; i <= numbers; i++) {
		list_append(list, &i);
	}

	list_for_each(list, iterate_int);


	list_destroy(list);
	printf("Successfully freed %d numbers...\n", numbers);

	free(list);
}

void list_with_strings()
{
	int numNames = 5;
	const char* names[] = { "David", "Kevin", "Michael", "Craig", "Jimi" };

	int i;
	list list;
	list_new(&list, sizeof(char*), free_data);

	char* name;
	for (i = 0; i < numNames; i++) {
		name = _strdup(names[i]);
		list_append(&list, &name);
	}

	list_for_each(&list, iterate_string);

	list_destroy(&list);
	printf("Successfully freed %d strings...\n", numNames);
}

void list_with_vectors()
{
	int numNames = 3;

	Vector2_t v = { 9 , 8 };
	Vector2_t v1 = { 69 , 68 };
	Vector2_t v2 = { 99 , 98 };

	//Vector2_t names[] = { v, v1, v2 };
	Vector2_t* names[] = { init_vector(9, 8), init_vector(69, 68), init_vector(99, 98) };

	int i;
	list* list = malloc(sizeof(list));
	list_new(list, sizeof(Vector2_t), free_data);

	for (i = 0; i < numNames; i++) {
		list_append(list, names[i]);
	}

	list_for_each(list, iterate_vector);

	list_remove_at(list, 1);
	printf("Removed\n");
	list_for_each(list, iterate_vector);

	list_destroy(list);
	printf("Successfully freed %d vectors...\n", numNames);
}


bool iterate_int(void* data)
{
	printf("Found value: %d\n", *(int*)data);
	return TRUE;
}

bool iterate_string(void* data)
{
	printf("Found string value: %s\n", *(char**)data);
	return TRUE;
}
bool iterate_vector(void* data)
{
	printf("X: %d Y:", *(int*)data);

	int* y = ((int*)data) + 1;

	printf("%d\n", *(int*)y);
	return TRUE;
}


void free_data(void* data)
{
	//free((Vector2_t*)data);
	free(data);
}
	*/