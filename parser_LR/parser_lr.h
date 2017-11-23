#ifndef PARSER_LR_H
# define PARSER_LR_H

#define NB_SYMBOLS 3
#define NB_TOKEN 4
#define FIRST_SYMBOL 4
#define FIRST_TOKEN 1

#define NB_RULES 4

#define IS_TOKEN(i) i >= FIRST_TOKEN && i <= c

#define IS_SYMBOL(i) i >= FIRST_SYMBOL && i <= F

enum e_symbol {
	start_symbol = FIRST_SYMBOL,
	s,
	c,
};

enum e_token {
	DOLLAR = FIRST_TOKEN,
	E,
	F,
	EPSILON,
};

/*
**	a morpheme is a token or a symbol
*/

typedef t_morpheme int 

struct s_morpheme_lst {
	struct s_morphene_lst	*next;
	t_morpheme				m;
};

struct s_static_grammar_rule {
	t_morpheme		node;
	t_morpheme		childs[7];
};

struct s_grammar_rule {
	t_morpheme				node;
	struct morpheme_lst		*child;
};


/*
**	an item is a [S->ß.Eµ, a]
**	whit a gramar rule, a point and a look ahead symbol
*/

struct s_item {
	struct item			*next_item;
	struct s_grammar_rule	*rule;
	int					point;
	enum e_token		look_ahead;
};

struct s_parser_lr {
	struct s_grammar_rule	grammar_rules[NB_RULES];
	struct s_token_lst		*firsts[NB_SYMBOLS + 1];
};

/*
** in firsts, the indice match the symbol
*/

#endif
