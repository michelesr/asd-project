# Progetto Algoritmi e Strutture Dati
# Sessione Estiva 2011/2012 
# Michele Sorcinelli, Matricola n° 248412

# Makefile

# Compilazione del progetto

progetto: progetto.c Makefile
	gcc progetto.c -ansi -Wall -O2 -o progetto

# Compilazione con simboli di debug 

debug: progetto.c Makefile
	gcc progetto.c -ansi -Wall -g -o progetto

# Compilazione del generatore pseudo-casuale di studenti

genera_studenti: genera_studenti.c Makefile
	gcc genera_studenti.c -ansi -Wall -O2 -o genera_studenti

	 
