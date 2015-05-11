/* PROGETTO ALGORITMI E STRUTTURE DATI     */
/* Sessione Estiva 2011/2012               */
/* Michele Sorcinelli, Matricola n° 248412 */

/*******************************************/

/* Inclusione delle librerie */

#include <stdio.h>    /* Libreria di Input/Output */
#include <stdlib.h>   /* Libreria Standard del C  */
#include <string.h>   /* Gestione delle strighe   */

/* Dichiarazione delle costanti simboliche */

#define LUNGHEZZA_STRINGA_CODICE_ESAME 6   /* Lunghezza della stringa del codice esame */
#define LUNGHEZZA_STRINGA_NOME_ESAME 51    /* Lunghezza della stringa del nome esame   */

typedef struct nodo_albero_bin_esami                  /* Definizione di un nodo dell'albero degli esami */
{
  char codice_esame[LUNGHEZZA_STRINGA_CODICE_ESAME],  /* Codice di identificazione dell'esame           */
       nome_esame[LUNGHEZZA_STRINGA_NOME_ESAME];      /* Nome dell'esame                                */
  int voto_esame;                                     /* Voto dell'esame                                */
  struct nodo_albero_bin_esami *sx_p,                 /* Puntatore al figlio sinistro del nodo          */
                               *dx_p;                 /* Puntatore al figlio destro del nodo            */
} nodo_albero_bin_esami_t;                            /* Ridenominazione del tipo di dato               */

typedef struct nodo_albero_bin_studenti       /* Definizione di un nodo dell'albero degli studenti */
{
  int numero_matricola,                       /* Numero di matricola dello studente                */ 
      esami_sostenuti;                        /* Numero di esami sostenuti                         */
  nodo_albero_bin_esami_t *radice_p;          /* Puntatore alla radice dell'albero degli esami     */
  struct nodo_albero_bin_studenti *sx_p,      /* Puntatore al figlio sinistro del nodo             */
                                  *dx_p;      /* Puntatore al figlio destro del nodo               */
} nodo_albero_bin_studenti_t;                 /* Ridenominazione del tipo di dato                  */

/* Dichiarazione delle funzioni */

void quicksort(int [],
	       int,
	       int);

int inserisci_studente_in_albero_bin_studenti(nodo_albero_bin_studenti_t **,
                                              int,
                                              int,
                                              nodo_albero_bin_esami_t *);

int inserisci_esame_in_albero_bin_esami(nodo_albero_bin_esami_t **,
                                        char[],
                                        char[],
                                        int);

int rimuovi_esame_da_albero_bin_esami(nodo_albero_bin_esami_t **,
                                      char []);

nodo_albero_bin_studenti_t *cerca_studente_in_albero_bin_studenti_ant(nodo_albero_bin_studenti_t *,
                                                                      int);

nodo_albero_bin_esami_t *cerca_esame_in_albero_bin_esami_ant(nodo_albero_bin_esami_t *,  
		            		                     char []); 

void visita_per_stampa_studenti_albero_bin_studenti_simm(nodo_albero_bin_studenti_t *,
			                                 FILE *,
			                                 int);

void visita_per_stampa_esami_albero_bin_esami_simm(nodo_albero_bin_esami_t *,
			                           FILE *);

void visita_per_sommatoria_voti_studente_albero_bin_esami_simm(nodo_albero_bin_esami_t *, 
                                                               int *);    

void visita_per_sommatoria_voti_albero_bin_studenti_simm(nodo_albero_bin_studenti_t *,
				                         int *);      

void visita_per_raccolta_voti_albero_bin_studenti_simm(nodo_albero_bin_studenti_t *,
					               int *,
					               int *);

void visita_per_raccolta_voti_studente_albero_bin_esami_simm(nodo_albero_bin_esami_t *,
                                                             int *,
                                                             int *); 			                     

nodo_albero_bin_studenti_t *seleziona_studente(nodo_albero_bin_studenti_t *);


void stampa_su_file(int, 
	            int, 
	            char *[], 
	            nodo_albero_bin_studenti_t *);

void modifica_voto(nodo_albero_bin_studenti_t *);

int inserisci_esame(nodo_albero_bin_studenti_t *);

int rimuovi_esame(nodo_albero_bin_studenti_t *);

void calcola_media_studente(nodo_albero_bin_studenti_t *);

void calcola_media_corso(nodo_albero_bin_studenti_t *,
		         int);

void calcola_mediana_corso(nodo_albero_bin_studenti_t *, 
	                   int);

void menu(int, 
          int, 
          int, 
          char *[],
          nodo_albero_bin_studenti_t *);
   

/* Definizione delle funzioni */

/* Algoritmo per l'ordinamento di un array di interi (Tony Hoare - 1961) */

void quicksort(int a[], /* input: array da ordinare                       */ 
               int sx,  /* lavoro: indice del primo elemento dell'array   */
               int dx)  /* lavoro: indice dell'ultimo elemento dell'array */
{
  int pivot,
      tmp,
      i,
      j;

  /* creazione della tripartizione */

  for (pivot = a[(sx + dx) / 2], i = sx, j = dx;
       (i <= j);
       )
  {
    while (a[i] < pivot)
      i++;
    while (a[j] > pivot)
      j--;	
    if (i <= j)
    {
      if (i < j)
      {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      } 
      i++; 
      j--;
    } 
  }

  /* ordinamento della prima e la terza parte quando contengono più di un elemento */

  if (sx < j)
    quicksort(a, sx, j);

  if (i < dx)
    quicksort(a, i, dx);
}

/* Algoritmo per l'inserimento di uno studente nell'albero binario degli studenti */

int inserisci_studente_in_albero_bin_studenti(nodo_albero_bin_studenti_t **radice_p,   /* lav: puntatore al puntatore alla radice dell'albero */
                                              int numero_matricola,                    /* in: numero di matricola dello studente da inserire  */
			                      int esami_sostenuti,                     /* in: numero di esami sostenuti dallo studente        */
			                      nodo_albero_bin_esami_t *radice_esami_p) /* lav: puntatore alla radice dell'albero degli esami  */
                                                                                                       
{
  int inserito; /* output: esito dell'inserimento */

  nodo_albero_bin_studenti_t *nodo_p,  /* lavoro: puntatore ad un nodo                             */
      	                     *padre_p, /* lavoro: puntatore al padre del nodo puntato da nodo_p    */
	                     *nuovo_p; /* lavoro: puntatore al nodo che conterrà il nuovo studente */
  
  /* nodo_p e padre_p vengono inizializzati con l'indirizzo della radice,
     e ad ogni iterazione padre_p prende l'indirizzo contenuto in nodo_p,
     e, a seconda che il numero di matricola dello studente da inserire 
     sia < o >= al numero di matricola dell'elemento puntato da nodo_p, 
     allora nodo_p prende rispettivamente l'indirizzo del suo figlio sx o dx;
 
     il ciclo termina quando nodo_p punta a NULL oppure punta ad un
     elemento che contiene un numero di matricola uguale a quello dello
     studente da inserire */

  for (nodo_p = padre_p = *radice_p;
       ((nodo_p != NULL) && (nodo_p->numero_matricola != numero_matricola));
       padre_p = nodo_p, nodo_p = (numero_matricola < nodo_p->numero_matricola)?
			           nodo_p->sx_p:
			           nodo_p->dx_p);

  /* se nodo_p punta ad un nodo significa che il ciclo di prima è stato interrotto
     perché il numero di matricola dello studente da inserire era già presente, ciò 
     implica che lo studente non verrà reinserito */
  
  if (nodo_p != NULL)
    inserito = 0;
  else
  {
    inserito = 1;

    /* viene allocata memoria per il nuovo nodo */
    nuovo_p = (nodo_albero_bin_studenti_t *)malloc(sizeof(nodo_albero_bin_studenti_t)); 
    
    /* viene inserito il numero di matricola */
    nuovo_p->numero_matricola = numero_matricola;              

    /* viene inserito il numero di esami sostenuti */                     
    nuovo_p->esami_sostenuti = esami_sostenuti;         

    /* viene inserito il puntatore alla radice dell'albero degli esami */                            
    nuovo_p->radice_p = radice_esami_p;                                                
    
    /* i puntatori vengono inizializzati a NULL */
    nuovo_p->sx_p = nuovo_p->dx_p = NULL;                                               
     
    /* se il nodo si trova in cima all'albero diventa la radice */
    if (nodo_p == *radice_p)       
      *radice_p = nuovo_p;   

    /* altrimenti se il numero di matricola dello studente inserito è inferiore 
       a quello dello studente contenuto nel nodo padre */

    else if (numero_matricola < padre_p->numero_matricola) 

      /* il nuovo nodo diventa figlio sinistro */
      padre_p->sx_p = nuovo_p;               
                   
    else

      /* il nuovo nodo diventa figlio destro */
      padre_p->dx_p = nuovo_p;                              
  }

  /* viene restituito il valore di esito dell'inserimento */
  return(inserito); 
} 

