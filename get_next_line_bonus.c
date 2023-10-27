/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/27 13:35:09 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_endl(t_list *node, ssize_t cnt)
{
	ssize_t	idx;

	idx = 0;
	while (idx < node->len)
	{
		if ((node->str)[idx] == '\n')
		{
			node->loc = idx + 1;
			return (1);
		}
		idx++;
	}
	if (cnt != BUFFER_SIZE)
	{
		node->loc = node->len;
		return (1);
	}
	node->loc = -1;
	return (0);
}

int	cpy_buff(t_list *node, char *buff, ssize_t cnt)
{
	char	*tmp;
	ssize_t	idx;

	idx = 0;
	if (node->size < node->len + cnt)
	{
		node->size = 2 * (node->len + cnt);
		tmp = (char *)malloc(sizeof(char) * node->size);
		if (!tmp)
			return (0);
		while (idx < node->len)
		{
			tmp[idx] = node->str[idx];
			idx++;
		}
		free(node->str);
		node->str = tmp;
	}
	idx = -1;
	while (++idx < cnt)
		(node->str)[node->len + idx] = buff[idx];
	node->len += cnt;
	return (1);
}

char	*get_ans(t_list **root, t_list *node)
{
	char	*ans;
	char	*tmp;
	ssize_t	idx;

	ans = (char *)malloc(sizeof(char) * (node->loc + 1));
	if (!ans)
		return (list_free_and_connect(root, node->fd));
	idx = -1;
	while (++idx < node->loc)
		ans[idx] = node->str[idx];
	ans[idx] = '\0';
	tmp = (char *)malloc(sizeof(char) * (node->len - node->loc));
	if (!tmp)
	{
		free(ans);
		return (list_free_and_connect(root, node->fd));
	}
	idx = -1;
	while ((++idx) + node->loc < node->len)
		tmp[idx] = node->str[idx + node->loc];
	free(node->str);
	node->str = tmp;
	node->len -= node->loc;
	node->size = node->len - node->loc;
	return (ans);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	static t_list	*root;
	t_list			*node;
	ssize_t			cnt;

	if (fd < 0 || fd == 2)
		return (0);
	node = find_or_make_lst(&root, fd);
	if (!node)
		return (0);
	while (1)
	{
		cnt = read(fd, buff, BUFFER_SIZE);
		if (cnt <= 0)
			break ;
		if (!cpy_buff(node, buff, cnt))
			return (list_free_and_connect(&root, fd));
		if (find_endl(node, cnt))
			return (get_ans(&root, node));
	}
	if (cnt < 0 || node->len == 0)
		return (list_free_and_connect(&root, fd));
	find_endl(node, cnt);
	return (get_ans(&root, node));
}
