
/*
**
** non relier
**
**
**
*/

#include "libft.h"
#include "../includes/history.h"
#include "get_next_line.h"

static int		ft_isspace(const char c)
{
	return (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ');
}

static char		*cut_w(char *s, int start, int end)
{
	char	*ret;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = 0;
	i = -1;
	ret = (char *)(s);
	while (*(s + ++i))
		if ((!ft_isspace(*(s + i))) && (i == 0 || ft_isspace(*(s + i - 1))))
			if (++len && (len == start + 1 || start == -1))
				ret = (char *)(s + i);
	end = (end < 0) ? len + end : end;
	start = (start < 0) ? len + start : start;
	if ((start && ret == s) || (len <= end) || start > end)
		return (NULL);
	if (s != ret)
		ret = ft_strcpy(s, ret);
	if (start && len == end)
		return (ret);
	while (len-- > end + 1)
	{
		while (ft_isspace(*(s + i)) || !*(s + i))
			i--;
		while ((--i >= 0) && (!ft_isspace(*(s + i))))
			;
	}
	while (ft_isspace(*(s + i)) || !*(s + i))
		i--;
	*(ret + i + 1) = '\0';
	return (ret);
}

char		*recup_number(int depl, t_lst_head *head)
{
	t_list_d *tmp;

	tmp = (depl < 0) ? head->first : head->last;
	depl += (depl < 0) ? 1 : -1;
	while (tmp && depl)
	{
		tmp = (depl < 0) ? tmp->next : tmp->prev;
		depl += (depl < 0) ? 1 : -1;
	}
	if (tmp)
		return (ft_strdup(tmp->data));
	return (NULL);
}


int			isdesignator(char c)
{
	return (c == '^' || c == '%' || c == '$' || c == '-' || c == '*');
}

char	*ft_strrnstr(const char *big, const char *little, size_t little_len)
{
	size_t	len;

	len = ft_strlen(big);
	if (!*little)
		return ((char*)big);
	while (*big && len)
	{
		if (ft_strncmp(big, little, little_len) == 0 && little_len <= len)
			return ((char*)big);
		big++;
		len--;
	}
	return (NULL);
}

char		*getset_str(char *str, int size)
{
	static char	*s = NULL;
	char		tmp;
	char		*tmp_str;

	if (str)
	{
		free(s);
		tmp_str = ft_strchr(str, ' ');
		if (tmp_str)
			if (tmp_str - str < size)
				size = tmp_str - str;
		tmp = *(str + size);

		*(str + size) = '\0';
		s = ft_strdup(str);
		*(str + size) = tmp;
		//ft_putendl(s);
	}
	return (s);
}

char		*recup_str_first(char **str, char *string)
{
	int		size;
	char	*ret;
	size = *str - string;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * size)))
		return (NULL);
	ft_strncpy(ret, string, size - 1);
	++(*str);
	return(ret);
}

char		*recup_str(char **str, t_list_d *lst, char *string)
{
	char		*ret;
	int			size;
	int			flag;

	size = 0;
	flag = 0;
	ret = NULL;
	if (**str == '#')
		return (recup_str_first(str, string));
	if (**str == '?' && (flag = 1))
	{
		ret = ft_strchr(++*str, '?');
		size = (ret) ? ret - *str : ft_strlen(*str);
		getset_str(*str, size);
	}
	else
		while (*(*str + size) && (!ft_isspace(*(*str + size)) &&
					*(*str + size) != ':' && !isdesignator(*(*str + size))))
			++size;
	while (lst && ((!flag) ? ft_strncmp(*str, lst->data, size) :
					(int)!ft_strrnstr(lst->data, *str, size)))
	{
		lst = lst->next;
	}
	*str += size + (ret != NULL);
	if (lst)
		return (ft_strdup(lst->data));
	return (NULL);
}

int			recup(char **str, t_lst_head *head, char **new, char *string)
{
	t_list_d	*tmp;
	int			depl;
	char		*save;

	save = ++*str;
	depl = -1;
	if (**str == '!')
		depl = -1;
	else if (**str != '0' && ((**str == '-' && ft_isdigit(*(*str + 1))) ||
				(ft_isdigit(**str))))
	{
		depl = ft_atoi(*str);
		if (**str == '-')
			++*str;
		while (ft_isdigit(*(*str + 1)))
			++*str;
	}
	else if (**str != ':' || --(*str))
		depl = 0;
	if (depl && ++*str)
		*new = recup_number(depl, head);
	else
		*new = recup_str(str, head->first, string);
	if (*new)
		return (0);
	**str = '\0';
	*str = save;
	return (3);
}