/* Algoritmo per l'inserimento di un esame nell'albero binario degli esami */

int inserisci_esame_in_albero_bin_esami(nodo_albero_bin_esami_t **radice_p, /* lavoro: puntatore al puntatore alla radice dell'albero */
			                char codice_esame[],                /* input: codice dell'esame da inserire                   */
			                char nome_esame[],                  /* input: nome dell'esame da inserire                     */
			                int voto_esame)                     /* input: voto dell'esame da inserire                     */

                                                                                                       
{
  int inserito, /* output: esito dell'inserimento */
             i; /* lavoro: indice per i cicli for */

  nodo_albero_bin_esami_t *nodo_p,  /* lavoro: puntatore ad un nodo                             */
      	                  *padre_p, /* lavoro: puntatore al padre del nodo puntato da nodo_p    */
	                  *nuovo_p; /* lavoro: puntatore al nodo che conterrà il nuovo esame    */
  
  /* nodo_p e padre_p vengono inizializzati con l'indirizzo della radice,
     e ad ogni iterazione padre_p prende l'indirizzo contenuto in nodo_p,
     e, a seconda che il codice dell'esame  da inserire 
     sia < o >= al codice esame dell'elemento puntato da nodo_p, 
     allora nodo_p prende rispettivamente l'indirizzo del suo figlio sx o dx;
 
     il ciclo termina quando nodo_p punta a NULL oppure punta ad un
     elemento che contiene un codice esame uguale a quello dello
     studente da inserire */

  for (nodo_p = padre_p = *radice_p;
       ((nodo_p != NULL) && (strcmp(nodo_p->codice_esame, codice_esame) != 0));
       padre_p = nodo_p, nodo_p = (strcmp(codice_esame, nodo_p->codice_esame) < 0)?
			           nodo_p->sx_p:
			           nodo_p->dx_p);

  /* se nodo_p punta ad un nodo significa che il ciclo di prima è stato interrotto
     perché il codice dell'esame da inserire era già presente, ciò implica che 
     l'esame non verrà reinserito */
  
  if (nodo_p != NULL)
    inserito = 0;
  else
  {
    inserito = 1;

    /* viene allocata memoria per il nuovo nodo */
    nuovo_p = (nodo_albero_bin_esami_t *)malloc(sizeof(nodo_albero_bin_esami_t)); 
     
    /* inserimento del codice esame */
    for (i = 0;                                                                       
         (i < LUNGHEZZA_STRINGA_CODICE_ESAME); 
         i++)
      nuovo_p->codice_esame[i] = codice_esame[i]; 

    /* inserimento del nome esame */
    for (i = 0;                                                                   
         (i < LUNGHEZZA_STRINGA_NOME_ESAME); 
         i++)
      nuovo_p->nome_esame[i] = nome_esame[i];

    /* inserimento del voto esame */
    nuovo_p->voto_esame = voto_esame;    
    
    /* i puntatori vengono inizializzati a NULL */                                     
    nuovo_p->sx_p = nuovo_p->dx_p = NULL;                                         

    /* se il nodo si trova in cima all'albero diventa la radice */
    if (nodo_p == *radice_p)       
      *radice_p = nuovo_p;  
 
    /* se il numero di matricola dello studente inserito è inferiore 
    a quello dello studente contenuto nel nodo padre */

    else if (strcmp(codice_esame, padre_p->codice_esame) < 0) 

        /* il nuovo nodo diventa figlio sinistro */
        padre_p->sx_p = nuovo_p;                              

      else

        /* il nuovo nodo diventa figlio destro */
        padre_p->dx_p = nuovo_p;                              
  }
  
  /* viene restituito il valore di esito dell'inserimento */
  return(inserito); 
} 

/* Algoritmo per la rimozione di un nodo dall'albero binario degli esami */

