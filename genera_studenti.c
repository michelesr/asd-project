/* Programma per generare un database random di studenti */
/* Progetto Algoritmi Sessione Estiva 2011/2012          */
/* Michele Sorcinelli, Matricola n° 248412               */
/* comando di compilazione: make genera_studenti         */

/*********************************************************/

/* inclusione delle librerie */

#include <stdio.h>  /* Standard Input/Output Library */
#include <stdlib.h> /* C Standard Library            */
#include <string.h> /* Gestione delle stringhe       */

/* ATTENZIONE : Controllare che i valori di queste costanti coincidano con quelli del programma principale */

#define LUNGHEZZA_STRINGA_CODICE_ESAME 6 /* lunghezza della stringa del codice esame */
#define LUNGHEZZA_STRINGA_NOME_ESAME 51  /* lunghezza della stringa del nome esame   */
#define PERCORSO_FILE "./random"         /* percorso del file di output              */

/* Definizione della funzione MAIN */

int main(void)
{
  int numero_studenti, /* input: numero di studenti da generare  */
      numero_esami,    /* input: numero di esami per studente    */
      esito,           /* lavoro: variabile di controllo         */
      i,j,k;           /* lavoro: indice per i cicli             */

  char codice_esame[LUNGHEZZA_STRINGA_CODICE_ESAME], /* output: codice dell'esame generato */
       nome_esame[LUNGHEZZA_STRINGA_NOME_ESAME];     /* output: nome dell'esame generato   */
  FILE *output;

  /* acquisizione del numero di studenti da generare */
  printf("\nInserire il numero di studenti da generare: ");
  do
  {
    esito = scanf("%d", &numero_studenti);

    /* se il numero acquisito non è valido */
    if (esito != 1 || numero_studenti < 1)
    {
      printf("\nScelta non valida!\n ... ");

      /* pulisci il file stdin */
      while (getchar() != '\n');
    }
  }
  while (esito != 1 || numero_studenti < 1);

  /* acquisizione del numero di esami da generare per ogni studente */
  printf("Inserire il numero di esami da generare per ogni studente: ");
  do
  {
    esito = scanf("%d", &numero_esami);

    /* se il numero acquisito non è valido */
    if (esito != 1 || numero_esami < 0)
    {
      printf("\nScelta non valida!\n ... ");

      /* pulizia del file stdin */
      while (getchar() != '\n');
    }
  }
  while (esito != 1 || numero_esami < 0);
  
  /* apri il file di output */
  output = fopen(PERCORSO_FILE , "w");

  /* stampa il numero di studenti */
  fprintf(output, "%d\n", numero_studenti);

  /* il ciclo stampa gli studenti uno ad uno */
  for (i = 0; i < numero_studenti; i++)
  {
    /* stampa il numero di matricola */
    fprintf(output, "%d\n", rand());
    
    /* stampa il numero di esami sostenuti */
    fprintf(output, "%d\n", numero_esami);
 
    /* il ciclo stampa gli esami uno ad uno */
    for (j = 0; j < numero_esami; j++)
    {
      /* viene generato il codice_esame */
      for(k = 0; k < LUNGHEZZA_STRINGA_CODICE_ESAME - 1; k++)
      {
        if (k < (LUNGHEZZA_STRINGA_CODICE_ESAME / 2))
        codice_esame[k] = ((rand() % 26) + 'A');

        else
        codice_esame[k] = ((rand() % 10) + '0');
      }
      codice_esame[k] = '\0';
      
      /* viene stampato il codice esame */
      fprintf(output, "%s ", codice_esame);

      /* viene generato il nome esame */
      nome_esame[0] = ((rand() % 26) + 'A'); 
      for (k = 1; 
           k < (LUNGHEZZA_STRINGA_NOME_ESAME - (LUNGHEZZA_STRINGA_NOME_ESAME / 2)); 
           k++)
        nome_esame[k] = ((rand() % 26) + 'a');
      nome_esame[k] = '\0';

      /* viene stampato il nome esame */
      fprintf(output, "%s ", nome_esame);

      /* viene generato e stampato il voto esame */
      fprintf(output, "%d\n", ((rand() % 12) + 18)); 
    }
    fprintf(output, "\n");
  } 

  /* viene chiuso il file */
  fclose(output);

  printf("Il database casuale di studenti è stato salvato in \"%s\"!\n\n", PERCORSO_FILE); 

  return(0);   
}
