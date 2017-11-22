#include "t_history.h"
#include "libft.h"

t_histfile	*create_histfile(const char *filename)
{
	t_histfile *histfile;

	histfile = ft_memalloc(sizeof(t_histfile));
	if (filename)
		histfile->filename = ft_strdup(filename);
	histfile->ln = 0;
	histfile->last_cmd = NULL;
	return (histfile);
}

t_histfile	*get_histfile(t_list *histfile, const char *filename)
{
	t_histfile *node;

	if (!filename)
	{
		if (histfile)
			return (histfile->data);
	}
	while (histfile)
	{
		node = histfile->data;
		if (ft_strequ(filename, node->filename))
			break ;
		histfile = histfile->next;
	}
	if (histfile)
		return (histfile->data);
	return (NULL);
}

t_histfile	*add_histfile(t_list **histfile_l, const char *filename)
{
	t_histfile *histfile;

	histfile = NULL;
	if (!(histfile = get_histfile(*histfile_l, filename)))
	{
		histfile = create_histfile(filename);
		ft_simple_lst_pushback(histfile_l, ft_simple_lst_create(histfile));
	}
	return (histfile);
}
