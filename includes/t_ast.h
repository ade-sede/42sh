#ifndef T_AST_H
# define T_AST_H
# include "t_token.h"
typedef struct			s_ast
{
	struct s_ast	*child[7];
	int				symbol;
	t_token			*token;
}						t_ast;

t_ast	*new_ast(t_token *token, int symbol);
void	free_ast(t_ast *ast);
#endif
