#include "parser.h"
#include "color.h"
#include <stdio.h>
#include "exec.h"

void			init_parser(t_parser *parser)
{
	ft_bzero(parser, sizeof(parser));
	parser->state = 0;
	parser->ast_stack = NULL;
	parser->state_stack = new_state_lst(0);
}
