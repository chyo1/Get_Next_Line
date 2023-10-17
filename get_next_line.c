/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/17 18:28:41 by hyowchoi         ###   ########.fr       */
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
		free(*node);
	}
	idx = -1;
	while (++idx < buf_len)
		str[(*node)->fill + idx] = buff[idx];
	(*node)->fill += buf_len;
	return (1);
}

char	*ft_free(t_list *ans, char *buff)
{
	lstfree(&ans);
	free(buff);
	return (0);
}

size_t	find_endl(char *str, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (str[idx] == '\n')
			return (idx + 1);
	}
	return (len);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static t_list	*ans;
	t_list			*node;
	ssize_t			val_read;
	size_t			str_len;

	buff = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buff)
		return (0);
	node = find_or_make_lst(ans, fd);
	if (!node)
		return (0);
	while (1)
	{
		val_read = read(fd, buff, BUFFER_SIZE);
		if (val_read < 0)
			return (ft_free(ans, buff));
		str_len = find_endl(buff, val_read);
		if (alloc(&node, buff, str_len) < 0)
			return (ft_free(ans, buff));
	}
	return (node->content);
}
