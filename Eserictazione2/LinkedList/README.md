Esercizio 2

●Implement the following functions
LIST EnqueueFirst(LIST l, itemType item );
LIST DequeueLast( LIST l );
/* Inserts item in first position of list */
/* Removes the last item from list, if list is not empty */
LIST EnqueueOrdered(LIST l, itemType item );
/* Inserts the item in the list according to an order */
itemType * Find( LIST l, itemType item );
/* Finds given item in the list and returns a pointer to the item
(note: pointer to the item, not to the node type!!!) */
