#include "completion.h"
#include "line_editing.h"
#include <stdio.h>
#include <string.h>

char	*get_word_slash(t_line *line)
{
	char	*word;

	word = line->buff + line->pos;
	while (word > line->buff && (*word != ' ') && (*word != '/'))
	{ 
		//printf("\n%c\n", *word);
		word--;
	}
	return ((*word == '/') ?  word : NULL); 
}

char	*get_start_word_cursor(t_line *line)
{
	char	*word;

	word = line->buff + line->pos;
	while (word > line->buff && (*word != ' '))
	{ 
		//printf("\n%c\n", *word);
		word--;
	}
	word = (*word == ' ') ? word + 1 : word;
	return (word);
}

void	delete_word_cursor(t_line *line)
{
	char	*word;
	char	*end;
	
	end = NULL;
	word = line->buff + line->pos;
	while (word > line->buff && (*word != ' '))
	{ 
		printf("\n%c\n", *word);
		word--;
	}
	word = (*word == ' ') ? word + 1 : word;
	end = ft_strchr(word, ' ');
	if (end)
	{
		ft_memmove(word, end, ft_strlen(end));
		ft_strclr(word + ft_strlen(end));
	}
	else
		ft_strclr(word);
}

void	delete_word(char *to_replace)
{
	char	*end;

	end = ft_strchr(to_replace, ' ');
	if (end)
	{
		ft_memmove(to_replace, end, ft_strlen(end));
		ft_strclr(to_replace + ft_strlen(end));
	}
	else
		ft_strclr(to_replace);
}

char	*get_current_word_cursor(t_line *line)
{
	char	*word;
	char	*end;
	char	tmp;

	end = NULL;
	word = get_start_word_cursor(line);
	end = ft_strchr(word, ' ');
	if (end)
	{
		tmp = *end;
		*end = '\0';
	}
	word = ft_strdup(word);
	if (end)
		*end = tmp;
	return (word);
}

char	**array_matches(char *dir_match, char *to_match)
{
	struct dirent	*dirent;
	DIR		*dir;
	char		**matches;
	int		i;

	i = 0;
	dir = NULL;
	matches = ft_memalloc(sizeof(char *) * 1000); ///////////////////////////////////////////////////
	dir = (dir_match) ? opendir(dir_match) : opendir(".");
	if (!dir)
	{
		printf("open was a failure\n");
		return (matches);
	}
	while ((dirent = readdir(dir)) != NULL)
	{
		//printf("\nd_name: %s to_match: %s\n", dirent->d_name, to_match);
		if (!to_match || ft_strstr(dirent->d_name, to_match))
		{
			matches[i] = ft_strdup(dirent->d_name);
			printf("\nd_name: %s\n", matches[i]);
			i++;
		}
	}
	closedir(dir);
	return (matches);
}

void	split_word(char *str, char *separator, char **head, char **queu)
{
	char tmp;

	tmp = *separator;
	*separator = '\0';
	*head = ft_strdup(str);
	*queu = ft_strdup(separator + 1);
	*separator = tmp;
}

char	**comple_file_matches(t_line *line)
{
	char		*to_match;
	char		*dir_match;

	to_match = NULL;
	dir_match = NULL;
	to_match = get_current_word_cursor(line);
	singleton_comple()->to_replace = get_start_word_cursor(line); 
	printf("\nto_match: %s, dir_match: %s\n", (to_match) ? to_match : "null", (dir_match) ? dir_match : "null");
	if (to_match && ft_strichr(to_match, '/') != -1)
	{
		singleton_comple()->to_replace = get_word_slash(line) + 1; 
		split_word(to_match, ft_strrchr(to_match, '/'), &dir_match, &to_match); 
	}
printf("\nto_match: %s, dir_match: %s\n", (to_match) ? to_match : "null", (dir_match) ? dir_match : "null");
	return (array_matches(dir_match, to_match));
}
