#include <stdio.h>
#include "list.h"

int main(int argc, char* argv[]) {
    LIST mylist;
    ItemType i;

    mylist = NewList();
    printf("Fase di inizializzazione: Creata lista\n");

    printf("Fase di Controllo: ");
    if (isEmpty(mylist))
        printf(" La lista e' vuota\n");
    else
        printf(" La lista non e' vuota \n");

    printf("Fase di Inserimento dati\n");

    printf("La lista contiene %d elementi\n", getLength(mylist));

    printf("Contenuto della lista: [");
    PrintList(mylist);
    printf("]\n");

    i.value = 10;
    mylist = EnqueueLast(mylist, i);

    printf("La lista contiene %d elementi ho inserito %lf \n", getLength(mylist), i.value);

    i.value = 20;
    mylist = EnqueueLast(mylist, i);

    printf("La lista contiene %d elementi ho inserito %lf \n", getLength(mylist), i.value);

    i.value = 30;
    mylist = EnqueueLast(mylist, i);

   printf("La lista contiene %d elementi ho inserito %lf \n", getLength(mylist), i.value);
    i.value = 40;
    mylist = EnqueueLast(mylist, i);

   printf("La lista contiene %d elementi ho inserito %lf \n", getLength(mylist), i.value);

    i.value = 50;
    mylist = EnqueueLast(mylist, i);
   printf("La lista contiene %d elementi ho inserito %lf \n", getLength(mylist), i.value);
    
    i.value = 1;
    mylist = EnqueueFirst(mylist, i);
   printf("La lista contiene %d elementi ho inserito %lf \n", getLength(mylist), i.value);
    
    printf("Rimuovo l'ultimo elemento \n");
    DequeueLast(mylist);
    
    i.value = 25;
    printf("ho inserito %lf in modo ordinato\n", i.value);
    EnqueueOrdered(mylist,i);

    printf("Contenuto della lista: [");
    PrintList(mylist);
    printf("]\n");

    printf("Elemento di testa ");
    PrintItem(getHead(mylist));
    printf("\n");

    printf("Elemento di coda ");
    PrintItem(getTail(mylist));
    printf("\n");

    printf("Fase di Estrazione dati\n");

    i.value = 1.2345;
    printf("Estrazione elemento ");
    PrintItem(i);
    printf("\n");
    mylist = Dequeue(mylist, i);

    i.value = 9.9999;
    printf("Estrazione elemento ");
    PrintItem(i);
    printf("\n");
    mylist = Dequeue(mylist, i);

    i.value = 4.004;
    printf("Estrazione elemento ");
    PrintItem(i);
    printf("\n");
    mylist = Dequeue(mylist, i);

    printf("Estrazione primo elemento\n");
    mylist = DequeueFirst(mylist);

    printf("Contenuto della lista: [");
    PrintList(mylist);
    printf("]\n");

    printf("Fase di Distruzione dati\n");
    mylist = DeleteList(mylist);

    printf("Fase di Controllo: ");
    if (isEmpty(mylist))
        printf(" La lista e' vuota\n");
    else
        printf(" La lista non e' vuota \n");

    return 0;

} /* Main */
