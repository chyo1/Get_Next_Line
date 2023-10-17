/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/17 18:31:18 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

t_list	*find_or_make_lst(t_list *ans, int fd)
{
	t_list	*node;

	while (ans)
	{
		if (ans->fd == fd)
			return (ans);
		ans = ans->next;
	}
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = 0;
	node->fd = fd;
	node->fill = 0;
	node->size = 1;
	node->next = 0;
	ft_lstadd_back(&ans, node);
	return (node);
}

void	lstfree(t_list **lst)
{
	t_list	*node_next;
	t_list	*node_free;

	node_next = *lst;
	while (node_next)
	{
		node_free = node_next;
		node_next = node_next->next;
		free(node_free->content);
		free(node_free);
	}
	free(node_next->content);
	free(node_next);
}
