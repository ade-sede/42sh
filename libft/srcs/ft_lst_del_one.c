#include "libft.h"


static void	is_middle_right(t_lst_head **head)
{
	if ((*head)->shift_middle == 1)
	{
		if ((*head)->middle->next != NULL)
		{
			(*head)->shift_middle = 0;
			(*head)->middle = (*head)->middle->next;
		}
		else
		{
			if ((*head)->middle->prev != NULL)
				(*head)->middle = (*head)->middle->prev;
		}
	}
}

static void	is_middle_left(t_lst_head **head)
{
	if ((*head)->shift_middle == -1)
	{
		if ((*head)->middle->prev != NULL)
		{
			(*head)->middle = (*head)->middle->prev;
			(*head)->shift_middle = 0;
		}
		else
		{
			if ((*head)->middle->next != NULL)
				(*head)->middle = (*head)->middle->next;
		}
	}
}

static void	relink_head(t_lst_head **head, int pos)
{
	if (pos == 1)
		if ((*head)->first->next != NULL)
		{
			(*head)->first = (*head)->first->next;
			(*head)->first->prev = NULL;
		}
	if (pos == 3)
		if ((*head)->last->prev != NULL)
		{
			(*head)->last = (*head)->last->prev;
			(*head)->last = NULL;
		}
	if (pos == 2)
	{
		if ((*head)->shift_middle == -1)
			is_middle_left(head);
		if ((*head)->shift_middle == 1)
			is_middle_right(head);
		if ((*head)->shift_middle == 0)
		{
			if ((*head)->middle->next != NULL)
			{
				(*head)->shift_middle -= 1;
				(*head)->middle = (*head)->middle->next;
			}
			else if ((*head)->middle->prev != NULL)
			{
				(*head)->shift_middle += 1;
				(*head)->middle = (*head)->middle->prev;
			}
		}
	}
}

void	ft_double_lst_del_one(t_lst_head **head, t_list_d *node, void (*f)(void*))
{
	int	pos;
	t_list_d	*prev;
	t_list_d	*next;

	if (node)
	{
		pos = 0;
		if (node == (*head)->first)
			pos = 1;
		if (node == (*head)->middle)
			pos = 2;
		if (node == (*head)->last)
			pos = 3;
		prev = node->prev;
		next = node->next;
		(f)(node->data);
		free(node);
		(*head)->node_count -= 1;
		if (pos != 0)
			relink_head(head, pos);
		if (prev != NULL)
			prev->next = next;
		if (next != NULL)
			next->prev = prev;
	}
}

void	ft_simple_lst_del_one(t_list **first, t_list *node, void(*f)(void*))
{
	t_list	*old_tmp;
	t_list	*curr_tmp;

	if (node)
	{
		curr_tmp = *first;
		while (curr_tmp && curr_tmp != node)
		{
			old_tmp = curr_tmp;
			curr_tmp = curr_tmp->next;
		}
		if (*first == node)
			*first = node->next;
		else
			old_tmp->next = curr_tmp->next;
		(f)(node->data);
		free(node);
	}
}
