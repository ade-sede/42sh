#include "libft.h"
#include <unistd.h>
#include "t_env.h"
#include "exec.h"
#include "builtin.h"
#include "history.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "job_control.h"
#include "parser.h"
#include "local.h"

void	exec_main_loop(t_ast *ast)
{
	int			exit_status;
	char		nbr[20];

	singleton_jc()->background = 0;
	if (singleton_jc()->shell_is_interactive)
	{
		parse_heredoc(ast);
		conf_term_canonical();
	}
	exit_status = exec(ast);
	local_add_change_from_key_value(singleton_env(), "?",
			ft_itoa_word(exit_status, nbr));
	if (singleton_jc()->shell_is_interactive)
		conf_term_non_canonical();
}
