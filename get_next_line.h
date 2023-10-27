/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:49 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/27 13:08:48 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str;
	int				fd;
	ssize_t			len;
	ssize_t			size;
	ssize_t			loc;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		cpy_buff(t_list *node, char *buff, ssize_t cnt);
int		find_endl(t_list *node, ssize_t cnt);
char	*get_ans(t_list **root, t_list *node);

t_list	*find_or_make_lst(t_list **root, int fd);
int		init_node(t_list *node, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
char	*list_free_and_connect(t_list **lst, int fd);

#endif