int 		cut_w_fprec(char **new)
{
	char *tmp;
	char *tmp2;
	char tmp_swap;

	//ft_putendl("tamere");
	tmp = ft_strstr(*new, getset_str(NULL, 0));
	if (!tmp || !getset_str(NULL, 0))
		return (5);
	tmp2 = ft_strchr(tmp, ' ');
	while (*tmp != ' ' && tmp > *new)
		--tmp;
	if (*tmp == ' ')
		++tmp;
	//ft_putendl(tmp);
	//ft_putendl(tmp2);
	if (tmp2)
		*tmp2 = '\0';
	ft_strcpy(*new, tmp);
	return (0);
}

int			designators(char **new, char **str)
{
	int		start;
	int		end;

	if (!((**str == ':' && ++(*str)) || isdesignator(**str)))
		return (-1);
	//ft_putendl(*str);
	if (isdesignator(**str) && **str != '%')
	{
		if (**str == '^')
		{
			start = 1;
			end = 1;
		}
		else if (**str == '$')
		{
			start = -1;
			end = -1;
		}
		else if (**str == '*')
		{
			start = 1;
			end = -1;
		}
		else if (**str == '-' && ft_isdigit(*(*str + 1)))
		{
			start = 0;
			end = ft_atoi(*str + 1);
			while (ft_isdigit(*(*str + 1)))
				++*str;
		}
		else if (**str == '-')
		{
			start = 0;
			end = -2;
		}
	}
	else if (ft_isdigit(**str))
	{
		start = ft_atoi(*str);
		end = start;
		while (ft_isdigit(**str))
			++*str;
		if (**str == '*')
			end = -1;
		else if (**str == '-' && ft_isdigit(*(*str + 1)))
		{
			end = ft_atoi(*str + 1);
			while (ft_isdigit(*(*str + 1)))
				++*str;
		}
		else if (**str == '-')
			end = -1 - 1;
		else
			--*str;
	}
	else if (**str == '%' && ++*str)
		return (cut_w_fprec(new));
	else if ((--(*str)))
		return (0);
	++*str;
	if ((*new = cut_w(*new, start, end)))
		return (0);
	return (2);
}

static char		*ft_strrchr_noend(const char *src, int s)
{
	char	*d;
	int		i;

	i = -1;
	d = (char *)src;
	while (*(++i + d + 1) != '\0')
		if (*(i + d) == s)
		{
			d += i;
			i = 0;
		}
	if (s == '\0')
		return (d + i);
	if (*d != s)
		return (NULL);
	return (d);
}

int			modifier_cut_pathname(char *sep, char **new, char **str)
{
	char	*middle;

	if (**str == *(sep + 1) || **str == *(sep + 2))
	{
		if (!(middle = ft_strrchr(*new, *sep)))
			return (0);
		if (!*(middle + 1))
		{
			while (*(--middle + 1) == *sep)
				*(middle + 1) = '\0';
			middle = ft_strrchr(*new, *sep);
		}
		if (**str == *(sep + 1))
			ft_strcpy(*new, middle + 1);
		else
			while (*(--middle + 1) == *sep)
				*(middle + 1) = '\0';
		return (1);
	}
	return (0);
}

int			modifier_cut_suffix(char *sep, char **new, char **str)
{
	char	*middle;

	if (**str == *(sep + 1) || **str == *(sep + 2))
	{
		if (!(middle = ft_strrchr(*new, *sep)))
			return (0);
		if (**str == *(sep + 1))
			ft_strcpy(*new, middle + 1);
		else
			*(middle) = '\0';
		return (1);
	}
	return (0);
}

static unsigned int	count_words_space(char const *s)
{
	unsigned int	i;
	unsigned int	nb_words;
	unsigned int	nb_space;
	unsigned int	nb_cote;

	i = 0;
	nb_words = 0;
	nb_cote = 0;
	nb_space = ft_isspace(*s);
	while (*(s + i))
	{
		while (*(s + i) && ft_isspace(*(s + i)) && ++i)
			if (ft_isspace(*(s + i)) || !*(s + i))
				++nb_space;
		if (*(s + i) && !ft_isspace(*(s + i)))
			nb_words++;
		while (*(s + i) && !ft_isspace(*(s + i)) && ++i)
			if (*(s + i - 1) == '\'')
				++nb_cote;
	}
	return ((nb_words + nb_space) * 2 + nb_cote * 3);
}

