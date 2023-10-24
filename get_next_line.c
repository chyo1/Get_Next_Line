/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/24 19:31:56 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_realloc(t_list *root)
{
	char	*tmp;
	ssize_t	idx;

	idx = 0;
	root->con_size *= 2;
	tmp = (char *)malloc(sizeof(char) * (root->con_size));
	if (!tmp)
		return (0);
	while (idx < root->fill)
	{
		tmp[idx] = (root->content)[idx];
		idx++;
	}
	if (root->content)
		free(root->content);
	root->content = tmp;
	return (1);
}

size_t	ft_strcat(t_list *node, char *buff, size_t cnt)
{
	size_t	idx;
	ssize_t	loc;

	loc = -1;
	idx = 0;
	while (idx < cnt)
	{
		(node->content)[node->fill + idx] = buff[idx];
		if ((node->content)[node->fill + idx] == '\n' && loc == -1)
			loc = node->fill + idx;
		idx++;
	}
	node->fill += cnt;
	return (loc);
}

void	find_endl(t_list *node)
{
	ssize_t	idx;

	idx = 0;
	node->loc = -1;
	while (idx < node->fill)
	{
		if ((node->content)[idx] == '\n' || (node->content)[idx] == EOF)
		{
			node->loc = idx;
			return ;
		}
		idx++;
	}
}

char	*strcut_n_cpy(t_list *node, char **res)
{
	char	*tmp;
	ssize_t	idx;

	if (node->loc == -1)
		node->loc = node->fill;
	tmp = (char *)malloc(sizeof(char) * (node->loc + 1));
	if (!tmp)
		return (0);
	idx = -1;
	while (++idx <= node->loc)
		tmp[idx] = (node->content)[idx];
	*res = tmp;
	tmp = (char *)malloc(sizeof(char) * (node->fill - node->loc));
	if (!tmp)
		return (0);
	idx = 1;
	while (idx + node->loc < node->fill)
	{
		tmp[idx - 1] = (node->content)[node->loc + idx];
		idx++;
	}
	free(node->content);
	node->content = tmp;
	return (*res);
}

//0123\n56789

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	static t_list	*root;
	char			*res;
	ssize_t			cnt;

	if (fd < 0 || fd == 2)
		return (0);
	if (!root)
	{
		root = (t_list *)malloc(sizeof(t_list));
		if (!root)
			return (0);
		root->con_size = BUFFER_SIZE;
		root->fill = 0;
		root->content = 0;
		if (!ft_realloc(root))
		{
			free(root);
			return (0);
		}
	}
	while (1)
	{
		cnt = read(fd, buff, BUFFER_SIZE);
		if (cnt == -1 && root != 0)
		{
			free(root->content);
			free(root);
			return (0);
		}
		if (root->con_size < root->fill + cnt)
		{
			if (!ft_realloc(root))
			{
				free(root->content);
				free(root);
				return (0);
			}
		}
		ft_strcat(root, buff, cnt);
		find_endl(root);
		if (root->loc >= 0)
			break ;
	}
	if (!strcut_n_cpy(root, &res))
	{
		free(root);
		return (0);
	}
	return (res);
}

// #include <fcntl.h>

// int main()
// {
// 	//int fd = open("text.txt", O_RDONLY);

//  	printf("%s", get_next_line(1234252435));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	return (0);
// }
