/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */ /*   list_test.c                                        :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:42:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/12 12:14:26 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "printf.h"

int		return_is_okay(void *p)
{
	if (ft_strcmp("14", p) == 0)
		return (1);
	return (0);
}

void	print_simple(t_list *node)
{
	ft_printf("%s\n", node->data);
}

static void	del_str(void *lol)
{
	free(lol);
}

static int	simple_is_okay(t_list *node1, t_list *node2)
{
	int	i;
	int	j;
	
	i = atoi(node1->data);
	j = atoi(node2->data);
	if (i == j)
	{
		/* printf("0"); */
		return (0);
	}
	if (i < j)
	{
		/* printf("1\n"); */
		return (1);
	}
	if (i > j)
	{
		/* printf("1\n"); */
		return (-1);
	}
	return (0);
}

static int double_is_okay(t_list_d *node1, t_list_d *node2)
{
	int	i;
	int	j;
	
	i = atoi(node1->data);
	j = atoi(node2->data);
	if (i == j)
	{
		/* printf("0"); */
		return (0);
	}
	if (i < j)
	{
		/* printf("1\n"); */
		return (1);
	}
	if (i > j)
	{
		/* printf("1\n"); */
		return (-1);
	}
	return (0);
}

static void	change_double(t_list_d *first)
{
	first->data = "lol";
}

static void	print_double(t_list_d *first)
{
		ft_printf("%s\n", first->data);
}

static void double_add(t_lst_head **head)
{
	ft_printf("\n%s\n", __func__);
	t_list_d	*node0;
	t_list_d	*node1;
	t_list_d	*node2;
	t_list_d	*node3; t_list_d	*node4;
	t_list_d	*node5;
	t_list_d	*first;

	node0 = ft_double_lst_create(ft_itoa_base(1, 10));
	node1 = ft_double_lst_create(ft_itoa_base(2, 10));
	node2 = ft_double_lst_create(ft_itoa_base(3, 10));
	node3 = ft_double_lst_create(ft_itoa_base(4, 10));
	node4 = ft_double_lst_create(ft_itoa_base(5, 10));
	node5 = ft_double_lst_create(ft_itoa_base(6, 10));
	ft_double_lst_add(head, node0);
	ft_double_lst_add(head, node1);
	ft_double_lst_add(head, node2);
	ft_double_lst_add(head, node3);
	ft_double_lst_add(head, node4);
	ft_double_lst_add(head, node5);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	/* print_double(ft_double_lst_get_n((*head)->last, -2)); */
	ft_printf(" List has %d\n", (*head)->node_count);

}

static void double_pushback(t_lst_head **head)
{
	ft_printf("\n%s\n", __func__);
	t_list_d	*node0;
	t_list_d	*node1;
	t_list_d	*node2;
	t_list_d	*node3;
	t_list_d	*node4;
	t_list_d	*node5;
	t_list_d	*first;

	node0 = ft_double_lst_create(ft_itoa_base(1, 10));
	node1 = ft_double_lst_create(ft_itoa_base(2, 10));
	node2 = ft_double_lst_create(ft_itoa_base(3, 10));
	node3 = ft_double_lst_create(ft_itoa_base(4, 10));
	node4 = ft_double_lst_create(ft_itoa_base(5, 10));
	node5 = ft_double_lst_create(ft_itoa_base(6, 10));
	ft_double_lst_pushback(head, node0);
	ft_double_lst_pushback(head, node1);
	ft_double_lst_pushback(head, node2);
	ft_double_lst_pushback(head, node3);
	ft_double_lst_pushback(head, node4);
	ft_double_lst_pushback(head, node5);
	ft_double_lst_foreach((*head)->last, NULL, print_double, 1);
	/* print_double(ft_double_lst_get_n((*head)->last, -2)); */
	ft_printf(" List has %d\n", (*head)->node_count);
}

static void	get_head_info(t_lst_head **head)
{
	ft_printf("---------------------------\n");
	ft_printf("Number of nodes -> %d\n", (*head)->node_count);
	ft_printf("First is -> %s\n", (*head)->first->data);
	/* ft_printf("Middle is -> %s\n", (*head)->middle->data); */
	ft_printf("Last is -> %s\n", (*head)->last->data);
	ft_printf("Shift middle = %d\n", (*head)->shift_middle);
	ft_printf("---------------------------\n");
}

