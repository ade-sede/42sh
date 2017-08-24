#include <stdio.h>
#include "env.h"
#include "completion.h"

void	comple_bin_matches_extract_tree(t_ternary_tree *node, char **matches, int *i)
{
	if (!node)
		return ;
	/*
**		printf("c is %c\n", node->c);
**		if (node->match)
**			printf("match is %s\n", node->match);
**		if (node->left)
**			printf("\n left \n");
*/
	if (node->match)
	{
		matches[*i] = ft_strdup(node->match);
	//	printf("match is %s\n", matches[*i]);
		*i = *i + 1;
	}
	comple_bin_matches_extract_tree(node->left, matches, i);
	/*
**		if (node->down)
**			printf("\n down \n");
*/
	comple_bin_matches_extract_tree(node->down, matches, i);
	//put_termcap("do");
	/*
**		if (node->right)
**			printf("\n right\n");
*/
	comple_bin_matches_extract_tree(node->right, matches, i);
}

void	comple_bin_matches_tripping_tree(t_ternary_tree *node, char **matches, char *cur)
{
	int	i = 0;
	//printf("c is %c\n", node->c);
	if (!cur[0]) 
		return comple_bin_matches_extract_tree(node, matches, &i);
	if (*cur < node->c && (!node->left || (node->left && *cur > node->left->c)))// aret
		return ;
	else if (*cur > node->c && (!node->right || (node->right && *cur < node->right->c))) // aret
		return ;
	else if (*cur < node->c)
		return comple_bin_matches_tripping_tree(node->left, matches, cur);
	else if (*cur > node->c)
		return comple_bin_matches_tripping_tree(node->right, matches, cur);
	else if (*cur == node->c && node->down)
		return comple_bin_matches_tripping_tree(node->down, matches, cur + 1);
	else if (*cur == node->c && !node->down)
		return ;
}

char	**comple_bin_matches(t_line *line, t_comple *c, char *current_word)
{
	char		**matches;
	
	c->to_replace = get_start_word_cursor(line);
	matches = ft_memalloc(sizeof(char *) * 2000); ///////////////////////////////////////////////////
//	printf("\ncurrent_word is |%s|\n", current_word);
	comple_bin_matches_tripping_tree(singleton_env()->tree, matches, current_word);
	getchar();
	return (matches);
}
