#include "libft.h"
#include "builtin.h"
#include "lexer.h"
#include <stdio.h>


t_list	*expand_alias(t_lexer *lex, t_token **token, t_list *alias_list)
{
	t_list	*alias_node;
	t_list	*alias_copy;
	t_list	*token_list;
	char	*alias_value;
	t_lexer new_lex;
	ssize_t	eq_index;
	int		ret;

	alias_copy = NULL;
	token_list = NULL;
	if ((*token)->cmd_name == FALSE)
		return (NULL);
	if (!alias_list)
		return (NULL);
	ft_simple_lst_dup(&alias_copy, alias_list);
	if ((alias_node = find_alias(alias_copy, (*token)->value, ft_strlen((*token)->value))) != NULL)
	{
		alias_value = alias_node->data;
		ft_simple_lst_del_one(&alias_copy, alias_node, NULL);
		eq_index = ft_strichr(alias_value, '=');
		init_lexer(&new_lex, alias_value + eq_index + 1);
		/* Give state to child // NOT NEEDED HERE */
		/* Lex in child */
		ret = get_token_list(&new_lex, &token_list, alias_copy);
		/* Give state to parent == remove state_list of parent and use the child's list */
		/* Substitute list of parent lexer with list of child_lexer */
		ft_simple_lst_remove(&lex->state_list, free_info);
		lex->state_list = new_lex.state_list;
		new_lex.state_list = NULL;
		lex->state = new_lex.state;
		/*	Cmd word_status transmition */
		lex->cmd_name_open = new_lex.cmd_name_open;

		/* Concatenate reversed_lists */
		ft_simple_lst_pushback(&new_lex.reversed_list, lex->reversed_list);
		lex->reversed_list = new_lex.reversed_list;
		new_lex.reversed_list = NULL;


		/* Delete child_lexer */
		free_lexer(&new_lex);
	}
	else
		return (NULL);
	ft_simple_lst_remove(&alias_copy, NULL);
	if (token_list || (!token_list && ret == LEXER_REOPEN))
	{
		free_token(*token);
		*token = NULL;
	}
	return (token_list);
}
