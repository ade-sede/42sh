#ifndef EXEC_SYMBOL_H
# define EXEC_SYMBOL_H

# include "t_ast.h"
# include "parser_slr.h"

typedef struct	s_exec_func
{
	enum e_symbol	symbol;
	int				(*f)(t_ast*);
}				t_exec_func;

int	exec_program(t_ast *ast);
int	exec_complete_commands(t_ast *ast);
int	exec_complete_command(t_ast *ast);
int	exec_list(t_ast *ast);
int	exec_and_or(t_ast *ast);
int	exec_pipeline(t_ast *ast);
int	exec_pipe_sequence(t_ast *ast);
int	exec_command(t_ast *ast);
int	exec_compound_command(t_ast *ast);
int	exec_subshell(t_ast *ast);
int	exec_compound_list(t_ast *ast);
int	exec_term(t_ast *ast);
int	exec_for_clause(t_ast *ast);
int	exec_case_clause(t_ast *ast);
int	exec_if_clause(t_ast *ast);
int	exec_else_part(t_ast *ast);
int	exec_while_clause(t_ast *ast);
int	exec_until_clause(t_ast *ast);
int	exec_function_definition(t_ast *ast);
int	exec_function_body(t_ast *ast);
int	exec_do_group(t_ast *ast);
int	exec_simple_command(t_ast *ast);
void	debug_symbol(t_ast *ast);

struct	s_sym_to_string
{
	enum e_symbol	symbol;
	char			*string;
};
#endif
