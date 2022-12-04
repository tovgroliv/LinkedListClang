#ifndef LINKED_LIST_H
#define LINKED_LIST_H

	/*****************	Структуры	*********************/

	typedef struct list
	{
		struct node *	first;
		struct node *	last;
		unsigned int	count;
		unsigned int	clear;
	}
	list_t;

	/*****************	Публичные функции	*************/
	
	/**
	 * Создать новый список.
	 * Вход		:	list_t **		-	указатель на заголовок списка
	 * 				unsigned int	-	1 / 0 - освободить память значений записей / не освобождать память значений записей
	 * Выход	:	отсутствует
	*/
	void		ListCreate			(list_t **, unsigned int);
	/**
	 * Удалить список.
	 * Вход		:	list_t **		-	указатель на заголовок списка
	 * Выход	:	отсутствует
	*/
	void		ListRemove			(list_t **);
	/**
	 * Вставить запись в начало списка.
	 * Вход		:	list_t **		-	указатель списка
	 * 				void *			-	значение для вставки
	 * Выход	:	отсутствует
	*/
	void		ListInsertBottom	(list_t *, void *);
	/**
	 * Вставить запись в конец списка.
	 * Вход		:	list_t *		-	указатель списка
	 * 				void *			-	значение для вставки
	 * Выход	:	отсутствует
	*/
	void		ListInsertTop		(list_t *, void *);
	/**
	 * Получить значение записи списка по индексу.
	 * Вход		:	list_t *		-	указатель списка
	 * 				unsigned int	-	идентификатор записи
	 * Выход	:	void *			-	указатель на значение записи списка
	*/
	void *		ListGetAt			(list_t *, unsigned int);
	/**
	 * Удалить запись списка по индексу.
	 * Вход		:	list_t *		-	указатель списка
	 * 				unsigned int	-	идентификатор записи
	 * Выход	:	отсутствует
	*/
	void		ListRemoveAt		(list_t *, unsigned int);

#endif