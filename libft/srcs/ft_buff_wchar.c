#include "libft.h"

char	*ft_buff_wchar(wchar_t c)
{
	char	*s;

	s = malloc(sizeof(char) * 4 + 1);
	ft_bzero(s, 5);
	if (c <= 0x7F)
		s[0] = c;
	else if (c < 0x7FF)
	{
		s[0] = ((c >> 6) + 0xC0);
		s[1] = ((c & 0x3F) + 0x80);
	}
	else if (c < 0xFFFF)
	{
		s[0] = ((c >> 12) + 0xE0);
		s[1] = ((c >> 6 & 0x3f) + 0x80);
		s[2] = ((c & 0x3F) + 0x80);
	}
	else if (c < 0x10FFFF)
	{
		s[0] = ((c >> 18) + 0xF0);
		s[1] = ((c >> 12) + 0x3F);
		s[2] = ((c & 0x3F) + 0x80);
		s[3] = ((c & 0x3F) + 0x80);
	}
	return (s);
}