int rimuovi_esame_da_albero_bin_esami(nodo_albero_bin_esami_t **radice_p, /* lavoro: puntatore al puntatore alla radice dell'albero esami */
                                      char codice_esame[])                /* input: codice dell'esame da rimuovere                        */
{
  int rimosso, /* output: esito della rimozione     */
      i;       /* lavoro: contatore per i cicli for */

  nodo_albero_bin_esami_t *nodo_p,  /* lavoro: puntatore a un nodo */
                          *padre_p, /* lavoro: padre di nodo_p     */
                          *sost_p;  /* lavoro: sostituto di nodo_p */

  /* nodo_p e padre_p vengono inizializzati con l'indirizzo della radice,
     e ad ogni iterazione padre_p prende l'indirizzo contenuto in nodo_p,
     e, a seconda che il codice dell'esame da rimuovere sia < o >= al 
     codice esame dell'elemento puntato da nodo_p, allora nodo_p prende 
     rispettivamente l'indirizzo del suo figlio sx o dx;
 
     il ciclo termina quando nodo_p punta a NULL oppure punta ad un
     elemento che contiene un codice esame uguale a quello dello
     studente da rimuovere */

  for (nodo_p = padre_p = *radice_p;
       ((nodo_p != NULL) && (strcmp(nodo_p->codice_esame,codice_esame) != 0));
       padre_p = nodo_p, nodo_p = (strcmp(codice_esame,nodo_p->codice_esame) < 0)?
                                   nodo_p->sx_p:
                                   nodo_p->dx_p);

  /* se nodo_p punta a NULL significa che l'esame da rimuovere non era presente, ciò
     implica che la rimozione non può essere effettuata */

  if (nodo_p == NULL)
    rimosso = 0;
  else
  {
    rimosso = 1;

    /* se il nodo puntato da nodo_p non ha il figlio sx */
    if (nodo_p->sx_p == NULL)
    {
      /* se il nodo puntato da nodo_p si trova in cima all'albero */
      if (nodo_p == *radice_p)

        /* il figlio destro del nodo diventa la radice */
        *radice_p = nodo_p->dx_p;

      /* altrimenti, se il codice dell'esame da rimuovere è < del codice esame
         del padre del nodo puntato da nodo_p */
      else if (strcmp(codice_esame, padre_p->codice_esame) < 0)

        /* il figlio destro del nodo puntato da nodo_p diventa figlio sinistro
           del padre del nodo puntato da nodo_p */
        padre_p->sx_p = nodo_p->dx_p;

      else

        /* il figlio destro del nodo puntato da nodo_p diventa figlio destro
           del padre dell'elemento puntato da nodo_p */
        padre_p->dx_p = nodo_p->dx_p;
    }
    /* altrimenti, se il nodo puntato da nodo_p non ha il figlio destro */
    else if (nodo_p->dx_p == NULL)
    {   
      /* se il nodo puntato da nodo_p si trova in cima all'albero */
      if (nodo_p == *radice_p)

        /* il figlio sinistro del nodo diventa la radice */
        *radice_p = nodo_p->sx_p;

      /* altrimenti, se il codice dell'esame da rimuovere è < del codice esame
         del padre del nodo puntato da nodo_p */
      else if (strcmp(codice_esame, padre_p->codice_esame) < 0)

        /* il figlio sinistro del nodo puntato da nodo_p diventa figlio sinistro
           del padre del nodo puntato da nodo_p */
        padre_p->sx_p = nodo_p->sx_p;

      else

        /* il figlio sinistro del nodo puntato da nodo_p diventa figlio destro
           del padre del nodo puntato da nodo_p */
        padre_p->dx_p = nodo_p->sx_p;
    }
    
    /* altrimenti, se il nodo puntato da nodo_p ha entrambi i figli */
    else
    {
      /* sost_p prende l'indirizzo contenuto in nodo_p */
      sost_p = nodo_p;  

      /* viene iniziallizato padre_p con l'indirizzo di sost_p e nodo_p
         con l'indirizzo del figlio sinistro del nodo puntato da sost_p;

         ad ogni iterazione del ciclo padre_p prende l'indirizzo di nodo_p
         e nodo_p prende l'indirizzo del figlio destro del nodo a cui punta;

         il ciclo termina quando il nodo puntato da nodo_p non ha il figlio
         destro */

      for (padre_p = sost_p, nodo_p = sost_p->sx_p;
           (nodo_p->dx_p != NULL);
           padre_p = nodo_p, nodo_p = nodo_p->dx_p);
  
      /* sostuzione del codice esame del nodo puntato da sost_p con quello
         del nodo puntato da nodo_p */      
      for (i = 0;                                                 
           (i < LUNGHEZZA_STRINGA_CODICE_ESAME); 
           i++)
        sost_p->codice_esame[i] = nodo_p->codice_esame[i]; 

      /* sostituzione del nome esame del nodo puntato da sost_p con quello
         del nodo puntato da nodo_p */
      for (i = 0;                                            
           (i < LUNGHEZZA_STRINGA_NOME_ESAME); 
           i++)
        sost_p->nome_esame[i] = nodo_p->nome_esame[i];   

      /* sostuzione del voto esame del nodo puntato da sost_p con quello 
         del nodo puntato da nodo_p */
      sost_p->voto_esame = nodo_p->voto_esame;   
       
      /* se padre_p e sost_p puntano allo stesso nodo */     
      if (padre_p == sost_p)

        /* il figlio sinistro del nodo puntato da nodo_p diventa figlio
           sinistro del nodo puntato da padre_p */
        padre_p->sx_p = nodo_p->sx_p;

      else

        /* il figlio sinistro del nodo puntato da nodo_p diventa figlio
           destro del nodo puntato da padre_p */
        padre_p->dx_p = nodo_p->sx_p;
    }

    /* il nodo puntato da nodo_p viene rimosso dalla memoria */
    free(nodo_p);
  }  
  return(rimosso);
}

/* Algoritmo di ricerca anticipata di studenti nell'albero binario */
 
nodo_albero_bin_studenti_t 
*cerca_studente_in_albero_bin_studenti_ant(nodo_albero_bin_studenti_t *nodo_p, /* lavoro: puntatore ad un nodo dell'albero             */
				           int numero_matricola)               /* input: numero di matricola dello studente da cercare */
{
  nodo_albero_bin_studenti_t *nodo_ris_p; /* output: puntatore al nodo risultato */
   
  /* se nodo_p punta a NULL o punta a un elemento che contiene il numero
     di matricola dello studente che si sta cercando */

  if ((nodo_p == NULL) || (nodo_p->numero_matricola == numero_matricola))

    /* il nodo risultato prende l'indirizzo puntato da nodo_p */
    nodo_ris_p = nodo_p;
 
  else
  {
    /* viene reinvocata la funzione di ricerca passando il figlio sx dell'elemento puntato da nodo_p come 1° parametro */
    nodo_ris_p = cerca_studente_in_albero_bin_studenti_ant(nodo_p->sx_p,      
	                	                           numero_matricola); 

    /* se lo studente non è ancora stato trovato */
    if (nodo_ris_p == NULL) 

      /* viene reinvocata la funzione di ricerca passando il figlio dx dell'elemento puntato da nodo_p come 1° parametro */  
      nodo_ris_p = cerca_studente_in_albero_bin_studenti_ant(nodo_p->dx_p,      
	  			                             numero_matricola); 
  }

  /* viene restituito il puntatore al nodo risultato */
  return(nodo_ris_p); 
}

/* Algoritmo di ricerca anticipata di esami nell'albero binario */
 
nodo_albero_bin_esami_t *cerca_esame_in_albero_bin_esami_ant(nodo_albero_bin_esami_t *nodo_p,  /* lavoro: puntatore ad un nodo dell'albero  */
		            		                     char codice_esame[])              /* input: codice dell'esame da cercare       */
{
  nodo_albero_bin_esami_t *nodo_ris_p; /* output: puntatore al nodo risultato */
   
  /* se nodo_p punta a NULL o punta a un elemento che contiene il codice dell'esame che si sta cercando */
  if ((nodo_p == NULL) || (strcmp(nodo_p->codice_esame, codice_esame) == 0))

    /* il nodo risultato prende l'indirizzo puntato da nodo_p */
    nodo_ris_p = nodo_p;
 
  else
  {
    /* viene reinvocata la funzione di ricerca passando il figlio sx dell'elemento puntato da nodo_p come 1° parametro */
    nodo_ris_p = cerca_esame_in_albero_bin_esami_ant(nodo_p->sx_p,  
	                	                     codice_esame);  

    /* se il nodo risultato punta ancora a NULL */
    if (nodo_ris_p == NULL)

      /* viene reinvocata la funzione di ricerca passando il figlio dx dell'elemento puntato da nodo_p come 1° parametro */ 
      nodo_ris_p = cerca_esame_in_albero_bin_esami_ant(nodo_p->dx_p,  
	  			                       codice_esame); 
  }

  /* viene restituito il puntatore al nodo risultato */
  return(nodo_ris_p); 
}

/* Algoritmo di visita simmetrica dell'albero binario per stampa su file delle informazioni sugli studenti */

void visita_per_stampa_studenti_albero_bin_studenti_simm(nodo_albero_bin_studenti_t *nodo_p, /* lavoro: puntatore a un nodo dell'albero */
                                                         FILE *output,                       /* lavoro: puntatore al file d'output      */
                                                         int scelta)                         /* input: scelta dell'utente               */
{

  /* se nodo_p punta ad un nodo dell'albero */
  if (nodo_p != NULL) 
  {

    /* reinvoca la funzione passando il figlio sx del nodo puntato da nodo_p */
    visita_per_stampa_studenti_albero_bin_studenti_simm(nodo_p->sx_p, 
                                                        output,        
                                                        scelta);

    /* stampa su file delle informazioni sullo studente */

    if (scelta == 1)
    {
      fprintf(output, "Matricola n° : %d\n"
                      "Numero esami sostenuti: %d\n", 
                       nodo_p->numero_matricola,
                       nodo_p->esami_sostenuti);
    }
    else
    {
      fprintf(output, "%d\n"
                      "%d\n", 
                       nodo_p->numero_matricola,
                       nodo_p->esami_sostenuti);
    }
    
    /* visita per stampa su file dell'albero esami dello studente */

    visita_per_stampa_esami_albero_bin_esami_simm(nodo_p->radice_p, 
                                                  output); 
    if (scelta == 1)
      fprintf(output, "\n");

    /* reinvoca la funzione passando il figlio dx dell'elemento puntato da nodo_p */
    visita_per_stampa_studenti_albero_bin_studenti_simm(nodo_p->dx_p, 
                                                        output,                
                                                        scelta);
  }
}

