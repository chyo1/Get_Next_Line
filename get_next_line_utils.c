/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/23 18:10:48 by hyowchoi         ###   ########.fr       */
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
	char	*str2;

	str1 = (char *)malloc(sizeof(buf_size));
	if (!str1)
		return (0);
	str2 = (char *)malloc(sizeof(buf_size));
	if (!str2)
	{
		free(str1);
		return (0);
	}
	node->content = str1;
	node->ans = str2;
	node->fd = fd;
	node->fill = 0;
	node->flag = 0;
	node->con_size = buf_size;
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

int	list_free_and_connect(t_list **lst, int fd)
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
	free(now->content);
	free(now->ans);
	free(now);
	return (0);
}
