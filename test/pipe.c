/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 16:20:41 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/08 16:21:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
**	See libft/test/redir.c and this file. 
**	References pour la creation de pipes interprocess
*/
			pid_t		child;
			t_pipe		*pr;
			t_pipe		*pl;
			int			*p_right;
			int			*p_left;
			int			save;
			t_list_d	*cur;

			cur = head->middle;
			pr = (cur != NULL) ? cur->data : NULL;
			pl = (cur && cur->prev) ? cur->prev->data : NULL;
			p_right = (pr) ? pr->p : NULL;
			p_left = (pl) ? pl->p : NULL;

			if (p_right && !p_left) // If our command is on the left of a pipe (WRITE_END)
			{
				child = fork();
				if (child == 0) // In child process
				{
					/* Write to the pipe to the right */
					dup2(p_right[WRITE_END], STDOUT_FILENO);
					close(p_right[READ_END]); // Looks like its optional
					/* Execute the command (execve call) */
					exec_simple_command(ast, head);
					/* All FDs are closed from this process */
					close(p_right[WRITE_END]); // Looks like its optional
					exit(0);
				}
				else
				{
					pr->pid = child;
				}
			}
			else if (p_right && p_left) // Between pipes
			{
				child = fork();
				if (child == 0)
				{
					/* Read from the pipe on the left */
					dup2(p_left[READ_END], STDIN_FILENO);
					close(p_left[WRITE_END]);
					/* Write to the next pipe */
					dup2(p_right[WRITE_END], STDOUT_FILENO);
					close(p_right[READ_END]);
					/* Execute the command (execve call) */
					exec_simple_command(ast, head);
					close(p_right[WRITE_END]);
					close(p_left[READ_END]);
					exit(0);
				}
				else
				{
					close(p_left[WRITE_END]);
					pr->pid = child;
				}
			}
			else if (p_left && !p_right) // Right of the pipe ; happens in the main process.
			{
				/* Save STD INPUT */

				save = dup(STDIN_FILENO);
				/* Read from the pipe on the left */
				dup2(p_left[READ_END], STDIN_FILENO);
				close(p_left[WRITE_END]);
				/* Execute the command */
				exec_simple_command(ast, head);
				/* Restore fd 0 as the STD INPUT */
				close(p_left[READ_END]);
				dup2(save, STDIN_FILENO);
				close(save);
			}
			else // Not pipe related
				exec_simple_command(ast, head);