/* Algoritmo di visita simmetrica dell'albero binario per stampa su file delle informazioni sugli esami */

void visita_per_stampa_esami_albero_bin_esami_simm(nodo_albero_bin_esami_t *nodo_p, /* lavoro: puntatore a un nodo dell'albero */
                                                   FILE *output)                    /* lavoro: puntatore al file d'output      */
{
  if (nodo_p != NULL) /* se nodo_p punta ad un nodo */
  {

    /* reinvoca la funzione passando il figlio sx dell'elemento puntato da nodo_p */
    visita_per_stampa_esami_albero_bin_esami_simm(nodo_p->sx_p,     
                                                  output);        
 
    /* stampa delle informazioni sull'esame contenuto nel nodo */

    fprintf(output, "%s", nodo_p->codice_esame); 
    fprintf(output, " %s %d\n", 
            nodo_p->nome_esame,
            nodo_p->voto_esame);

    /* reinvoca la funzione passando il figlio dx dell'elemento puntato da nodo_p */
    visita_per_stampa_esami_albero_bin_esami_simm(nodo_p->dx_p, 
                                                  output);      
  }
}

/* Funzione di visita dell'albero esami per il calcolo della sommatoria voti dello studente */

void visita_per_sommatoria_voti_studente_albero_bin_esami_simm(nodo_albero_bin_esami_t *nodo_p, /* lavoro: puntatore a un nodo dell'albero */
                                                               int *sommatoria_voti)            /* lavoro: puntatore alla sommatoria voti  */
{
  /* se nodo_p punta ad un nodo */
  if (nodo_p != NULL) 
  {

    /* reinvoca la funzione passando il figlio sx dell'elemento puntato da nodo_p */
    visita_per_sommatoria_voti_studente_albero_bin_esami_simm(nodo_p->sx_p,      
                                                              sommatoria_voti);  

    /* aggiunge il voto dell'esame alla sommatoria voti */
    *sommatoria_voti = *sommatoria_voti + nodo_p->voto_esame; 
 
    /* reinvoca la funzione passando il figlio dx dell'elemento puntato da nodo_p */
    visita_per_sommatoria_voti_studente_albero_bin_esami_simm(nodo_p->dx_p,     
                                                              sommatoria_voti); 
  }
}

/* Algoritmo di visita simmetrica dell'albero binario degli studenti per il calcolo della sommatoria voti del corso */

void visita_per_sommatoria_voti_albero_bin_studenti_simm(nodo_albero_bin_studenti_t *nodo_p, /* lavoro: puntatore ad un nodo dell'albero   */
                                                         int *sommatoria_voti)               /* lavoro: sommatoria dei voti degli studenti */
{
  /* se nodo_p punta ad un nodo */
  if (nodo_p != NULL)
  {

    /* reinvoca la funzione passando il figlio sx dell'elemento puntato da nodo_p */
    visita_per_sommatoria_voti_albero_bin_studenti_simm(nodo_p->sx_p, 
                                                        sommatoria_voti);

    /* aggiunge alla sommatoria voti la sommatoria dei voti degli esami dello studente */
    visita_per_sommatoria_voti_studente_albero_bin_esami_simm(nodo_p->radice_p, 
                                                              sommatoria_voti);

    /* reinvoca la funzione passando il figlio dx dell'elemento puntato da nodo_p */
    visita_per_sommatoria_voti_albero_bin_studenti_simm(nodo_p->dx_p, 
                                                        sommatoria_voti);
  }
}

/* Algoritmo di visita dell'albero degli studenti la raccolta dei voti degli studenti */

void visita_per_raccolta_voti_albero_bin_studenti_simm(nodo_albero_bin_studenti_t *nodo_p, /* lavoro: puntatore a un nodo dell'albero */
                                                       int *voti, /* lavoro: puntatore al primo elemento dell'array dei voti          */
                                                       int *i)    /* lavoro: puntatore all'indice di posizione                        */
{
  /* se nodo_p punta ad un nodo */
  if (nodo_p != NULL)
  {
    /* reinvoca la funzione passando il figlio sx dell'elemento puntato da nodo_p */
    visita_per_raccolta_voti_albero_bin_studenti_simm(nodo_p->sx_p, 
                                                      voti, 
                                                      i);

    /* inserisce nell'array i voti degli esami sostenuti dallo studente */
    visita_per_raccolta_voti_studente_albero_bin_esami_simm(nodo_p->radice_p, 
                                                            voti, 
                                                            i);

    /* reinvoca la funzione passando il figlio dx dell'elemento puntato da nodo_p */
    visita_per_raccolta_voti_albero_bin_studenti_simm(nodo_p->dx_p, 
                                                      voti,
                                                      i);
  }
}

/* Algoritmo di visita dell'albero degli esami per la raccolta dei voti dello studente */

void visita_per_raccolta_voti_studente_albero_bin_esami_simm(nodo_albero_bin_esami_t *nodo_p, /* lavoro: puntatore a un nodo dell'albero   */ 
                                                             int *voti, /* lavoro: puntatore al primo elemento dell'array dei voti         */
                                                             int *i)    /* lavoro: puntatore all'indice di posizione                       */

{
  /* se nodo_p punta ad un nodo */
  if (nodo_p != NULL)

  {

    /* reinvoca la funzione passando il figlio sx dell'elemento puntato da nodo_p */
    visita_per_raccolta_voti_studente_albero_bin_esami_simm(nodo_p->sx_p, 
                                                            voti, 
                                                            i);

    /* inserimento dell'esame nell'array  */
    voti[*i] = nodo_p->voto_esame; 

    /* incremento del valore puntato da i */
    *i = *i + 1;                   
    
    /* reinvoca la funzione passando il figlio dx dell'elemento puntato da nodo_p */
    visita_per_raccolta_voti_studente_albero_bin_esami_simm(nodo_p->dx_p, 
                                                            voti,
                                                            i);

  }
 
}

/* Funzione per selezionare lo studente */

nodo_albero_bin_studenti_t *seleziona_studente(nodo_albero_bin_studenti_t *radice_p) /* lavoro: puntatore alla radice dell'albero */
{
  int numero_matricola,                          /* input: numero di matricola dello studente scelto               */
      esito;                                     /* lavoro: variabile di controllo: esito scanf                    */
  nodo_albero_bin_studenti_t *studente_p = NULL; /* lavoro: puntatore al nodo che contiene lo studente selezionato */
  
  /* acquisizione del numero di matricola da stdin */

  printf("\nInserire il numero di matricola dello studente: ");
  do  
  {
    esito = scanf("%d", &numero_matricola); 

    /* se viene inserito un valore non valido */
    if (esito != 1 || numero_matricola < 0)
    {   
      printf("Numero di matricola non valido\n... ");

      /* pulizia del file stdin */
      while((getchar()) != '\n');      
    }
  }   
  while (esito != 1 || numero_matricola < 0);

  /* ricerca dello studente selezionato */
  studente_p = cerca_studente_in_albero_bin_studenti_ant(radice_p, 
                                                         numero_matricola);
  
  /* stampa del messaggio di errore se lo studente non viene trovato */
  if (studente_p == NULL)
    printf("Studente non trovato!\n");

  /* viene restituito il puntatore al nodo contenente lo studente selezionato */
  return(studente_p);                          
}


/* Funzione per la stampa su file dei valori */

