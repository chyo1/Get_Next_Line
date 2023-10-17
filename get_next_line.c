/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/17 20:32:58 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	alloc(t_list **node, char *buff, size_t buf_len)
{
	char	*str;
	size_t	idx;

	if ((*node)->size < (*node)->fill + buf_len)
	{
		(*node)->size *= 2;
		str = (char *)malloc((*node)->size);
		if (str == NULL)
			return (-1);
		idx = -1;
		while (++idx < (*node)->fill)
			str[idx] = ((*node)->content)[idx];
		(*node)->content = str;
		free((*node)->content);
	}
	idx = -1;
	while (++idx < buf_len)
		str[(*node)->fill + idx] = buff[idx];
	(*node)->fill += buf_len;
	return (1);
}

char	*ft_free(t_list *ans)
{
	lstfree(&ans);
	return (0);
}

ssize_t	find_endl(t_list *node)
{
	size_t	idx;
	size_t	i;

	idx = 0;
	i = 0;
	while (idx < node->fill)
	{
		if ((node->content)[idx] == '\n')
			break ;
	}
	node->content = (char *)malloc(sizeof(char) * idx);
	if (!node->content)
		return (-1);
	i = -1;
	while (++i <= idx)
		(node->ans)[idx] = (node->content)[idx];
	i = 1;
	while (idx + i < node->fill)
	{
		(node->content)[i] = (node->content)[idx + i];
		i++;
	}
	node->fill = (node->fill) - idx - 1;
	return (0);
}
// 012345\n6789
char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	static t_list	*ans;
	t_list			*node;
	ssize_t			val_read;

	if (fd < 0 || fd == 2 || read(fd, NULL, 0) < 0)
		return (0);
	node = find_or_make_lst(ans, fd);
	if (!node)
		return (0);
	while (1)
	{
		val_read = read(fd, buff, BUFFER_SIZE);
		if (val_read < 0)
			return (ft_free(ans));
		if (alloc(&node, buff, BUFFER_SIZE) < 0)
			return (ft_free(ans));
		if (0 < find_endl(node))
			return (node->ans);
	}
	if (alloc(&node, buff, BUFFER_SIZE) < 0)
		return (ft_free(ans));
	return (node->ans);
}
