#include "parser_lr.h"
#include <stdio.h>

void	generate_automaton(struct s_parser_lr *lr, struct s_line *l)
{
    int i = 0;
	printf("\n---------automaton----------\n");
	printf("\n");
	printf("int	g_lr_table[][86] = {\n");
	while (l)
	{
		i = 0;
		printf("{");
		while (i < NB_TOKEN)
		{
			if (l->action_table[i] == acc)
				printf("acc, ");
			else if (l->action_table[i] >= 4242)
				printf("r%d, ", l->action_table[i] - 4242);
			else if (l->action_table[i] == -1)
				printf("%d, ", -1);
			else 
				printf("s%d, ", l->action_table[i]);
			i++;
		}
		while (i < NB_SYMBOLS)
		{
			printf("%d, ", l->goto_table[i]);
			i++;
		}
		printf("},");
		printf("\n");
		l = l->next;
	}
}