void stampa_su_file(int numero_studenti,                  /* input: numero di studenti frequentanti il corso                            */
                    int argc,                             /* lavoro: numero di stringhe del comando con cui viene lanciato il programma */
                    char *argv[],                         /* lavoro: stringhe contenute nel comando con cui viene lanciato il programma */
                    nodo_albero_bin_studenti_t *radice_p) /* lavoro: puntatore alla radice dell'albero binario                          */
{
  int scelta,   /* input: scelta dell'utente */
      esito;    /* lavoro: esito scanf       */ 
 
  FILE *output; /* lavoro: puntatore al file di output */

  /* se è stato specificato un file di output nel comando di lancio del programma */
  if(argc >= 3)
  {
    /* apri quel file */
    output = fopen(argv[2], "w"); 
    printf("\nScegliere il formato del file di output:\n"
           "1) File di migliore leggibilità per l'utente\n"
           "2) File riutilizzabile dal programma\n... ");

    /* acquisisci da stdin la scelta dell'utente */
    do
    {
      esito = scanf("%d", &scelta);
      /* se la scelta non è valida */
      if (esito != 1 || scelta < 1 || scelta > 2)
      {
        printf("Scelta non valida\n... ");

        /* pulizia del file stdin */
        while((getchar()) != '\n'); 
        
      }
    }
    while (esito != 1 || scelta < 1 || scelta > 2);
    
    /* stampa del numero totale di studenti frequentanti il corso */
    if (scelta == 1)
      fprintf(output, 
              "Numero di studenti frequentanti il corso: %d\n\n", 
              numero_studenti);
    else 
      fprintf(output, "%d\n", numero_studenti);

    /* stampa delle informazioni sugli studenti */
    visita_per_stampa_studenti_albero_bin_studenti_simm(radice_p, 
                                                        output, 
                                                        scelta);

    printf("\nScrittura su \"%s\" completata!\n", argv[2]);

    /* chiudi il file */
    fclose(output); 
  }

  /* se non è stato specificato un file di output */
  else 
    printf("\nAttenzione: non è stato specificato nessun file di destinazione!\n\n"
           "Per favore rilanciare il programma con i parametri adeguati:\n"
           "%s <percorso file di input> <percorso file di output>\n"
           "(se il file è nella dir. di lavoro basta specificarne il nome)\n", 
           argv[0]);
}

/* Funzione per la modifica del voto di un esame */

void modifica_voto(nodo_albero_bin_studenti_t *radice_p) /* lavoro: puntatore alla radice dell'albero studenti */
{
  
  nodo_albero_bin_studenti_t *studente_p;            /* lavoro: studente che ha sostenuto l'esame con il voto da modificare */

  char codice_esame[LUNGHEZZA_STRINGA_CODICE_ESAME], /* input: codice dell'esame con il voto da modificare   */
       carattere_acquisito = '~';                    /* lavoro: variabile usata per acquisizioni e controlli */

  int esito,            /* lavoro: esito scanf               */
      voto_esame,       /* input: nuovo voto dell'esame      */
      controllo_errori, /* lavoro: controllo su codice esame */
      i;                /* lavoro: indice per i cicli        */

  nodo_albero_bin_esami_t *esame_p; /* lavoro: puntatore al nodo dell'albero esami che contiene l'esame con il voto da modificare */
  
  /* viene selezionato lo studente */
  studente_p = seleziona_studente(radice_p); 

  /* se lo studente viene trovato */
  if (studente_p != NULL)
  {
    while (carattere_acquisito != '\n')
      carattere_acquisito = getchar(); 

    /* acquisizione da stdin del codice dell'esame da modificare */ 
    printf("Inserire il codice dell'esame da modificare: ");
    
    /* il ciclo do/while si ripete se il codice inserito da tastiera è troppo corto oppure se il codice contiene caratteri non alfanumerici*/ 
    do
    {
      controllo_errori = 0;
      carattere_acquisito = '~';

      for (i = 0;
           ((i < (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)) && (carattere_acquisito != '\n') && (carattere_acquisito != ' '));
           i++)
      {
        carattere_acquisito = getchar();
        if ((carattere_acquisito != '\n') && (carattere_acquisito != ' '))
          codice_esame[i] = carattere_acquisito;
        else
        {
          i--;
          printf("I codici esame devono essere di %d caratteri alfanumerici!\n... ",
                 (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));
        }

        /* se il codice esame contiene caratteri non alfanumerici */
        if (codice_esame[i] < '0' || 
            (codice_esame[i] > '9' && codice_esame[i] < 'A') || 
            (codice_esame[i] > 'Z' && codice_esame[i] < 'a') || 
            codice_esame[i] > 'z')
        {
          controllo_errori = 1;
        }
      }
      codice_esame[i] = '\0';
    }
    while ((strlen(codice_esame) != (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)) || (controllo_errori == 1));

    carattere_acquisito = getchar();   

    /* se l'utente ha inserito un codice esame troppo lungo */
    if (carattere_acquisito != '\n')
    {
      printf("Il codice esame è stato abbreviato a %d caratteri!\n",
             (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));  
     
      /* ripulisci il file stdin */
      while (carattere_acquisito != '\n')
        carattere_acquisito = getchar();
    }
 
    /* ricerca dell'esame */
    esame_p = cerca_esame_in_albero_bin_esami_ant(studente_p->radice_p, 
                                                  codice_esame);

    /* se l'esame non viene trovato */
    if (esame_p == NULL)
      printf("L'esame \"%s\" non è presente!\n", codice_esame);
    else
    {
      /* acquisizione da stdin del nuovo voto dell'esame */
      printf("Inserire il nuovo voto per l'esame \"%s\" : \"%s\": ", 
             esame_p->codice_esame, esame_p->nome_esame);
      do
      {
        esito = scanf("%d", &voto_esame);

        /* se il voto non è valido */
        if (esito != 1 || voto_esame < 18 || voto_esame > 30)
        {
          printf("Voto non valido!\n... ");

          /* pulizia del file stdin */
          while((getchar()) != '\n'); 
        }
      }
      while (esito != 1 || voto_esame < 18 || voto_esame > 30);

      /* scrittura del nuovo voto */
      esame_p->voto_esame = voto_esame; 
      printf("Voto modificato!\n");
    }
  }   
}

/* Funzione per l'inserimento di un nuovo esame */

