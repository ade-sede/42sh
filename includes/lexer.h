#ifndef LEXER_H
# define LEXER_H
# include "t_lexer.h"
# include "t_token.h"
# include "env.h"

/*
**	We define macros to easily check wich type the character belongs to.
*/

# ifndef IS_QUOTED
#  define IS_QUOTED(state)	(state == 39 || state == 34)
# endif
# ifndef IS_OPERATOR
#  define __L_IS_OP1(c) (c == '<' || c == '>' || c == ';')
#  define __L_IS_OP2(c) (c == '&' || c == '|')
#  define IS_OPERATOR(c) (__L_IS_OP1(c) || __L_IS_OP2(c))
# endif
# ifndef IS_EXPAND
#  define IS_EXPAND(c) (c == '$' || c == '`')
# endif
# ifndef IS_INPUT_END
#  define IS_INPUT_END(c) (c == 0)
# endif
#define LEXER_SUCCESS 0
#define LEXER_DQUOTE DQUOTED
#define LEXER_QUOTE QUOTED

/*
**	Token delimitation is done according to the POSIX STANDARD found here:
**	http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
*/

/*
**	In file srcs/lexer/expand_alias.c
*/

int				lexer_insert_str_dest(char *dest, char *str, size_t dest_len);
int				lexer_insert_str(t_lexer *lex, char *dest, char *str);
void			lexer_delete_word(char *to_replace);
int				check_alias(t_lexer *lex, t_token *token);

/*
**	In file srcs/lexer/expand_param.c
*/

void			parameter_expansion(t_env *env, t_token *token);

/*
**	In file srcs/lexer/expand_tild.c
*/

void			tild_expand(t_env *env, t_token *token);

/*
**	In file srcs/lexer/expand_word.c
*/

t_list			*exec_expand(t_token *token);

/*
**	In file srcs/lexer/lexer.c
*/

int				lex_all(t_lexer *lex, t_list **token_list);
t_token			*start_lex(t_lexer *lex, int *reopen);
t_token			*handle_lexer(t_lexer *lex);
int				update_state(t_lexer *lex);
int				start_token(t_lexer *lex, size_t *token_start);
t_token			*tokenize(t_lexer *lex, size_t token_start, size_t token_end);
t_token_id		lex_get_token_id(t_lexer *lex, t_token *token);

/*
**	In file srcs/lexer/match_expand.c
*/

int				match_expand(t_lexer *lex, size_t token_start);

/*
**	In file srcs/lexer/match_operator.c
*/

int				match_operator(const char *value, size_t token_start, \
		size_t token_end);
t_token_id		lex_id_operator(const char *value);

/*
**	In file srcs/lexer/match_token.c
*/

void			append_history(char *command);
int				token_match(t_lexer *lex, size_t token_start);

/*
**	In file srcs/lexer/match_word.c
*/

int				match_word(t_lexer *lex);
int				lex_id_io_number(t_token *token, char delimiter, \
		t_token_id *id);
int				lex_id_reserved_words(t_token *token, t_token_id *id);
int				lex_id_word(t_lexer *lex, t_token *token, t_token_id *id);
#endif
