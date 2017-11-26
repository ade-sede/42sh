/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:44 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "t_lexer.h"
# include "t_token.h"
# include <string.h>
# include "list.h"

struct			s_state_to_prompt
{
	int			id;
	char		*string;
};

/*
**	Convenient debug data structure.
*/

struct			s_debug_token_id
{
	int		id;
	char	*name;
};

struct			s_debug_token_state
{
	int		state;
	char	*name;
};

/*
**	Struct used to get action depending on state
*/

struct			s_lex_action
{
	ssize_t	state;
	int		(*func)(t_lexer *lex, struct s_info **state_info);
};

/*
**	Macro to check if a character is a potential operator.
*/

# ifndef IS_OPERATOR
#  define _L_IS_OP1(c) (c == '<' || c == '>' || c == ';')
#  define _L_IS_OP2(c) (c == '&' || c == '|')
#  define CHAR_IS_OPERATOR(c) (_L_IS_OP1(c) || _L_IS_OP2(c))
# endif
# ifndef IS_RESERVED_WORD
#  define IS_RESERVED_WORD(id) (id >= TK_IF && id <= TK_IN)
# endif

# define LEXER_SUCCESS 0
# define LEXER_REOPEN 1

/*
**	In get_token.c
*/

t_token			*get_token(t_lexer *lex);

/*
**	In get_token_list.c
*/

int				get_token_list(t_lexer *lex, t_list **token_list, \
		t_list *aliast_list);
t_list			*expand_alias(t_lexer *lex, t_token **token, \
		t_list *alias_list);

/*
**	In utils.c
*/

void			free_info(void *ptr);
struct s_info	*create_state_info(void);
void			copy_state_info(struct s_info *old_info, \
		struct s_info *new_info);
int				push_state(t_lexer *lex, int new_state);
int				consume_input(t_lexer *lex);
int				pop_state(t_lexer *lex, struct s_info **info);
int				change_state(t_lexer *lex, int	new_state);

/*
**	REFERENCING ACTIONS
*/

int				lex_action_default(t_lexer *lex, struct s_info **state_info);
int				lex_action_word(t_lexer *lex, struct s_info **state_info);
int				lex_action_whitespace(t_lexer *lex, struct s_info **state_info);
int				lex_action_dquotes(t_lexer *lex, struct s_info **state_info);
int				lex_action_quotes(t_lexer *lex, struct s_info **state_info);
int				lex_action_bs(t_lexer *lex, struct s_info **state_info);
int				lex_action_operator(t_lexer *lex, struct s_info **state_info);
int				lex_action_newline(t_lexer *lex, struct s_info **state_info);
int				lex_action_comment(t_lexer *lex, struct s_info **state_info);
int				lex_action_param_exp(t_lexer *lex, struct s_info **state_info);
int				lex_action_cmd_subst(t_lexer *lex, struct s_info **state_info);
int				lex_action_ar_exp(t_lexer *lex, struct s_info **state_info);

/*
**	REFERENCING IDS
*/

void			get_token_id(t_lexer *lex, t_token *token);
int				id_operator(const char *value);
int				id_reserved_words(const char *value);
int				id_word(t_lexer *lex, t_token *token);
char			*lexer_construct_prompt(t_lexer *lex);

int				check_valid_name(const char *value, size_t size);
t_token			*check_function_name(t_lexer *lex, const char *value);
int				check_assignement_word(t_lexer *lex, const char *value);
int				check_io_number(t_token *token);

#endif
