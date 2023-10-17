/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/17 14:30:26 by hyowchoi         ###   ########.fr       */
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
	p = ft_lstlast(*lst);
	p->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node_next;
	t_list	*node_free;

	node_next = *lst;
	while (node_next)
	{
		node_free = node_next;
		node_next = node_next->next;
		ft_lstdelone(node_free, del);
	}
	*lst = 0;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*root;

	root = (t_list *)malloc(sizeof(t_list));
	if (!root)
		return (0);
	root->content = content;
	root->next = 0;
	return (root);
}