int inserisci_esame(nodo_albero_bin_studenti_t *radice_p) /* lavoro: puntatore alla radice dell'albero */
{
  char codice_esame[LUNGHEZZA_STRINGA_CODICE_ESAME],  /* input: codice dell'esame da inserire                 */
       nome_esame[LUNGHEZZA_STRINGA_NOME_ESAME],      /* input: nome dell'esame da inserire                   */
       carattere_acquisito = '~';                     /* lavoro: variabile usata per acquisizioni e controlli */
  
  int voto_esame = 0,                                 /* input: voto dell'esame da inserire    */
      inserito = 0,                                   /* output: esito dell'inserimento        */
      controllo_errori,                               /* lavoro: controllo su codice esame     */
      i,                                              /* lavoro: indice per i cicli for        */
      esito;                                          /* lavoro: esito scanf                   */

  nodo_albero_bin_studenti_t *studente_p;    /* lavoro: puntatore al nodo che contiene lo studente 
                                                che ha sostenuto il nuovo esame da inserire        */

  /* viene selezionato lo studente */
  studente_p = seleziona_studente(radice_p); 

  /* se lo studente viene trovato */
  if (studente_p != NULL) 

  {
       
    while (carattere_acquisito != '\n')
      carattere_acquisito = getchar(); 

    /* acquisizione da stdin del codice dell'esame da inserire */ 
    printf("Inserire il codice dell'esame da inserire: ");
    
    /* il ciclo do/while si ripete se il codice inserito da tastiera è troppo corto */ 
    do
    {
      controllo_errori = 0;
      carattere_acquisito = '~';

      for (i = 0;
           ((i < (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)) && (carattere_acquisito != '\n') && (carattere_acquisito != ' '));
           i++)
      {
        carattere_acquisito = getchar();
        if ((carattere_acquisito != '\n') && (carattere_acquisito != ' '))
          codice_esame[i] = carattere_acquisito;
        else
        {
          i--;
          printf("I codici esame devono essere di %d caratteri alfanumerici!\n... ",
                 (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));
        }

        /* se il codice esame contiene caratteri non alfanumerici */
        if (codice_esame[i] < '0' || 
            (codice_esame[i] > '9' && codice_esame[i] < 'A') || 
            (codice_esame[i] > 'Z' && codice_esame[i] < 'a') || 
            codice_esame[i] > 'z')
        {
          controllo_errori = 1;
        }
      }
      codice_esame[i] = '\0';
    }
    while ((strlen(codice_esame) != (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)) || (controllo_errori == 1));

    carattere_acquisito = getchar();   

    /* se l'utente ha inserito un codice esame troppo lungo */
    if (carattere_acquisito != '\n')
    {
      printf("Il codice esame è stato abbreviato a %d caratteri!\n",
             (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));  
     
      /* ripulisci il file stdin */
      while (carattere_acquisito != '\n')
        carattere_acquisito = getchar();
    }
    
    /* acquisizione da stdin del nome esame da inserire */
    
    /* il ciclo do/while continua se l'utente non inserisce nessun nome */
    do
    {
      printf("Inserire il nome dell'esame da inserire: ");

      carattere_acquisito = '~';
    
      for (i = 0; 
           ((i < (LUNGHEZZA_STRINGA_NOME_ESAME - 1)) && (carattere_acquisito != '\n') && (carattere_acquisito != ' '));
           i++)
      {
        carattere_acquisito = getchar();
        if ((carattere_acquisito != '\n') && (carattere_acquisito != ' ')) 
          nome_esame[i] = carattere_acquisito;
        else
          i--;
       }
       nome_esame[i] = '\0';
     
       /* se l'utente ha inserito un nome esame troppo lungo */
       if (carattere_acquisito != '\n')
       {
         printf("Il nome esame è stato abbreviato a %d caratteri!\n",
                (LUNGHEZZA_STRINGA_NOME_ESAME - 1));

         /* ripulisci il file stdin */
         while (carattere_acquisito != '\n')
           carattere_acquisito = getchar();
       }
    } 
    while (strlen(nome_esame) == 0);
     
    /* acquisizione da stdin del voto dell'esame da inserire */
    printf("Inserire il voto per l'esame \"%s\" : \"%s\" : ", 
           codice_esame, nome_esame);
    do
    {
      esito = scanf("%d", &voto_esame);
      /* se il voto non è corretto */
      if (esito != 1 || voto_esame < 18 || voto_esame > 30)
      {
        printf("Voto non valido!\n... ");

        /* pulizia del file stdin */
        while((getchar()) != '\n'); 
         
      }
    }
    while (esito != 1 || voto_esame < 18 || voto_esame > 30);

    /* inserimento dell'esame nell'albero */
    inserito = inserisci_esame_in_albero_bin_esami(&studente_p->radice_p, 
                                                     codice_esame, 
                                                     nome_esame, 
                                                     voto_esame);

    /* se l'inserimento è andato a buon fine */
    if (inserito == 1)
    {
      printf("Esame \"%s\" : \"%s\" inserito con voto %d!\n", 
             codice_esame, nome_esame, voto_esame);

      /* incrementa il numero di esami sostenuti dallo studente */
      studente_p->esami_sostenuti++; 
    }
    else
      printf("Esame \"%s\" già presente!\n", codice_esame);

  } 

  /* viene restituito l'esito dell'inserimento */
  return(inserito); 
}

/* Funzione per la rimozione di un esame */

int rimuovi_esame(nodo_albero_bin_studenti_t *radice_p) /* lavoro: puntatore alla radice dell'albero */
{
  nodo_albero_bin_studenti_t *studente_p; /* lavoro: puntatore al nodo dello studente che ha sostenuto l'esame da rimuovere  */

  char codice_esame[LUNGHEZZA_STRINGA_CODICE_ESAME], /* input: codice dell'esame da rimuovere                */
       carattere_acquisito = '~';                    /* lavoro: variabile usata per acquisizioni e controlli */

  int  rimosso = 0,      /* output: esito rimozione           */
       controllo_errori, /* lavoro: controllo su codice esame */
       i;                /* lavoro: indice per i cicli        */
  
  /* viene selezionato lo studente */
  studente_p = seleziona_studente(radice_p); 

  /* se lo studente viene trovato */
  if (studente_p != NULL)
  {
    while (carattere_acquisito != '\n')
      carattere_acquisito = getchar();
 
    /* acquisizione da stdin del codice dell'esame da rimuovere */ 
    printf("Inserire il codice dell'esame da rimuovere: ");
    
    /* il ciclo do/while si ripete se il codice inserito da tastiera è troppo corto oppure il codice contiene caratteri non alfanumerici */ 
    do
    {
      controllo_errori = 0;
      carattere_acquisito = '~';

      for (i = 0;
           ((i < (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)) && (carattere_acquisito != '\n') && (carattere_acquisito != ' '));
           i++)
      {
        carattere_acquisito = getchar();
        if ((carattere_acquisito != '\n') && (carattere_acquisito != ' '))
          codice_esame[i] = carattere_acquisito;
        else
        {
          i--;
          printf("I codici esame devono essere di %d caratteri alfanumerici!\n... ",
                 (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));
        }

        /* se il codice esame contiene caratteri non alfanumerici */
        if (codice_esame[i] < '0' || 
            (codice_esame[i] > '9' && codice_esame[i] < 'A') || 
            (codice_esame[i] > 'Z' && codice_esame[i] < 'a') || 
            codice_esame[i] > 'z')
        {
          controllo_errori = 1;
        }
      }
      codice_esame[i] = '\0';
    }
    while ((strlen(codice_esame) != (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)) || (controllo_errori == 1));

    carattere_acquisito = getchar();   

    /* se l'utente ha inserito un codice esame troppo lungo */
    if (carattere_acquisito != '\n')
    {
      printf("Il codice esame è stato abbreviato a %d caratteri!\n",
             (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));  
     
      /* ripulisci il file stdin */
      while (carattere_acquisito != '\n')
        carattere_acquisito = getchar();
    } 

    /* rimozione dell'esame dall'albero */
    rimosso = rimuovi_esame_da_albero_bin_esami(&studente_p->radice_p, 
                                                codice_esame);
    
    /* se la rimozione è andata a buon fine */
    if (rimosso == 1)
    {
      printf("Esame \"%s\" rimosso!\n", codice_esame);

      /* decrementa il numero di esami sostenuti dallo studente */
      studente_p->esami_sostenuti--; 
    }
    else
     printf("Impossibile rimuovere l'esame \"%s\", non è in memoria!\n", 
            codice_esame);  
  }

  /* viene restituito l'esito della rimozione */
  return(rimosso); 
}

/* Funzione per il calcolo della media dello studente */

void calcola_media_studente(nodo_albero_bin_studenti_t *radice_p) /* lavoro: puntatore alla radice dell'albero studenti */
{
  int sommatoria_voti = 0; /* lavoro: sommatoria dei voti dello studente */

  double media = 0.0; /* output: media dello studente */

  nodo_albero_bin_studenti_t *studente_p = NULL; /* puntatore al nodo che contiene lo studente selezionato */

  /* viene selezionato lo studente */
  studente_p = seleziona_studente(radice_p);

  /* se lo studente è stato trovato ma non ha sostenuto esami */
  if (studente_p != NULL && studente_p->esami_sostenuti == 0)
      printf("Lo studente %d non ha sostenuto esami!\n", 
             studente_p->numero_matricola); 
  
  /* altrimenti, se lo studente è stato trovato e ha sostenuto almeno un esame */
  else if (studente_p != NULL && studente_p->esami_sostenuti != 0)
  {
    /* invoca la visita per eseguire la sommatoria dei voti dello studente */
    visita_per_sommatoria_voti_studente_albero_bin_esami_simm(studente_p->radice_p, 
                                                              &sommatoria_voti);

    /* calcola e stampa la media dello studente */
    media = (double)sommatoria_voti / studente_p->esami_sostenuti;
    printf("La media dello studente numero %d è %.2f!\n", 
           studente_p->numero_matricola, media);
  }
}

