#ifndef T_TOKEN_H
# define T_TOKEN_H
# include <sys/types.h>

/*
**	Every type of token we can find accoring to the POSIX STANDARD should be
**	listed in the following enums. The first enum of each groups starts at the
**	last group's last element index + 1. As if they were all defined in one
**	enum.  This will be usefull when matching them with the strings/index pair
**	of a global variable.
*/

/*
**	Words and assignement words. According to this enum, operator will have an
**	id such that `5 <= id < 20', and reserved words will have an id such as `id
**	>= 20'.
*/

# define OPERATOR_OFFSET 5
# define RESERVED_WORDS_OFFSET 21
enum
{
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_NAME,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_LESS = OPERATOR_OFFSET,
	TK_HERE,
	TK_GREAT,
	TK_SEMI,
	TK_PIPE,
	TK_AND,
	TK_AND_IF,
	TK_OR_IF,
	TK_DSEMI,
	TK_DLESS,
	TK_DGREAT,
	TK_LESSAND,
	TK_GREATAND,
	TK_LESSGREAT,
	TK_DLESSDASH,
	TK_CLOBBER,
	TK_IF = RESERVED_WORDS_OFFSET,
	TK_THEN,
	TK_ELSE,
	TK_ELIF,
	TK_FI,
	TK_DO,
	TK_DONE,
	TK_CASE,
	TK_ESAC,
	TK_WHILE,
	TK_UNTIL,
	TK_FOR,
	TK_LBRACE,
	TK_RBRACE,
	TK_BANG,
	TK_LPAREN,
	TK_RPAREN,
	TK_IN,
	$ = 666
};

#define _T_STATE 0
#define _T_START 1
#define _T_END 2
#define _T_COUNT 3
#define _T_NEST 4

typedef struct	s_token
{
	ssize_t				*state_info;
	char				*value;
	char				delim;
	int					id;
}				t_token;
#endif


t_token		*create_token(const char *source, ssize_t *info);
void		free_token(void *value);
