#include "libft.h"
#include "t_env.h"
#include "environ.h"
#include "failure.h"

static int	update_pwd_old_pwd(char *cwd_before_chdir)
{
	char	buf[PATH_MAX];
	t_env	*env;
	char	*cwd;

	env = singleton_env();
	ft_bzero(buf, PATH_MAX);
	if ((cwd = getcwd(buf, PATH_MAX)) == NULL)
		return (investigate_error(1, "cd", NULL, -1));
	env_add_change(env, "PWD", (const char*)cwd);
	if (cwd_before_chdir)
		env_add_change(env, "OLDPWD", (const char*)cwd_before_chdir);
	else
		env_remove_var(env, "OLDPWD");
	free(cwd_before_chdir);
	return (EXIT_SUCCESS);
}

static int	return_builtin_cd(char *new_pwd, char *cwd_before_chdir)
{
	if (chdir(new_pwd) == -1)
	{
		free(cwd_before_chdir);
		return (investigate_error(1, "cd", NULL, -1));
	}
	return (update_pwd_old_pwd(cwd_before_chdir));
}

int			builtin_cd(t_env *env, const char **argv)
{
	char	buf[PATH_MAX];
	char	*cwd_before_chdir;
	char	*new_pwd;

	cwd_before_chdir = NULL;
	if (ft_arraylen(argv) == 1)
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "HOME", NULL)))
			return (investigate_error(1, NULL,
						"cd: HOME not set", EXIT_FAILURE));
	}
	else if (ft_strequ(argv[1], "-"))
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "OLDPWD", NULL)))
			return (investigate_error(1, NULL,
						"cd: OLDPWD not set", EXIT_FAILURE));
	}
	else
		new_pwd = (char*)argv[1];
	ft_bzero(buf, PATH_MAX);
	if ((cwd_before_chdir = ft_strdup(getcwd(buf, PATH_MAX))) == NULL)
		investigate_error(1, "cd", NULL, -1);
	return (return_builtin_cd(new_pwd, cwd_before_chdir));
}