static void double_del_one_2(t_lst_head **head)
{
	ft_printf("\n%s\n", __func__);
	t_list_d	*node0;
	t_list_d	*node1;
	t_list_d	*node2;
	t_list_d	*node3;
	t_list_d	*node4;
	t_list_d	*node5;
	t_list_d	*first;

	node0 = ft_double_lst_create(ft_itoa_base(1, 10));
	node1 = ft_double_lst_create(ft_itoa_base(2, 10));
	node2 = ft_double_lst_create(ft_itoa_base(3, 10));
	node3 = ft_double_lst_create(ft_itoa_base(4, 10));
	node4 = ft_double_lst_create(ft_itoa_base(5, 10));
	node5 = ft_double_lst_create(ft_itoa_base(6, 10));

	ft_double_lst_pushback(head, node0);
	ft_double_lst_pushback(head, node1);
	ft_double_lst_pushback(head, node2);
	ft_double_lst_pushback(head, node3);
	ft_double_lst_pushback(head, node4);
	ft_double_lst_pushback(head, node5);

	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	get_head_info(head);

	ft_double_lst_del_one(head, node2, del_str);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	get_head_info(head);

	ft_double_lst_del_one(head, node4, del_str);
	ft_double_lst_foreach((*head)->last, NULL, print_double, -1);
	get_head_info(head);

	ft_double_lst_del_one(head, node5, del_str);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	get_head_info(head);

	ft_double_lst_del_one(head, node3, del_str);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	get_head_info(head);

	ft_double_lst_del_one(head, node1, del_str);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	get_head_info(head);

	ft_double_lst_del_one(head, node0, del_str);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	get_head_info(head);

	/* print_double(ft_double_lst_get_n((*head)->last, -2)); */
}





static void	double_sort_insert(t_lst_head **head)
{
	ft_printf("\n%s\n", __func__);
	t_list_d	*node0;
	t_list_d	*node1;
	t_list_d	*node2;
	t_list_d	*node3;
	t_list_d	*node4;
	t_list_d	*node5;
	t_list_d	*node6;
	t_list_d	*node7;
	t_list_d	*first;

	node0 = ft_double_lst_create(ft_itoa_base(2, 10));
	node1 = ft_double_lst_create(ft_itoa_base(8, 10));
	node2 = ft_double_lst_create(ft_itoa_base(8, 10));
	node3 = ft_double_lst_create(ft_itoa_base(5, 10));
	node4 = ft_double_lst_create(ft_itoa_base(1, 10));
	node5 = ft_double_lst_create(ft_itoa_base(7, 10));
	node6 = ft_double_lst_create(ft_itoa_base(1, 10));
	node7 = ft_double_lst_create(ft_itoa_base(0, 10));
	ft_double_lst_sort_insert(head, node0, double_is_okay);
	ft_double_lst_sort_insert(head, node1, double_is_okay);
	ft_double_lst_sort_insert(head, node2, double_is_okay);
	ft_double_lst_sort_insert(head, node3, double_is_okay);
	ft_double_lst_sort_insert(head, node4, double_is_okay);
	ft_double_lst_sort_insert(head, node5, double_is_okay);
	ft_double_lst_sort_insert(head, node6, double_is_okay);
	ft_double_lst_sort_insert(head, node7, double_is_okay);
	ft_printf("\n");
	ft_double_lst_for_n((*head)->first, 10000, print_double, 1);
}



static void	double_del_one_and_remove(t_lst_head **head)
{
	ft_printf("\n%s\n", __func__);
	t_list_d	*node0;
	t_list_d	*node1;
	t_list_d	*node2;
	t_list_d	*node3;
	t_list_d	*node4;
	t_list_d	*node5;
	t_list_d	*node6;
	t_list_d	*first;

	node0 = ft_double_lst_create(ft_itoa_base(2, 10));
	node1 = ft_double_lst_create(ft_itoa_base(8, 10));
	node2 = ft_double_lst_create(ft_itoa_base(9, 10));
	node3 = ft_double_lst_create(ft_itoa_base(5, 10));
	node4 = ft_double_lst_create(ft_itoa_base(1, 10));
	node5 = ft_double_lst_create(ft_itoa_base(7, 10));
	node6 = ft_double_lst_create(ft_itoa_base(8, 10));
	ft_double_lst_sort_insert(head, node0, double_is_okay);
	ft_double_lst_sort_insert(head, node1, double_is_okay);
	ft_double_lst_sort_insert(head, node2, double_is_okay);
	ft_double_lst_sort_insert(head, node3, double_is_okay);
	ft_double_lst_sort_insert(head, node4, double_is_okay);
	ft_double_lst_sort_insert(head, node5, double_is_okay);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	ft_printf("first is %s\n", (*head)->first->data);
	ft_printf("middle is %s\n", (*head)->middle->data);
	ft_printf("last is %s\n", (*head)->last->data);
	ft_printf(" List has %d\n", (*head)->node_count);
	ft_double_lst_del_one(head, node3, del_str);
	ft_printf(" List has %d\n", (*head)->node_count);
	ft_double_lst_sort_insert(head, node6, double_is_okay);
	ft_double_lst_foreach((*head)->first, NULL, print_double, 1);
	ft_printf("first is %s\n", (*head)->first->data);
	ft_printf("middle is %s\n", (*head)->middle->data);
	ft_printf("last is %s\n", (*head)->last->data);
	ft_remove_head(head, del_str);
	if (*head == NULL)
		ft_printf("SUCCESS\n");
}


