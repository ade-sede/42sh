#include "exec.h"

struct t_token_id_to_string	tts[] =
{
	{TK_WORD,"tk_word"},
	{TK_ASSIGNMENT_WORD,"tk_assignment_word"},
	{TK_NAME,"tk_name"},
	{TK_NEWLINE,"tk_newline"},
	{TK_IO_NUMBER,"tk_io_number"},
	{TK_LESS , "tk_less"},
	{TK_HERE,"tk_here"},
	{TK_GREAT,"tk_great"},
	{TK_SEMI,"tk_semi"},
	{TK_PIPE,"tk_pipe"},
	{TK_AND,"tk_and"},
	{TK_AND_IF,"tk_and_if"},
	{TK_OR_IF,"tk_or_if"},
	{TK_DSEMI,"tk_dsemi"},
	{TK_DLESS,"tk_dless"},
	{TK_DGREAT,"tk_dgreat"},
	{TK_LESSAND,"tk_lessand"},
	{TK_GREATAND,"tk_greatand"},
	{TK_LESSGREAT,"tk_lessgreat"},
	{TK_DLESSDASH,"tk_dlessdash"},
	{TK_CLOBBER,"tk_clobber"},
	{TK_IF, "TK_IF2"},
	{TK_THEN,"tk_then"},
	{TK_ELSE,"tk_else"},
	{TK_ELIF,"tk_elif"},
	{TK_FI,"tk_fi"},
	{TK_DO,"tk_do"},
	{TK_DONE,"tk_done"},
	{TK_CASE,"tk_case"},
	{TK_ESAC,"tk_esac"},
	{TK_WHILE,"tk_while"},
	{TK_UNTIL,"tk_until"},
	{TK_FOR,"tk_for"},
	{TK_LBRACE,"tk_lbrace"},
	{TK_RBRACE,"tk_rbrace"},
	{TK_BANG,"tk_bang"},
	{TK_LPAREN,"tk_lparen"},
	{TK_RPAREN,"tk_rparen"},
	{TK_IN,"tk_in"},
	{$ , "tk_dollard"},
};

void	debug_token(t_token *token)
{
	if (!token)
	{
		printf("token not found\n");
		return ;
	}
	int	i= 0;
	while (tts[i].string)
	{
		if (token->id == tts[i].id)
		{
			printf("%s\n", tts[i].string);
			return ;
		}
		i++;
	}
}
