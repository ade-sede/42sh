#include "line_editing.h"

t_line		*singleton_line(void)
{
	static t_line	s;

	return (&s);
}

void		edit_line_init(void)
{
	ft_bzero(singleton_line()->buff, singleton_line()->len);
	singleton_line()->pos = 0;
	singleton_line()->len = 0;
}
