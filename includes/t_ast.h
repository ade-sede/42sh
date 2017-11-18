#ifndef T_AST_H
# define T_AST_H
# include "t_token.h"
typedef struct			s_ast
{
	struct s_ast	*child[7];
	int				symbol;
	t_token			*token;
	char			*heredoc;
}						t_ast;

t_ast	*new_ast(t_token *token, int symbol);
void	free_ast(t_ast *ast);
void	free_ast_and_token(t_ast *ast);
t_ast	*dup_ast(t_ast *ast);
#endif
