#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>



#include "list.h"

#define BUF_SIZE 1000
#define MAX_PENDENTI 10

typedef struct {
  char titolo[30];
  int sockfd;
  int valido; //0 libero 1 occupato

} LettorePendente;

int port = 8000;
LettorePendente pendenti[MAX_PENDENTI];

int num_pendenti = 0;

void gestisci_pendenti(char titolo[30], int sockfd){
  if(num_pendenti>=MAX_PENDENTI){
    printf("Coda pendenti piena lo cominico\n");
    char msg[BUF_SIZE];
    sprintf(msg,"Troppi lettori pendenti, Riprovare più tardi\n");
    send(sockfd, msg, strlen(msg),0);
    close(sockfd);
    return;

  }

  LettorePendente let;
  strcpy(let.titolo,titolo);
  let.sockfd=sockfd;
  let.valido=1;
  pendenti[num_pendenti]=let;
  num_pendenti++;
  for(int i=0; i<num_pendenti;i++){
    printf("Pendentiþ[%d]: %s",i, pendenti[i].titolo);

  }


}

void servi_pendenti(LIST libri,char titolo[30]){
  ItemType tmp;
  strcpy(tmp.titolo,titolo);


  int i = 0;
  while (i < num_pendenti) {
      if (pendenti[i].valido && strcmp(pendenti[i].titolo, titolo) == 0) {
          char msg[BUF_SIZE];
          sprintf(msg, "Il libro è ora disponibile, ti servo ora! Eccolo: %s\n", pendenti[i].titolo);
          send(pendenti[i].sockfd, msg, strlen(msg), 0);

          // Aggiorna le copie disponibili
          libri = DecreaseCopy(libri, tmp);

          close(pendenti[i].sockfd);

          // Rimuovo e compatto
          for (int j = i; j < num_pendenti - 1; j++) {
              pendenti[j] = pendenti[j + 1];
          }
          num_pendenti--;

      } else {
          i++;
      }
    }
    PrintList(libri);
  }





int main()
{

    LIST libri = NewList();
    ItemType libro_ricevuto;
    int counter=0;

    for(int i=0;i<MAX_PENDENTI;i++){
      pendenti[i].valido=0;
    }



    struct sockaddr_in serv_addr, cli_addr;
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Error opening socket");
        exit(1);
    }

    int options = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)) < 0)
    {
        perror("Error on setsockopt");
        exit(1);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("Error on binding");
        exit(1);
    }

    if (listen(sockfd, 20) == -1)
    {
        perror("Error on listen");
        exit(1);
    }

    socklen_t address_size = sizeof(cli_addr);
    char buf[BUF_SIZE];

		while (1) {
	    printf("\nIn attesa di una nuova connessione...\n\n");

	    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &address_size);
	    if (newsockfd == -1) {
	        perror("Errore nell'accept");
	        continue;
	    }

	    bzero(buf, BUF_SIZE);

	    if (recv(newsockfd, &libro_ricevuto, sizeof(ItemType), 0) == -1) {
	        perror("Errore nella ricezione");
	        close(newsockfd);
	        continue;
	    }

      ItemType tmp;
      tmp.titolo[sizeof(tmp.titolo)-1]='\0';
      tmp.num_copie=0;
      tmp.sockfd=newsockfd;

	    printf("Dati ricevuti: Titolo: %s Copie: %d\n",libro_ricevuto.titolo,libro_ricevuto.num_copie );
      ItemType* libro_trovato =Find(libri,libro_ricevuto);



      if(libro_trovato!=NULL && libro_ricevuto.num_copie!=-1){
        printf("\nLibro già Fornito impossibile rifornire\n");

      }
      else if(libro_trovato!=NULL && libro_ricevuto.num_copie==-1){ //lettore da servire
        printf("\nLibro trovato e da decrementare\n");
        strcpy(tmp.titolo,libro_ricevuto.titolo);
        tmp.num_copie=libro_trovato->num_copie;
        tmp.sockfd=newsockfd;
        libri=DecreaseCopy(libri,tmp);
        PrintList(libri);
        char msg[BUF_SIZE];
        sprintf(msg,"Ecco a te! %s buona lettura!\n", tmp.titolo);
        send(tmp.sockfd, msg, strlen(msg), 0);
        close(tmp.sockfd);
      }
      else if(libro_trovato==NULL && libro_ricevuto.num_copie==-1){ //lettore che deve diventare pendente
          printf("\nLibro non trovato sei inserito nei lettori pendenti\n");
          gestisci_pendenti(libro_ricevuto.titolo,newsockfd);

          }
      else{
        printf("\nLibro non trovato lo Fornisco\n");
        strcpy(tmp.titolo,libro_ricevuto.titolo);
        tmp.num_copie=libro_ricevuto.num_copie;
        libri=EnqueueLast(libri,tmp);
        PrintList(libri);
        servi_pendenti(libri,libro_ricevuto.titolo);


        }



      }









     return 0;
   }