int			cotetage(char **new, int flag)
{
	int		nbrajout;
	char	*tmp;
	int		in_tmp;
	int		in_new;

	in_tmp = 0;
	in_new = 0;
	nbrajout = count_words_space(*new);
	if (!(tmp = (char *)ft_memalloc(ft_strlen(*new) + nbrajout + 1)))
		return (0);
	if (ft_isspace(**new))
	{
		ft_strcpy(tmp, "''");
		in_tmp += 2;
	}
	while (*(*new + in_new))
	{
		while (*(*new + in_new) && ft_isspace(*(*new + in_new)) && ++in_new)
		{
			*(tmp + in_tmp + in_new - 1) = *(*new + in_new - 1);
			if (ft_isspace(*(*new + in_new)) || !*(*new + in_new))
			{
				ft_strcpy(tmp + in_tmp + in_new, "''");
				in_tmp += 2;
			}
		}
		if (!*(*new + in_new))
			break ;
		*(tmp + ++in_tmp + in_new - 1) = '\'';
		while (*(*new + in_new) && (!ft_isspace(*(*new + in_new)) || flag == 1)
				&& ++in_new)
		{
			*(tmp + in_tmp + in_new - 1) = 'q';
			*(tmp + in_tmp + in_new - 1) = *(*new + in_new - 1);
			if (*(*new + in_new - 1) == '\'')
			{
				ft_strcpy(tmp + in_tmp + in_new, "\\''");
				in_tmp += 3;
				flag = ~flag;
			}
		}
		*(tmp + ++in_tmp + in_new - 1) = '\'';
	}
	free(*new);
	*new = tmp;
	return (1);
}

int			chop_chang(char **str, char ***chang)
{
	char	*separator;
	int		nb_echap;

	if (!**str)
		return (1);
	if (!*(*str + 1))
		return (0);
	if (*(*str + 1) == **str)
		return (2);
	if (!*chang)
		*chang = (char **)ft_memalloc(sizeof(char *) * 2);
	separator = *str;
	while ((separator = ft_strchr(separator + 1, **str)))
	{
		nb_echap = 0;
		while (*(separator - ++nb_echap) == '\\')
			;
		if (nb_echap % 2)
			break ;
	}
	if (separator)
		*separator = '\0';
	ft_strdel(*chang);
	**chang = ft_strdup(*str + 1);
	if (separator && (*separator = **str))
		*str = separator + 1;
	if (!separator)
	{
		while (**str && *(*str + 1))
			++*str;
		return (0);
	}
	while ((separator = ft_strchr(separator + 1, *(*str - 1))))
	{
		nb_echap = 0;
		while (*(separator - ++nb_echap) == '\\')
			;
		if (nb_echap % 2)
			break ;
	}
	if (separator)
		*separator = '\0';
	ft_strdel((*chang + 1));
	*(*chang + 1) = ft_strdup(*str);
	if (separator)
		(*separator = *(*str - 1));
	if (separator && (*separator = **str))
		*str = separator;
	else
		while (**str && *(*str + 1))
			++*str;
	return (0);
}

int			str_in_str(char **s, int symb, char *insert, int save_p)
{
	char	*tmp;
	int		ret;

	if (!insert)
		return (str_in_str(s, symb, "", save_p));
	ret = ft_strlen(insert);
	tmp = *s;
	if (!(*s = ft_memalloc((1 + ft_strlen(*s) - save_p + ret))))
		return (0);
	ft_strncpy(*s, tmp, symb);
	ft_strcat(*s + symb, insert);
	ft_strcat(*s + symb + ft_strlen(insert), tmp + symb + save_p);
	free(tmp);
	return (ret);
}

int			insert_chang(char **new, char **chang)
{
	char	*where;

	if (!chang)
		return (6);
	if (!(where = ft_strstr(*new, *chang)))
		return (7);
	str_in_str(new, where - *new, *(chang + 1), ft_strlen(*chang));
	return (0);
}

