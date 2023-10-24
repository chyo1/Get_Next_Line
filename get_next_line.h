/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:49 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/24 17:02:09 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> //

typedef struct s_list
{
	char			*content;
	int				fd;
	ssize_t			fill;
	ssize_t			con_size;
	ssize_t			loc;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*find_or_make_lst(t_list *root, int fd, size_t buf_size);
int		init_node(t_list *node, int fd, size_t buf_size);
int		list_free_and_connect(t_list **lst, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
#endif
