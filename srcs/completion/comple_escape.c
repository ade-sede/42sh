#include "completion.h"
#include "line_editing.h"
#include "failure.h"
#include <string.h>
#include "libft.h"

/*
**	Returns the fully escaped name of the string it received as input in a way
**	that will allow the shell to reverse the process and find the origin string
**	after lexing and parsing.
*/

static size_t	escaped_size(char *input)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' || input[i] == '"' || input[i] == '\'' ||
				input[i] == '$')
			++size;
		if (input[i] == '\n')
			size += 4;
		++i;
		++size;
	}
	return (size);
}

char			*comple_escape(size_t i, size_t j, char *input)
{
	char	*escaped_str;

	escaped_str = ft_memalloc(sizeof(char*) *(escaped_size(input) + 1));
	while (input[i] != 0)
	{
		if (input[i] == '\\' || input[i] == '"' || input[i] == '\'' ||
				input[i] == '$')
			escaped_str[j++] = '\\';
		if (input[i] == '\n')
		{
			escaped_str[j++] = '$';
			escaped_str[j++] = '\'';
			escaped_str[j++] = '\\';
			escaped_str[j++] = 'n';
			escaped_str[j] = '\'';
		}
		else
			escaped_str[j] = input[i];
		++i;
		++j;
	}
	return (escaped_str);
}
