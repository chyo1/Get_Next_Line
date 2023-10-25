/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/25 19:37:50 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	make_root(t_list **root, size_t buf_size)
{
	if (*root)
		return (1);
	*root = (t_list *)malloc(sizeof(t_list));
	if (!root)
		return (0);
	(*root)->str = (char *)malloc(sizeof(char) * buf_size);
	if (!((*root)->str))
	{
		free(*root);
		*root = 0;
		return (0);
	}
	(*root)->len = 0;
	(*root)->size = buf_size;
	(*root)->loc = 0;
	return (1);
}

int	find_endl(t_list *root, ssize_t cnt, ssize_t buf_size)
{
	ssize_t	idx;

	idx = 0;
	while (idx < root->len)
	{
		if ((root->str)[idx] == '\n')
		{
			root->loc = idx + 1;
			return (1);
		}
		idx++;
	}
	if (cnt != buf_size)
	{
		root->loc = root->len;
		return (1);
	}
	root->loc = -1;
	return (0);
}

int	cpy_buff(t_list **node, char *buff, ssize_t cnt)
{
	char	*tmp;
	ssize_t	idx;

	idx = 0;
	if ((*node)->size < (*node)->len + cnt)
	{
		(*node)->size = (*node)->len + cnt;
		(*node)->size *= 2;
		tmp = (char *)malloc(sizeof(char) * (*node)->size);
		if (!tmp)
		{
			free((*node)->str);
			(*node)->str = 0;
			free(*node);
			*node = 0;
			return (0);
		}
		while (idx < (*node)->len)
		{
			tmp[idx] = (*node)->str[idx];
			idx++;
		}
		free((*node)->str);
		(*node)->str = tmp;
	}
	idx = 0;
	while (idx < cnt)
	{
		(*node)->str[(*node)->len + idx] = buff[idx]; //
		idx++;
	}
	(*node)->len += cnt;
	return (1);
}

// 0123\n567
char	*get_ans(t_list **node)
{
	char	*ans;
	char	*tmp;
	ssize_t	idx;

	ans = (char *)malloc(sizeof(char) * ((*node)->loc + 1));
	if (!ans)
	{
		free((*node)->str);
		(*node)->str = 0;
		free(*node);
		*node = 0;
		return (0);
	}
	idx = -1;
	while (++idx < (*node)->loc)
		ans[idx] = (*node)->str[idx];
	ans[idx] = '\0';
	tmp = (char *)malloc(sizeof(char) * ((*node)->len - (*node)->loc));
	(*node)->size = (*node)->len - (*node)->loc; // 
	if (!tmp)
	{
		free((*node)->str);
		(*node)->str = 0;
		free(*node);
		*node = 0;
		free(ans);
		return (0);
	}
	idx = -1;
	while ((++idx) + (*node)->loc < (*node)->len)
		tmp[idx] = (*node)->str[idx + (*node)->loc];
	free((*node)->str);
	(*node)->str = tmp;
	(*node)->len -= (*node)->loc;
	return (ans);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	static t_list	*root;
	ssize_t			cnt;

	if (fd < 0 || fd == 2 || !make_root(&root, BUFFER_SIZE))
		return (0);
	while (1)
	{
		cnt = read(fd, buff, BUFFER_SIZE);
		if (cnt < 0)
		{
			free(root->str);
			root->str = 0;
			free(root);
			root = 0;
			return (0);
		}
		else if (cnt == 0)
			break ;
		if (!cpy_buff(&root, buff, cnt))
			return (0);
		if (find_endl(root, cnt, BUFFER_SIZE))
			return (get_ans(&root));
	}
	if (!root->len)
	{
		free(root->str);
		root->str = 0;
		free(root);
		root = 0;
		return (0);
	}
	find_endl(root, cnt, BUFFER_SIZE);
	return (get_ans(&root));
}

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);

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