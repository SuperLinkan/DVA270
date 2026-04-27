#include "list.h"
#include "Declarationer_&_initieringar.h"
#include <stdlib.h>
#include <assert.h>


//Returnera en tom lista - funktionen är färdig
List create_empty_list(void)
{
    return NULL;
}

//Här skapas nya noder. Denna funktion är den enda som ska använda malloc.
//Denna funktion ska i sin tur bara kallas av add_first och add_last.
//Notera att den är static och inte finns med i interfacet
static Node * create_list_node(const Data data)
{
	//glöm inte att kolla så att malloc inte returnerade NULL

	Node *new_node;  
	
	new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return NULL; 
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = NULL;

    return new_node;
	
}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List head)
{
	return head == NULL;
}

//Lägg till en nod först i listan
void add_first(List *head, List *tail, const Data data)
{
	Node *new_node = create_list_node(data);

    if (new_node == NULL)
    {
        return; 
    }

    new_node->next = *head;

    if (*head != NULL)
    {
        (*head)->previous = new_node;
    }
    else
    {
        *tail = new_node; 
    }

    *head = new_node;

}

//lägg till nod sist i listan
void add_last(List *head, List *tail, const Data data)
{
    Node *new_node = create_list_node(data);

    if (new_node == NULL)
    {
        return; 
    }

    new_node->previous = *tail;

    if (*tail != NULL)
    {
        (*tail)->next = new_node;
    }
    else
    {
        *head = new_node; 
    }

    *tail = new_node;
}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *head, List *tail)
{
    assert(*head != NULL);

    Node *temp = *head;

    if ((*head)->next != NULL)
    {
        ((*head)->next)->previous = NULL;
    }
    else
    {
        *tail = NULL;
    }

    *head = (*head)->next;

    free(temp);

}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *head, List *tail)
{
    assert(*head != NULL);

    Node *temp = *tail;

    if ((*tail)->previous != NULL)
    {
        ((*tail)->previous)->next = NULL;
    }
    else
    {
        *head = NULL;
    }

    *tail = (*tail)->previous;

    free(temp);
}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *head, List *tail)
{
	if (*head != NULL)
    {
        remove_first(head, tail);
        clear_list(head, tail);
    }

    assert(*head == NULL);
}

//Skriv ut listan genom UART
void print_list(const List head)
{
    Node *current = head;
    while (current != NULL)
    {

        new_line();
        send_int(current->data);
        
        current = current->next;
    }
    new_line();
}

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List head)
{
    assert(head != NULL);

    return head->data;
}





//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List tail)
{
    assert(tail != NULL);

    return tail->data;
}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List head)
{
    Node *current = head;
    int counter = 0;
    while (current != NULL)
    {
        counter += 1;
        current = current->next;
    }

    return counter;
}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List head, const Data data)
{
	Node *current = head;
    
    while (current != NULL)
    {
        if (current->data == data)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *head, List *tail, const Data data)
{
    if ((*head)->data == data)
    {
        remove_first(head, tail);
        return 1;
    }

    if (*head == NULL)
    {
        return 0;
    }

    remove_element(&((*head)->next), tail, data);
}


/*int search_uneven_element(const List tail)
{

    assert(tail != NULL);
    Node *current = tail;
    
    while (current != NULL && current->data %2 != 1)
    {
        if (current != NULL && current->data %2 != 0)
        {
            return 0;
        }
        current = current->previous;
    }
    return 1;
}*/
/*Data get_first_uneven_element(const List head)
{

    assert(head != NULL);
    Node *current = head;
    
    while (current != NULL && current->data %2 != 1)
    {
        
        current = current->next;
    }
    return current->data;
}*/