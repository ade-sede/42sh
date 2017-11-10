char	*tilde_expansion(char *str)
{
	return (env_get_env(singleton_env()->environ, "HOME", NULL));
}
