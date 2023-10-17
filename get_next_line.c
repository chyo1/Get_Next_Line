/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/17 14:22:32 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*c;
	size_t	i;

	i = 0;
	if (size && count > (size_t)(-1) / size)
		return (NULL);
	c = (char *)malloc(count * size);
	if (c == NULL)
		return (NULL);
	while (i < count * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}

char	*ft_free(char *buff)
{
	free(buff);
	return (0);
}

unsigned int	find_endl(char *str, ssize_t len)
{
	ssize_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (str[idx] == '\n')
			return (idx + 1); // \n 문자 자리 포함
	}
	return (len);
}

char	*get_next_line(int fd)
{
	char	*buff;
	char	*ans;
	ssize_t	val_read;
	ssize_t	endl_loc;

	buff = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buff)
		return (0);
	while (1)
	{
		val_read = read(fd, buff, BUFFER_SIZE);
		if (val_read < 0)
			return (ft_free(buff));
		endl_loc = find_endl(buff, val_read);
	}
	return (buff);
}
