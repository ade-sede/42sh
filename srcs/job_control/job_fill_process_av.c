#include "exec.h"
#include "job_control.h"

t_process	*fill_process_av(t_ast *ast, t_process *process)
{
	int	i;
	t_ast	*child;

	i = 0;
	while (ast && ast->child[i])
	{
		child = ast->child[i];
		if (child && child->token)
			process->av = ft_strjoin3_free(process->av, " ", child->token->value, 4);
		else
			fill_process_av(child, process);
		i++;
	}
	return (process);
}