/* Funzione per il calcolo della media del corso di laurea */

void calcola_media_corso(nodo_albero_bin_studenti_t *radice_p, /* lavoro: puntatore alla radice dell'albero                     */
                         int totale_esami)                     /* input: numero totale di esami sostenuti da tutti gli studenti */
{
  int sommatoria_voti = 0; /* lavoro: sommatoria dei voti */                 
  double media = 0.0;      /* output: valore della media  */

  /* se nessuno studente ha sostenuto esami */
  if (totale_esami == 0)
   printf("\nNessuno studente ha sostenuto esami!\n");

  else
  {

    /* invoca la visita dell'albero per calcolare la sommatoria dei voti del corso di laurea */
    visita_per_sommatoria_voti_albero_bin_studenti_simm(radice_p, 
                                                        &sommatoria_voti);
    /* calcola e stampa la media */
    media = (double)sommatoria_voti / totale_esami;
    printf("\nLa media del corso di laurea è %.2f!\n", media);

  }  
}

/* Funzione per il calcolo della mediana del corso di laurea */

void calcola_mediana_corso(nodo_albero_bin_studenti_t *radice_p, /* lavoro: puntatore alla radice dell'albero studenti      */ 
                           int totale_esami)                     /* input: numero di esami sostenuti da tutti gli studenti  */
{
  int *voti, /* lavoro: puntatore al primo elemento dell'array dei voti */
      i = 0; /* lavoro: indice di posizione                             */

  double mediana = 0.0; /* output: valore della mediana */

  /* se nessuno studente ha sostenuto esami */
  if (totale_esami == 0)
    printf("\nNessuno studente ha sostenuto esami!\n");

  else
  {

    /* viene allocato l'array dei voti */
    voti = (int*)calloc(totale_esami, sizeof(int));

    /* viene invocata la visita per la raccolta dei voti degli studenti */
    visita_per_raccolta_voti_albero_bin_studenti_simm(radice_p, 
                                                      voti, 
                                                      &i);

    /* viene ordinato l'array dei voti */
    quicksort(voti, 0, (totale_esami - 1));

    /* calcolo della mediana del corso di laurea */
    if (totale_esami % 2 != 0)
      mediana = voti[(totale_esami - 1) / 2];
    else
      mediana = (((voti[(totale_esami/2 - 1)]) + (voti[totale_esami/2])) / 2);

    /* stampa della mediana */
    printf("\nLa mediana del corso di laurea è %.2f!\n", mediana);
    
    /* l'array dei voti viene rimosso dalla memoria */
    free(voti);
  }
}


/* Menù del programma */

void menu(int numero_studenti,                   /* input: numero di studenti frequentanti il corso                            */ 
          int argc,                              /* lavoro: numero di stringhe del comando con cui viene lanciato il programma */
          int totale_esami,                      /* input: numero totale di esami sostenuti dagli studenti                     */
          char *argv[],                          /* lavoro: stringhe contenute nel comando con cui viene lanciato il programma */
          nodo_albero_bin_studenti_t *radice_p)  /* lavoro: puntatore alla radice dell'albero binario                          */
{
  int esito,  /* lavoro: esito scanf        */
      scelta; /* input: scelta dell'utente  */
 
  do
  {
    printf("\nScegliere una delle seguenti opzioni:\n"
           "1) Modifica il voto di un esame di uno studente\n"
           "2) Inserisci un nuovo esame per uno studente\n"
           "3) Rimuovi un esame per uno studente\n"
           "4) Calcola media per uno studente\n"
           "5) Calcola media del corso di laurea\n"
           "6) Calcola mediana del corso di laurea\n"
           "7) Salva le modifiche sul file di output\n"
           "8) Chiudi il programma\n... ");

    /* acquisizione da stdin della scelta dell'utente */
    do
    {
      esito = scanf("%d", &scelta);

      /* se il valore non è corretto */
      if (esito != 1 || scelta < 1 || scelta > 8)
      {
        printf("Scelta non valida!\n... ");

        /* pulizia del file stdin */
        while((getchar()) != '\n'); 

      }
    }
    while (esito != 1 || scelta < 1 || scelta > 8);
    
    /* implementazione del menu */
    switch(scelta) 
    {
      case 1:
        modifica_voto(radice_p);
        break;
      case 2:
        esito = inserisci_esame(radice_p);

        /* se l'inserimento è andato a buon fine */ 
        if (esito == 1)

          /* incrementa il numero totale degli esami */
          totale_esami++; 

        break;
      case 3:
        esito = rimuovi_esame(radice_p);
        
        /* se la rimozione è andata a buon fine */
        if (esito == 1)

          /* decrementa il numero totale degli esami */
          totale_esami--; 

        break;
      case 4:
        calcola_media_studente(radice_p);
        break;
      case 5:
        calcola_media_corso(radice_p, 
                            totale_esami);
        break;
      case 6:
        calcola_mediana_corso(radice_p, 
                              totale_esami);
        break; 
      case 7: 
        stampa_su_file(numero_studenti, 
                       argc, 
                       argv, 
                       radice_p);
        break;
    } 
  } 
  while (scelta != 8);  
}

/* Funzione MAIN */

