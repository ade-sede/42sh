#include "libft.h"
#include <stdio.h>
#include <ncurses.h>
void	printer(void *data)
{
    printw((char *)data);  // Écrit Hello World à l'endroit où le curseur logique est positionné
    refresh();              // Rafraîchit la fenêtre courante afin de voir le message apparaître
}


int main(void)
{
	t_btree	*root;
	int   random_path;
	 
	srand(time(NULL));

	random_path = rand();
	printf("%d\n", random_path);
	random_path = rand();
	printf("%d\n", random_path);
	random_path = rand();
	printf("%d\n", random_path);
	random_path = rand();
	printf("%d\n", random_path);
	random_path = rand();
	printf("%d\n", random_path);
	random_path = rand();
	printf("%d\n", random_path);
	random_path = rand();
	printf("%d\n", random_path);
	root = btree_random(10);

	    initscr();              // Initialise la structure WINDOW et autres paramètres 
		root = btree_random(7);
		btree_print(root, printer);
	    getch();                // On attend que l'utilisateur appui sur une touche pour quitter
	    endwin();               // Restaure les paramètres par défaut du terminal

	return (0);
}
