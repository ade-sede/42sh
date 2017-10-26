#ifndef T_AST_H
# define T_AST_H

typedef struct			s_ast
{
	struct s_ast	*child[7];
	int				symbol;
	t_token			*token;
}						t_ast;

#endif