void	simple_add(void)
{
	ft_printf("\n%s\n", __func__);
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*node4;
	t_list	*node5;

	node0 = ft_simple_lst_create(ft_itoa_base(0, 10));
	node1 = ft_simple_lst_create(ft_itoa_base(1, 10));
	node2 = ft_simple_lst_create(ft_itoa_base(2, 10));
	node3 = ft_simple_lst_create(ft_itoa_base(3, 10));
	node4 = ft_simple_lst_create(ft_itoa_base(4, 10));
	node5 = ft_simple_lst_create(ft_itoa_base(5, 10));
	ft_simple_lst_add(&node0, node1);
	ft_simple_lst_add(&node0, node2);
	ft_simple_lst_add(&node0, node3);
	ft_simple_lst_add(&node0, node4);
	ft_simple_lst_add(&node0, node5);
	ft_simple_lst_foreach(node0, NULL, print_simple);

}

void	simple_pushback(void)
{
	ft_printf("\n%s\n", __func__);
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*node4;
	t_list	*node5;

	node0 = ft_simple_lst_create(ft_itoa_base(0, 10));
	node1 = ft_simple_lst_create(ft_itoa_base(1, 10));
	node2 = ft_simple_lst_create(ft_itoa_base(2, 10));
	node3 = ft_simple_lst_create(ft_itoa_base(3, 10));
	node4 = ft_simple_lst_create(ft_itoa_base(4, 10));
	node5 = ft_simple_lst_create(ft_itoa_base(5, 10));
	ft_simple_lst_pushback(&node0, node1);
	ft_simple_lst_pushback(&node0, node2);
	ft_simple_lst_pushback(&node0, node3);
	ft_simple_lst_pushback(&node0, node4);
	ft_simple_lst_pushback(&node0, node5);
	ft_simple_lst_foreach(node0, NULL, print_simple);
	ft_printf("\n");
	ft_printf("%s\n", ft_simple_lst_get_n(node0, 2)->data);
}


void	simple_del_one_and_remove2(void)
{
	ft_printf("\n%s\n", __func__);
	t_list	*node0;

	node0 = ft_simple_lst_create(ft_itoa_base(0, 10));
	ft_simple_lst_del_one(&node0, node0, del_str);
}

void	simple_del_one_and_remove(void)
{
	ft_printf("\n%s\n", __func__);
	t_list	**first;
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*node4;
	t_list	*node5;

	node0 = ft_simple_lst_create(ft_itoa_base(0, 10));
	node1 = ft_simple_lst_create(ft_itoa_base(1, 10));
	node2 = ft_simple_lst_create(ft_itoa_base(2, 10));
	node3 = ft_simple_lst_create(ft_itoa_base(3, 10));
	node4 = ft_simple_lst_create(ft_itoa_base(4, 10));
	node5 = ft_simple_lst_create(ft_itoa_base(5, 10));
	ft_simple_lst_pushback(&node0, node1);
	ft_simple_lst_pushback(&node0, node2);
	ft_simple_lst_pushback(&node0, node3);
	ft_simple_lst_pushback(&node0, node4);
	ft_simple_lst_pushback(&node0, node5);
	*first = node0;
	ft_simple_lst_foreach(*first, NULL, print_simple);
	ft_simple_lst_del_one(first, node3, del_str);
	ft_printf("\n");
	ft_simple_lst_foreach(*first, NULL, print_simple);
	ft_simple_lst_del_one(first, node0, del_str);
	ft_printf("\n");
	ft_simple_lst_foreach(*first, NULL, print_simple);
}
void	simple_sort_insert(void)
{
	ft_printf("\n%s\n", __func__);
	t_list	**first;
	t_list	*node0;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*node4;
	t_list	*node5;

	node0 = ft_simple_lst_create(ft_itoa_base(0, 10));
	node1 = ft_simple_lst_create(ft_itoa_base(8, 10));
	node2 = ft_simple_lst_create(ft_itoa_base(2, 10));
	node3 = ft_simple_lst_create(ft_itoa_base(4, 10));
	node4 = ft_simple_lst_create(ft_itoa_base(14, 10));
	node5 = ft_simple_lst_create(ft_itoa_base(29, 10));
	ft_simple_lst_sort_insert(&node0, node1, simple_is_okay);
	ft_simple_lst_sort_insert(&node0, node2, simple_is_okay);
	ft_simple_lst_sort_insert(&node0, node3, simple_is_okay);
	ft_simple_lst_sort_insert(&node0, node4, simple_is_okay);
	ft_simple_lst_sort_insert(&node0, node5, simple_is_okay);
	ft_simple_lst_foreach(node0, NULL, print_simple);
	ft_printf("%s\n", ft_simple_lst_return_if(node0, return_is_okay)->data);
}

int	main(void)
{
	t_lst_head	*head;
	int		i = 0;

	head = ft_create_head(ft_double_lst_create(ft_itoa_base(i, 10)));
	/* double_add(&head); */
	/* double_pushback(&head); */
	/* double_sort_insert(&head); */
	double_del_one_and_remove(&head);
	/* simple_add(); */
	/* simple_pushback(); */
	/* simple_del_one_and_remove(); */
	/* simple_sort_insert(); */
	/* double_del_one_2(&head); */
	/* simple_del_one_and_remove2(); */
	return (0);
}

