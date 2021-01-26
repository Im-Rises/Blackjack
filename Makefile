all:
		gcc main.c -o main joueur.c joueur.h

wall:
		gcc -wall seance7.c -o main joueur.c joueur.h
