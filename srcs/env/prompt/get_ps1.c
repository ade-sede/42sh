#include "libft.h"
#include "unistd.h"
#include "t_env.h"
#include "prompt.h"
#include "sys/wait.h"
#include "get_next_line.h"
#include "line_editing.h"
#include "failure.h"
#include "local.h"

static void	trim_newline(char *str)
{
	if (!str)
		return ;
	if (*str == '\n')
		*str = 32;
}

char		*get_ps1(t_env *env, size_t *len)
{
	char *git_status;
	char *current_dir;
	char *previous_exit;

	//protected variable
	previous_exit = (ft_atoi(local_get_value(env->local, "?")) == 0) ? \
		ft_strjoin3_free(GRN, "➜  ", RESET, 0) : \
			ft_strjoin3_free(RED, "➜  ", RESET, 0);
	*len += 3;
	if ((current_dir = get_current_directory()) == NULL)
		current_dir = ft_strnew(0);
	ft_striter(current_dir, &trim_newline);
	*len += ft_strlen(current_dir);
	current_dir = ft_strjoin3_free(CYN, current_dir, RESET, 2);
	git_status = get_git_status(len);
	return (ft_strjoin3_free(previous_exit, current_dir, git_status, 7));
}