int main (int argc,     /* lavoro: numero di stringhe acquisite dal comando di lancio   */ 
          char *argv[]) /* lavoro: array delle stringhe acquisite dal comando di lancio */
{
  FILE *input; /* lavoro: puntatore al file d'input */

  char codice_esame[LUNGHEZZA_STRINGA_CODICE_ESAME], /* input: codice dell'esame acquisito                        */
       nome_esame[LUNGHEZZA_STRINGA_NOME_ESAME],     /* input: nome dell'esame acquisito                          */
       carattere_acquisito = '~';                    /* lavoro: variabile utilizzata per acquisizioni e controlli */

  int numero_studenti,                  /* input: numero di studenti frequentanti il corso                            */
      numero_matricola,                 /* input: numero di matricola dello studente acquisito                        */
      esami_sostenuti,                  /* input: numero di esami sostenuti dallo studente acquisito                  */
      totale_esami = 0,                 /* input: numero totale di esami sostenuti da tutti gli studenti              */       
      voto_esame,                       /* input: voto dell'esame dello studente acquisito                            */
      esito,                            /* lavoro: variabile di controllo                                             */
      inserimenti_studente_falliti = 0, /* lavoro: numero di studenti non inseriti nella struttura dati               */
      inserimenti_esame_falliti = 0,    /* lavoro: numero di esami non inseriti per lo studente che si sta elaborando */
      controllo_errori = 0,             /* lavoro: quando assume valore 1 forza la chiusura del programma             */
      i, j, k;                          /* lavoro: indici per i cicli                                                 */
  
  nodo_albero_bin_studenti_t *radice_p = NULL; /* lavoro: puntatore alla radice dell'albero studenti              */
  nodo_albero_bin_esami_t *radice_esami_p;     /* lavoro: puntatore alla radice dell'albero esami di uno studente */
            
  /* se è stato specificato un file di input */
  if (argc >= 2)
  {
    /* apri il file */
    input = fopen(argv[1], "r");
  
    /* se il file specificato esiste */ 
    if (input != NULL)

    {
      printf("\nIl file \"%s\" è stato caricato in memoria!\n", argv[1]);

      /* acquisisci il numero di studenti frequentanti il corso */
      esito = fscanf(input, "%d", &numero_studenti);

      /* se il numero di studenti non è valido */
      if (esito != 1 || numero_studenti < 0)
      {
        printf("Lettura del numero di studenti non riuscita, "
               "la prima riga non contiene un numero naturale!\n");

        /* forza la chiusura del programma */
        controllo_errori = 1;
      }
      else
    
      /* il ciclo acquisce gli studenti uno ad uno e li inserisce nella struttura dati */
      for (i = 0; (i < numero_studenti); i++)
      {
        /* inizializzazione della radice all'albero esami dello studente */
        radice_esami_p = NULL;

        /* inizializzazione del numero di inserimenti di esame falliti   */
        inserimenti_esame_falliti = 0;

        /* acquisizione del numero di matricola dello studente */
        esito = fscanf(input, "%d", &numero_matricola);

        /* se il numero di matricola non è un intero */
        if (esito != 1)
        {
          printf("Lettura del %d° studente non riuscita!\n", (i + 1));
        
          /* forza la chiusura del programma */
          controllo_errori = 1; 
        }
      
        /* altrimenti, se il numero di matricola non è un numero naturale */
        else if (numero_matricola < 0)
        {
          printf("Il numero di matricola del %d° studente non è >= 0!\n", (i + 1));

          /* forza la chiusura del programma */
          controllo_errori = 1;
        }
        else
        {
          /* acquisizione del numero di esami sostenuti dallo studente */
          esito = fscanf(input, "%d", &esami_sostenuti); 

          /* se il valore acquisito non è un numero naturale */
          if (esito != 1 || esami_sostenuti < 0)
          {
            printf("Lettura del numero di esami sostenuti dallo studente con ID: %d non riuscita!\n",
                   numero_matricola);

            /* forza la chiusura del programma */
            controllo_errori = 1;
          }
          else
          {
 
            /* il ciclo acquisisce gli esami uno ad uno e li inserisce nella struttura dati */
            for (j = 0; (j < esami_sostenuti); j++)
            {
              /* spostati in avanti nel file fino ad arrivare all'inizio del codice esame */
              while (carattere_acquisito != '\n')
                carattere_acquisito = getc(input);
                    
              /* acquisizione del codice esame */
              for (k = 0; 
                   ((k < (LUNGHEZZA_STRINGA_CODICE_ESAME - 1)));
                   k++)
              {
                codice_esame[k] = getc(input);

                /* se il codice esame ha meno caratteri del previsto */
                if (codice_esame[k] == ' ')
                {
                  printf("I codici esame devono contenere %d caratteri!\n", 
                         (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));

                  controllo_errori = 1;
                }

                /* se il codice esame contiene caratteri non alfanumerici */
                else if (codice_esame[k] < '0' || 
                         (codice_esame[k] > '9' && codice_esame[k] < 'A') || 
                         (codice_esame[k] > 'Z' && codice_esame[k] < 'a') || 
                         codice_esame[k] > 'z')
                {
                  printf("I codici esame possono contenere solo caratteri alfanumerici!\n");
             
                  /* forza la chiusura del programma */
                  controllo_errori = 1;
                }
              }
              codice_esame[k] = '\0';

              carattere_acquisito = getc(input);
               
              /* se il codice esame ha più caratteri del previsto */
              if (carattere_acquisito != ' ')
                printf("I codici esame che superano i %d caratteri sono stati abbreviati!\n",
                       (LUNGHEZZA_STRINGA_CODICE_ESAME - 1));
              
             
              /* spostati in avanti nel file fino ad arrivare all'inizio del nome esame */ 
              while (carattere_acquisito != ' ')
                carattere_acquisito = getc(input);

              /* acquisizione del nome esame */
              for (k = 0, carattere_acquisito = '~';
                   ((k < (LUNGHEZZA_STRINGA_NOME_ESAME - 1)) && (carattere_acquisito != ' ') && (carattere_acquisito != '\n'));
                   k++)
              {
                carattere_acquisito = getc(input);

                if ((carattere_acquisito != ' ') && (carattere_acquisito != '\n'))
                  nome_esame[k] = carattere_acquisito;

                else 
                  k--;
              }
              nome_esame[k] = '\0';
              
              /* se il nome esame ha più caratteri del previsto */
              if (carattere_acquisito != ' ')
                printf("I nomi esami che superano i %d caratteri sono stati abbreviati!\n",
                       (LUNGHEZZA_STRINGA_NOME_ESAME - 1));

              /* spostati in avanti nel file in avanti fino ad arrivare all'inizio del voto esame */
              while (carattere_acquisito != ' ')
                carattere_acquisito = getc(input);
              
              /* acquisizione del voto dell'esame */
              esito = fscanf(input, "%d", &voto_esame);

              /* se il voto non è valido */
              if (esito != 1 || voto_esame < 18 || voto_esame > 30)
              {
                printf("Lettura dei voti dello studente %d non riuscita!\n" 
                       "(i voti devono essere numeri naturali compresi tra 18 e 30!)\n", 
                       numero_matricola);  

                /* forza la chiusura del programma */
                controllo_errori = 1;
              } 
            
              /* inserimento dell'esame nell'albero esami */ 
              esito = inserisci_esame_in_albero_bin_esami(&radice_esami_p, 
                                                          codice_esame, 
                                                          nome_esame, 
                                                          voto_esame);
             
              /* se l'inserimento non è andato a buon fine */
              if (esito == 0)
              {
                printf("Esame \"%s\" non inserito per lo studente %d, è già presente!\n", 
                       codice_esame, numero_matricola);

                /* incrementa il numero di inserimenti di esame falliti per questo studente */
                inserimenti_esame_falliti++;
              }   
            }
              /* decrementa il numero di esami sostenuti dallo studente del valore degli inserimenti di esame falliti */
              esami_sostenuti = esami_sostenuti - inserimenti_esame_falliti; 

              /* inserisci lo studente nell'albero degli studenti */
              esito = inserisci_studente_in_albero_bin_studenti(&radice_p,
                                                                numero_matricola,
                                                                esami_sostenuti,
                                                                radice_esami_p);

              /* se l'inserimento non è andato a buon fine */
              if (esito == 0)
              {
                printf("Lo studente %d è già presente e non verrà reinserito!\n", 
                       numero_matricola);
             
                /* incrementa il numero di inserimenti di studente falliti */
                inserimenti_studente_falliti++;
              }
  
              else
                /* incrementa il numero totale di esami del numero di esami sostenuti dallo studente */
                totale_esami = totale_esami + esami_sostenuti;
          }  
        }
      }

      /* chiudi il file di input */
      fclose(input);
    
      /* decrementa il numero degli studenti del numero di inserimenti di studente falliti */
      numero_studenti = numero_studenti - inserimenti_studente_falliti;

      /* se non si sono verificati errori */
      if (controllo_errori != 1)

        /* lancia il menu */
        menu(numero_studenti, 
             argc, 
             totale_esami, 
             argv, 
             radice_p);
    }

    /* se il file di input specificato dall'utente non esiste o non è valido */
    else printf("\nAttenzione: il file specificato come input non esiste o non è valido!\n");

  }

  /* se non è stato specificato un file di input durante il lancio del programma */
  else printf("\nAttenzione: non è stato specificato nessun file da leggere!\n\n"
              "Per favore rilanciare il programma con i parametri adeguati:\n"
              "%s <percorso file di input> <percorso file di output>\n"
              "(se il file è nella dir. di lavoro basta specificarne il nome)\n", 
              argv[0]);

  printf("\n");
  return(0);
}
