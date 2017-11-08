char	*remove_quote(char *value)
{
	return (ft_strchange(value, ft_strsub(value, 1, ft_strlen(value) - 2));
}
