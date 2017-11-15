#ifndef SYNTAX_COLORING
# define SYNTAX_COLORING
#include "lexer.h"
#include "line_editing.h"

/*
**	Plan 1;
**	The idea is to reuse the lexer, and write input to stderr when consuming it.
**
**	Plan 2:
**		Everytime we push or pop, we have finished a mini-token, and we can print its value.
**
**		Plan 2	vs Plan 1
**		Plan 1 is very easy
**		Plan 2 can handle falsy program names ( and everything that requires the analysis of the full token), plan 1 cant (because it requires
**		analysis of the full token, but plan 1 is writting on the fly ( no
**		buffering))
**
**	Variant of Plan 1 in the case of a command name :
**	If string is a command name, from the moment characters dont match a binary builtin or alias, we can print in red when it stops matching.
**
**	Stick with plan 1 for the moment.
*/

struct	s_lex_action_le
{
	ssize_t	state;
	int		(*func)(t_lexer *, ssize_t **, t_line *);
};

int		loop_le_delim(t_lexer *lex, t_line *line);
int		delim(t_lexer *lex, t_line *line);
void	write_term(t_line *line, size_t i);
ssize_t	*create_state_info_le(void);
void	copy_state_info_le(ssize_t *old_info, ssize_t *new_info);
int		push_state_le(t_lexer *lex, ssize_t new_state);
int		consume_input_le(t_lexer *lex, t_line *line);
int		pop_state_le(t_lexer *lex, ssize_t	**info);
int		change_state_le(t_lexer *lex, ssize_t new_state);

int		lex_action_bs_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_cmd_subst_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_comment_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_default_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_dquotes_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_newline_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_operator_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_param_exp_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_quotes_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_whitespace_le(t_lexer *lex, ssize_t **state_info, t_line *line);
int		lex_action_word_le(t_lexer *lex, ssize_t **state_info, t_line *line);
#endif
