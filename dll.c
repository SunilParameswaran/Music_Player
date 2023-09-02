
#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 

list_t *create_list() // return a newly created empty doubly linked list
{
    // DO NOT MODIFY!!!
    list_t *l = (list_t *)malloc(sizeof(list_t));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void insert_front(list_t *list, int data) // TODO: inserts data to the beginning of the linked list
{
    node_t *temp;
    temp = (node_t *)malloc(sizeof(node_t));
    if (temp == NULL)
    {
        return;
    }
    temp->data = data;
    temp->next = temp->prev = NULL;
    if (list->head == NULL)
    {
        list->head = list->tail = temp;
    }
    else
    {
        list->head->prev = temp;
        temp->next = list->head;
        list->head = temp;
    }
    list->size++;
}

void insert_back(list_t *list, int data) // TODO: inserts data to the end of the linked list
{
    node_t *temp;
    temp = (node_t *)malloc(sizeof(node_t));
    if (temp == NULL)
    {
        return;
    }

    temp->data = data;
    temp->next = temp->prev = NULL;
    if (list->head == NULL)
    {
        list->head = list->tail = temp;
    }
    else
    {
        list->tail->next = temp;
        temp->prev = list->tail;
        list->tail = temp;
    }
    list->size++;
}

void insert_after(list_t *list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
    node_t *temp;
    temp = (node_t *)malloc(sizeof(node_t));
    if (temp == NULL)
    {
        return;
    }

    temp->data = data;
    temp->next = temp->prev = NULL;
    node_t *ptr = list->head;
    while (ptr != NULL)
    {
        if (ptr->data == prev)
        {
            if (ptr->next == NULL)
            {

                ptr->next = temp;
                temp->prev = ptr;
                list->tail = temp;
                list->size++;
                break;
            }
            node_t *ptr1 = ptr->next;
            ptr->next = temp;
            temp->prev = ptr;
            temp->next = ptr1;
            ptr1->prev = temp;
            list->size++;
            break;
        }
        ptr = ptr->next;
    }
}

void delete_front(list_t *list) // TODO: delete the start node from the linked list.
{
    node_t *delNode = NULL;
    if (list->head == NULL)
    {
        return;
    }
    delNode = list->head;
    if (list->head->next == NULL && list->head->prev == NULL)
    {
        list->head = list->tail = NULL;
        list->size = 0;
        return;
    }
    list->head = list->head->next;
    list->head->prev = NULL;
    free(delNode);
     list->size--;
}

void delete_back(list_t *list) // TODO: delete the end node from the linked list.
{

      node_t *delNode = NULL;
    if (list->head == NULL)
    {
        return;
    }
    delNode = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(delNode);

    list->size--;
}

void delete_node(list_t *list, int data) // TODO: delete the node with “data” from the linked list.
{
    node_t *ptr = list->head;
    if (list->head == NULL)
    {
        return;
    }
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            if (ptr->next == NULL)
            {
                delete_back(list);
                list->size--;
                break;
            }
            if (ptr->prev == NULL)
            {
                delete_front(list);
                list->size--;
                break;
            }
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            free(ptr);
            list->size--;
            break;
        }
        ptr = ptr->next;
    }
   
}

node_t *search(list_t *list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{
    node_t *temp = list->head;
    
    if (!is_empty(list))
    {
        while (temp != NULL)
        {
            if (temp->data == data)
            {
                 return temp;
            }
            temp = temp->next;
        }
    }

    return NULL;
}

int is_empty(list_t *list) // return true or 1 if the list is empty; else returns false or 0
{
    // DO NOT MODIFY!!!
    return list->size == 0;
}

int size(list_t *list) // returns the number of nodes in the linked list.
{
    // DO NOT MODIFY!!!
    return list->size;
}

void delete_nodes(node_t *head) // helper
{
    // DO NOT MODIFY!!!
    if (head == NULL)
        return;
    delete_nodes(head->next);
    free(head);
}

void delete_list(list_t *list) // free all the contents of the linked list
{
    // DO NOT MODIFY!!!
    delete_nodes(list->head);
    free(list);
}

void display_list(list_t *list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
    // DO NOT MODIFY!!!
    node_t *it = list->head;
    while (it != NULL)
    {
        printf("%d ", it->data);
        it = it->next;
    }
    printf("\n");
}
