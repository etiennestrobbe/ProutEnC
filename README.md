Projet C - stdio
========


Questions :

1. _cnt est le compteur
   _ptr est le caractere courant dans le buffer
   _base est le premier caractere du buffer
   _bufsiz est la taille du buffer
   _flag est l'etat (ecriture, lecture, erreur ...) du buffer
   _file est le descripteur de fichier

2. _filbuf et _flsbuf ont ete realises

3.4. les fonctions ont ete testees à l'aide du fichier test.c qui utilise getc, putc,
   ainsi que fopen et fclose

5. test.c est une implémentation simple de cp
   cpSimple est l'executable y correspondant, on peu par exemple lancer la commande :
	"cpSimple foo result" 
   pour copier le fichier foo dans un nouveau fichier result2
