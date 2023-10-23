/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:49 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/23 17:23:47 by hyowchoi         ###   ########.fr       */
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
	char			*ans;
	int				fd;
	size_t			fill;
	size_t			con_size;
	int				flag;
	struct s_list	*next;
}	t_list;

int		alloc(t_list *node, char *buff, size_t buf_len);
size_t	find_endl(t_list	*node);
char	*get_ans(t_list	*node);
char	*get_next_line(int fd);
t_list	*find_or_make_lst(t_list *root, int fd, size_t buf_size);
int		init_node(t_list *node, int fd, size_t buf_size);
int		list_free_and_connect(t_list **lst, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
#endif
