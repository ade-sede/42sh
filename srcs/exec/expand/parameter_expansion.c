char	*parameter_expansion(char *str)
{
	return (env_get_env(singleton_env()->environ, str, NULL));
}
