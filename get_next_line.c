/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:19 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/27 13:47:15 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_endl(t_list *node, ssize_t cnt)
{
	ssize_t	idx;

	idx = 0;
	while (idx < node->len)
	{
		// 개행의 다음 idx 반환
		if ((node->str)[idx] == '\n')
		{
			node->loc = idx + 1;
			return (1);
		}
		idx++;
	}
	// 파일의 끝까지 읽었는데 개행이 나오지 않았을 때
	if (cnt != BUFFER_SIZE)
	{
		node->loc = node->len;
		return (1);
	}
	// 파일을 더 읽어야 할 때
	node->loc = -1;
	return (0);
}

int	cpy_buff(t_list *node, char *buff, ssize_t cnt)
{
	char	*tmp;
	ssize_t	idx;

	idx = 0;
	// 저장할 공간 < 현재 저장된 값 + 버퍼에 입력된 값
	if (node->size < node->len + cnt)
	{
		// 현재 들어온 값의 2배로 size 키우고 그만큼 할당
		node->size = 2 * (node->len + cnt);
		tmp = (char *)malloc(sizeof(char) * node->size);
		if (!tmp)
			return (0);
		// str에 저장한 값 복사
		while (idx < node->len)
		{
			tmp[idx] = node->str[idx];
			idx++;
		}
		// str 주소 옮겨주기
		free(node->str);
		node->str = tmp;
	}
	idx = -1;
	// buff에 담긴 값 str 뒤에 붙여 넣기
	while (++idx < cnt)
		(node->str)[node->len + idx] = buff[idx];
	// str에 담긴 문자열의 길이 늘리기
	node->len += cnt;
	return (1);
}

char	*get_ans(t_list **root, t_list *node)
{
	char	*ans;
	char	*tmp;
	ssize_t	idx;

	// 개행까지의 길이만큼 할당 + 문자열 마지막에 '\0'
	ans = (char *)malloc(sizeof(char) * (node->loc + 1));
	if (!ans)
		return (list_free_and_connect(root, node->fd));

	// str에서 반환할 값(ans) 복사
	idx = -1;
	while (++idx < node->loc)
		ans[idx] = node->str[idx];
	ans[idx] = '\0';

	// 개행문자 뒤부터 남는 문자열 길이만큼 할당 및 저장
	tmp = (char *)malloc(sizeof(char) * (node->len - node->loc));
	if (!tmp)
	{
		free(ans);
		return (list_free_and_connect(root, node->fd));
	}
	idx = -1;
	while ((++idx) + node->loc < node->len)
		tmp[idx] = node->str[idx + node->loc];
	free(node->str);
	node->str = tmp;

	// str의 길이와 size 변경
	node->len -= node->loc;
	node->size = node->len - node->loc;
	return (ans);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	static t_list	*root;
	t_list			*node;
	ssize_t			cnt;

	// fd 오류
	if (fd < 0 || fd == 2)
		return (0);

	// node 만들기
	node = find_or_make_lst(&root, fd);
	if (!node)
		return (0);
	while (1)
	{
		cnt = read(fd, buff, BUFFER_SIZE);

		// read error or 더 이상 읽을 값이 없을 때
		if (cnt <= 0)
			break ;
		
		// buff에 입력받은 값을 node에 저장
		if (!cpy_buff(node, buff, cnt))
			return (list_free_and_connect(&root, fd));

		// 개행문자의 위치 찾기
		if (find_endl(node, cnt))
			return (get_ans(&root, node));
	}
	// read error or 빈 파일 읽었을 때
	if (cnt < 0 || node->len == 0)
		return (list_free_and_connect(&root, fd));

	// 현재 읽은 값은 없지만 전에 읽고 남은 값이 있을 때
	find_endl(node, cnt);
	return (get_ans(&root, node));
}

// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int fd  = open("t.txt", O_RDONLY);
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// }