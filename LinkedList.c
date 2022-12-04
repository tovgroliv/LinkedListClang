#include <LinkedList.h>
#include <stdlib.h>

/*****************	Структуры	*********************/

typedef struct node
{
	struct node *	next;
	void *			value;
}
node_t;

/**************	Статичные функции	*****************/

static	void			ListRemoveBottom	(list_t *);
static	void			ListRemoveTop		(list_t *);
static	node_t *		NodeCreate			(void *);
static	void			NodeRemove			(node_t *, unsigned int);

/**
 * Создать новый список.
 * Вход		:	list_t **		-	указатель на заголовок списка
 * 				unsigned int	-	1 / 0 - освободить память значений записей / не освобождать память значений записей
 * Выход	:	отсутствует
*/
void ListCreate(list_t ** list_tag, unsigned int clear)
{
	list_t * list	= malloc(sizeof(list_t));
	list->first		= 0;
	list->last		= 0;
	list->count		= 0;
	list->clear		= clear;
	*list_tag		= list;
}

/**
 * Удалить список.
 * Вход		:	list_t **		-	указатель на заголовок списка
 * Выход	:	отсутствует
*/
void ListRemove(list_t ** list_tag)
{
	list_t *	list	= *list_tag;
	if (!list)
	{
		return;
	}
	
	while (list->count > 0)
	{
		ListRemoveBottom(list);
	}

	free(list);
	*list_tag = 0;
}

/**
 * Вставить запись в начало списка.
 * Вход		:	list_t **		-	указатель списка
 * 				void *			-	значение для вставки
 * Выход	:	отсутствует
*/
void ListInsertBottom(list_t * list, void * value)
{
	if (!list)
	{
		return;
	}

	node_t * node	= NodeCreate(value);
	node->next		= list->first;
	
	if (!list->last)
	{
		list->last = node;
	}
	
	list->first = node;
	list->count++;
}

/**
 * Вставить запись в конец списка.
 * Вход		:	list_t *		-	указатель списка
 * 				void *			-	значение для вставки
 * Выход	:	отсутствует
*/
void ListInsertTop(list_t * list, void * value)
{
	if (!list)
	{
		return;
	}

	node_t *	node	= NodeCreate(value);
	node_t *	lt		= list->last;
	
	if (lt)
	{
		lt->next = node;
	}
	
	if (!list->first)
	{
		list->first = node;
	}
	
	list->last = node;
	list->count++;
}

/**
 * Получить значение записи списка по индексу.
 * Вход		:	list_t *		-	указатель списка
 * 				unsigned int	-	идентификатор записи
 * Выход	:	void *			-	указатель на значение записи списка
*/
void * ListGetAt(list_t * list, unsigned int id)
{
	if (!list)
	{
		return 0;
	}
	
	if (id < 0 || id >= list->count)
	{
		return 0;
	}

	node_t *		node	= 0;
	unsigned int	i		= 0;

	if (id == 0)
	{
		node = list->first;
	}
	else if (id == list->count - 1)
	{
		node = list->last;
	}
	else
	{
		node = list->first;
		i = 0;
		while (node)
		{
			if (id == i)
			{
				break;
			}
			node = node->next;
			i++;
		}
	}

	if (!node)
	{
		return 0;
	}

	return node->value;
}

/**
 * Удалить запись списка по индексу.
 * Вход		:	list_t *		-	указатель списка
 * 				unsigned int	-	идентификатор записи
 * Выход	:	отсутствует
*/
void ListRemoveAt(list_t * list, unsigned int id)
{
	if (!list)
	{
		return;
	}

	if (id == 0)
	{
		ListRemoveBottom(list);
	}
	else if (id == list->count - 1)
	{
		ListRemoveTop(list);
	}
	else
	{
		node_t *		node	= list->first;
		node_t *		next	= 0;
		unsigned int	i		= 0;

		while (node)
		{
			if (id - 1 == i)
			{
				break;
			}
			node = node->next;
			i++;
		}
		next = node->next;
		node->next = next->next;

		NodeRemove(next, list->clear);
		list->count--;
	}
}

/**
 * Создать новую запись списка.
 * Вход		:	void *			-	значение для вставки
 * Выход	:	node_t *		-	указатель новой записи списка
*/
static node_t * NodeCreate(void * value)
{
	node_t * node	= malloc(sizeof(node_t));
	node->value		= value;
	node->next		= 0;
	return node;
}

/**
 * Удалить запись списка.
 * Вход		:	node_t *		-	указатель записи списка
 *				unsigned int	-	1 / 0 - освободить память значений записей / не освобождать память значений записей
 * Выход	:	отсутствует
*/
static void NodeRemove(node_t * node, unsigned int clear)
{
	if (!node)
	{
		return;
	}

	if (clear)
	{
		if (node->value)
		{
			free(node->value);
		}
	}

	free(node);
}

/**
 * Удалить запись в начале списка.
 * Вход		:	list_t *		-	указатель списка
 * Выход	:	отсутствует
*/
static void ListRemoveBottom(list_t * list)
{
	if (!list)
	{
		return;
	}

	node_t *	first	= list->first;

	if (!list->count || !list->first)
	{
		return;
	}

	if (list->count == 1)
	{
		list->first = 0;
		list->last = 0;
	}
	else
	{
		list->first = first->next;
	}

	NodeRemove(first, list->clear);
	list->count--;
}

/**
 * Удалить запись в конце списка.
 * Вход		:	list_t *		-	указатель списка
 * Выход	:	отсутствует
*/
static void ListRemoveTop(list_t * list)
{
	if (!list)
	{
		return;
	}

	node_t *	last	= list->last;

	if (!list->count || !list->last)
	{
		return;
	}

	if (list->count == 1)
	{
		list->first = 0;
		list->last = 0;
	}
	else
	{
		node_t * pv	= list->first;
		while (pv)
		{
			if(pv->next == last)
			{
				pv->next = 0;
				list->last = pv;
			}
			pv = pv->next;
		}
	}

	NodeRemove(last, list->clear);
	list->count--;
}