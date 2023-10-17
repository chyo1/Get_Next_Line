/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:49 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/17 20:27:34 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	char			*ans;
	int				fd;
	size_t			fill;
	size_t			size;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
ssize_t	find_endl(t_list *node);
char	*ft_free(t_list *ans);
int		alloc(t_list **node, char *buff, size_t buf_len);

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*find_or_make_lst(t_list *ans, int fd);
void	lstfree(t_list **lst);
#endif