int			sed(char **str, char **new)
{
	static char		**chang = NULL;
	int				flag;
	int				ret;

	flag = (**str == 'g' && ++*str) ? 0 : 2;
	ret = 0;
	if ((**str == '&' && !chang))
		ft_strdel(new);
	if ((**str != 's' && **str != '&') && (ret = 2))
		ft_strdel(new);
	if (**str == 's' && ++*str)
		ret = chop_chang(str, &chang);
	if (ret)
		return (ret);
	while (--flag && !ret)
		ret = insert_chang(new, chang);
	ret = (flag < -2) ? 0 : ret;
	return (ret);
}

int			modifier(char **new, char **str)
{
	int ret;

	ret = 0;
	if (**str != ':')
		return (-1);
	++(*str);
	if (modifier_cut_pathname("/th", new, str))
		;
	else if (modifier_cut_suffix(".er", new, str))
		;
	else if (**str == 'x' || **str == 'q')
		cotetage(new, ~(**str == 'q'));
	else if (**str == 's' || **str == '&' || **str == 'g')
		ret = sed(str, new);
	else
		return (4);
	++*str;
	return (ret);
}

int			isbang(char c)
{
	return (!c || ft_isspace(c) || c == '(' || c == '=');
}

int			expansion(char **string, t_lst_head *head)
{
	char	*str;
	char	*str_change;
	char	*str_new;
	char	tmp;
	int		ret;

	if (!*string || !**string || !head)
		return (10);
	str = *string;
	while (*str != '!' || isbang(*(str + 1)))
	{
		++str;
		if (str && !*str)
			return (0);
	}
	str_change = str;
	if (!(ret = recup(&str, head, &str_new, *string)))
		ret = designators(&str_new, &str);
	while (!ret && !(ret = modifier(&str_new, &str)))
		;
	if (ret == -1)
	{
		if (str_new)
			str_in_str(string, str_change - *string, str_new, str - str_change);
		else
			ft_strcpy(str_change, str);//strcpy
		free(str_new);
		return (expansion(string, head));
	}
	ft_strncpy(*string, str_change, str - str_change);
	return (ret);
}

void		bang_error(int error, char *str)
{
	if (error == 1)
	{
		ft_putstr_fd("modifier failed: ", 2);
		ft_putstr_fd(str, 2);
	}
	else if (error == 2)
		ft_putstr_fd("no such word in event", 2);
	else if (error == 3)
	{
		ft_putstr_fd("no such event: ", 2);
		ft_putstr_fd(str, 2);
	}
	else if (error == 4)
		ft_putstr_fd("unrecognized history modifier: ", 2);
	else if (error == 5)
		ft_putstr_fd("ambiguous history reference", 2);
	else if (error == 6)
		ft_putstr_fd("no previous substitution", 2);
	else if (error == 7)
		ft_putstr_fd("substitution failed", 2);
	else if (error == 8)
		ft_putstr_fd("bad word specifier", 2);
	else if (error == 10)
		ft_putstr_fd("commande ou historique vide", 2);
	write(1, "\n", 2);
}

int			history_load_test(const char *target, t_lst_head **head)
{
	int			fd;
	char		*line;
	char		*cat;
	t_list_d	*list;

	cat = NULL;
	if ((fd = open(target, O_RDWR | O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		if (cat)
		{
			cat[ft_strlen(cat) - 1] = '\n';
			cat = ft_strjoin_free(cat, line, 0b11);
		}
		if (!cat)
			cat = line;
		if (charcmp(cat, ft_strlen(cat) - 1, '\\'))
			continue ;
		list = ft_double_lst_create(cat);
		cat = NULL;
		if (*head == NULL)
			*head = ft_create_head(list);
		else
			ft_double_lst_add(head, list);
	}
	close(fd);
	return (1);
}

int main(int ac, char **av)
{
	char *str;
	int i;

	t_lst_head *head;

	head = NULL;
	history_load_test(".21sh_history", &head);

	str = ft_strdup("dfs !#!#!#!#:q:q:q:q !#:q !#:q !#:q:q:q:q:q:q:q:q:q:q:q:q");
	ft_putendl(str);
	ft_putendl("start");
	i = expansion(&str, head);
	ft_putendl("end");
	ft_putnbr(i);
	if (i)
		bang_error(i, str);
	else
		ft_putendl(str);
}
