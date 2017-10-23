/*
**	State est un pointer vers tableau d'int. Chaque case de ce tableau contient
**	un int representant un etat du parser. L'operation push_state(new_state)
**	correspond a ++state=new_state. L'operation pop_state correspond a :
**	state--=EMPTY_STATE
**
**	Token_list point vers une liste de token (passe par address de parser en
**	parser de maniere a ce que si un fils consomme un token, le parent reprenne
**	au bon token).
*/

#define EMPTY_STATE 0
#define STACK_SIZE 100;

struct s_parser
{
	int		*stack_top; // Pointeur vers l'etat courrant dans la stack d'etat ; state est un pointeur vers une des addresses de state_stack
	int		stack_start[STACK_SIZE]; // Stack d'etat
	t_list	**token_list; // Un pointer vers une liste de token.
}



int		parser_init(t_parser *parser, t_list **token)
{
	ft_memset(parser->state_stack, STACK_SIZE, EMPTY_STATE);
	parser->state = parser->state_stack;
	parser->token_list = token_list;
}

main_loop()
{
	t_parser parser;
	t_list	*token_list;
	t_ast	*ast;
	token_list = lex_all;
	parser_init(&parser, &token_list);
	ast = parse(parser);
}

/*
**	New_sym is the symbol that the current node would achieve if it was added
*/

/*
**	La fonction add token to tree ajoute le token a l'arbre courrant, ou bien
**	relance la creation d'un arbre qui sera un enfant de l'arbre courrant en
**	appelant parse avec un nouveau symbol. (partie recursive)
*/
 
/*
**	La fonction get_symbol retourne le symbol qui correspond a l'arbre UNE FOIS
**	LE TOKEN AJOUTE. Pour effectuer cet tache, on a besoin des symboles
**	rencontre depuis le debut du parsing actuel + l'etat transmit par le
**	parsing precedent.
*/

t_ast	*parser(t_parser *parser)
{
	t_ast	ast;
	int		new_sym;
	t_token token;

	while (1)
	{
		token = parser->(*token_list)->data;
		push_stack(parser, symbol_of_token(token));
		symbol_of_token(token);
		new_sym = get_symbol(parser->state_stack, parser->state);
		if (new_sym == ERROR)
			break ;
		add_token_to_tree(ast, token, new_sym);
		if (closing_symbol(new_sym, parser->state_stack[0]))
			return (ast);
	}
	return (ast);
}

add_token_to_tree(current_sym, new_sym)
{
}

closing_symbol(new_sym, start_sym)
{
}

g_symbol_list = 
{
}

get_symbol()
{
}
