/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/25 19:55:20 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_or_make_lst(t_list *root, int fd, size_t buf_size)
{
	t_list	*node;

	node = root;
	while (root)
	{
		if (root->fd == fd)
			return (root);
		root = root->next;
	}
	node = (t_list *)malloc(1 * sizeof(t_list));
	if (!node)
		return (0);
	if (!init_node(node, fd, buf_size))
	{
		free(node);
		return (0);
	}
	ft_lstadd_back(&root, node);
	return (node);
}

int	init_node(t_list *node, int fd, size_t buf_size)
{
	char	*str1;

	str1 = (char *)malloc(sizeof(buf_size));
	if (!str1)
		return (0);
	node->str = str1;
	node->fd = fd;
	node->len = 0;
	node->size = buf_size;
	node->loc = 0;
	node->next = 0;
	return (1);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

char	*list_free_and_connect(t_list **lst, int fd)
{
	t_list	*bef;
	t_list	*now;

	bef = *lst;
	now = *lst;

	while (now->fd != fd)
	{
		bef = now;
		now = now->next;
	}
	if (bef != now)
		bef->next = now->next;
	free(now->str);
	now->str = 0;
	free(now);
	now = 0;
	return (0);
}
