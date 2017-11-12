typedef struct	s_field_lst
{
	struct s_field_lst	*next;
	char				*value;
	int					expand;
	int					start;
	int					end;
}				t_field_lst;

typedef struct	s_token_lst
{
	struct s_token_lst	*next;
	char				*value;
	t_field_lst			*first_field;
}				t_token_lst;


typedef struct	s_expand
{
	int			state;
	t_token_lst	*first_token;
}				t_expand;

/*
**	AUTOMATA:
**
**	1 step is delimi
**		- List of states
**		- When do i consider a token finished ?
**			Everytime I changed state, the preceding token is delimited. (with a push, or a pop : doesn't matter)
**
**	PUSH AND POP:
**		Data which must be available after operation : state, start, end
**	If pop : state must disappear from the stack.
**	If push: State must stay on the stack.
**
**	2 step is creating
**		- Create data struct.
**		- Determine if it matters or not.
**
**	Everytime a token is created, treat it.
**
** state
** {
**		int		state;
**		int		start;
**		int		end;
** }
**
**	struct s_expand_token
**	{
**		state_stack	[2]
**	}
**
**	"q $lol*/
${dsadsadsa:-"dsaads${dfsdfsdfs}"}
