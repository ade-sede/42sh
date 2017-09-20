#include "libft.h"
#include "env.h"
#include "failure.h"

static int	update_pwd_old_pwd(char *cwd_before_chdir)
{
	char	buf[PATH_MAX];
	t_env	*env;
	char	*cwd;

	env = singleton_env();
	if ((cwd = getcwd(buf, PATH_MAX)) == NULL)
		return (investigate_error("cd", NULL, -1));
	env_add_change(env, "PWD", (const char*)cwd);
	env_add_change(env, "OLDPWD", (const char*)cwd_before_chdir);
	free(cwd_before_chdir);
	return (EXIT_SUCCESS);
}

int			builtin_cd(t_env *env, const char **argv)
{
	char	buf[PATH_MAX];
	char	*cwd_before_chdir;
	char	*new_pwd;

	if (ft_arraylen(argv) == 1)
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "HOME", NULL)))
			return (investigate_error(NULL, "cd: HOME not set", EXIT_FAILURE));
	}
	else if (ft_strequ(argv[1], "-"))
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "OLDPWD", NULL)))
			return (investigate_error(NULL, "cd: OLDPWD not set", EXIT_FAILURE));
	}
	else
		new_pwd = (char*)argv[1];
	ft_bzero(buf, PATH_MAX);
	if ((cwd_before_chdir = ft_strdup(getcwd(buf, PATH_MAX))) == NULL)
		return (investigate_error("cd", NULL, -1));
	ft_bzero(buf, PATH_MAX);
	if (chdir(new_pwd) == -1)
	{
		free(cwd_before_chdir);
		return (investigate_error("cd", NULL, -1));
	}
	return (update_pwd_old_pwd(cwd_before_chdir));
}
