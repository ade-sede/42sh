#include "libft.h"
#include "builtin.h"
#include "lexer.h"


t_list	*expand_alias(t_lexer *lex, t_token *token, t_list *alias_list)
{
	t_list	*alias_node;
	t_list	*alias_copy;
	t_list	*token_list;
	t_list	*child_state_list;
	char	*alias_value;
	t_lexer new_lex;
	ssize_t	eq_index;
	int		ret;

	alias_copy = NULL;
	token_list = NULL;
	if (!alias_list)
		return (NULL);
	ft_simple_lst_dup(&alias_copy, alias_list);
	if ((alias_node = find_alias(alias_copy, token->value, ft_strlen(token->value))) != NULL)
	{
		alias_value = alias_node->data;
		dprintf(2, "%p\n", alias_value);//			REMOVE		
		ft_simple_lst_del_one(&alias_copy, alias_node, NULL);
		eq_index = ft_strichr(alias_value, '=');
		init_lexer(lex, alias_value + eq_index + 1);
		/* Give state to child // NOT NEEDED HERE */
		/* Lex in child */
		ret = get_token_list(&new_lex, &token_list, alias_copy);
		/* Give state to parent == remove state_list of parent and use the child's list */
		ft_simple_lst_remove(&lex->state_list, free_info);
		lex->state_list = new_lex.state_list;
		new_lex.state_list = NULL;
		free_lexer(&new_lex);
	}
	ft_simple_lst_remove(&alias_copy, NULL);
	if (token_list)
		free_token(token);
	return (token_list);
}
