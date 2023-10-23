/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/23 17:45:24 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	alloc(t_list *node, char *buff, size_t buf_len)
{
	char	*str;
	size_t	cnt;

	cnt = -1;
	if (node->con_size < node->fill + buf_len)
	{
		node->con_size *= 2;
		str = (char *)malloc(sizeof(char) * node->con_size);
		if (!str)
			return (0);
		while (++cnt < node->fill)
			str[cnt] = (node->content)[cnt];
		cnt = -1;
		while (++cnt < buf_len)
			str[node->fill + cnt] = buff[cnt];
		free(node->content);
		node->content = str;
	}
	else
	{
		while (++cnt < buf_len)
			(node->content)[node->fill + cnt] = buff[cnt];
	}
	node->fill += buf_len;
	return (1);
}

size_t	find_endl(t_list	*node)
{
	size_t	len;

	len = 0;
	while (len < node->fill)
	{
		if ((node->content)[len] == '\n')
		{
			node->flag = 1;
			return (len + 1);
		}
		len++;
	}
	return (node->fill);
}

char	*get_ans(t_list	*node)
{
	size_t	idx;
	char	*str;
	size_t	len;

	len = find_endl(node);
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (0);
	idx = -1;
	while (++idx < len)
		str[idx] = (node->content)[idx];
	free(node->ans);
	node->ans = str;
	idx = 0;
	while (len + idx < node->fill)
	{
		node->content[idx] = node->content[len + idx];
		idx++;
	}
	node->fill = (node->fill) - len;
	return (node->ans);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	ssize_t			len;
	static t_list	*root;
	t_list			*node;

	if (fd < 0 || fd == 2)
		return (0);
	node = find_or_make_lst(root, fd, BUFFER_SIZE);
	if (!node)
		return (0);
	while (1)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len <= 0)
			break ;
		if (!alloc(node, buff, len) || !get_ans(node))
			break ;
		if (len != BUFFER_SIZE || node->flag)
			return (node->ans);
	}
	list_free_and_connect(&root, fd);
	return (0);
}

// #include <fcntl.h>

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);

// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	return (0);
// }
