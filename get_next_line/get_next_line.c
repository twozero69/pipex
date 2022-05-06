/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:20:35 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 01:28:28 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int	check_new_line(char *str, size_t length, ssize_t *new_line_idx)
{
	size_t	idx;

	idx = 0;
	while (idx < length)
	{
		if (str[idx] == '\n')
		{
			*new_line_idx = idx;
			return (1);
		}
		idx++;
	}
	return (0);
}

static t_line	*get_line_from_head(t_line *head, int fd)
{
	t_line	*list;
	t_line	*new_line;

	list = head;
	while (list->next != 0)
	{
		if (list != head && list->fd == fd)
			return (list);
		list = list->next;
	}
	if (list != head && list->fd == fd)
		return (list);
	new_line = make_new_line(list, fd);
	if (new_line == 0)
		return (0);
	list->next = new_line;
	return (new_line);
}

static char	*new_line_routine(t_line *list, ssize_t new_line_idx)
{
	char	*result;

	result = list->data;
	if (refresh_data(list, result, new_line_idx, list->data_back) == 0)
		return (0);
	result[new_line_idx + 1] = '\0';
	return (result);
}

static char	*read_routine(t_line *list, char *buffer)
{
	ssize_t		read_count;
	ssize_t		new_line_idx;
	char		*result;

	new_line_idx = -1;
	while (1)
	{
		read_count = read(list->fd, buffer, BUFFER_SIZE);
		if (read_count < 0 || (read_count == 0 && list->data_back == 0))
		{
			clear_line(list);
			return (0);
		}
		if (read_count == 0 && list->data_back != 0)
			break ;
		if (my_strncpy(list, buffer, read_count) == 0)
			return (0);
		if (check_new_line(list->data, list->data_back, &new_line_idx))
			return (new_line_routine(list, new_line_idx));
	}
	result = list->data;
	if (refresh_data(list, buffer, new_line_idx, read_count) == 0)
		return (0);
	return (result);
}

char	*get_next_line(int fd)
{
	static t_line	head_arr[HASH_SIZE];
	t_line			*list;
	ssize_t			new_line_idx;
	char			*buffer;
	char			*result;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	list = get_line_from_head(&head_arr[fd % HASH_SIZE], fd);
	if (list == 0)
		return (0);
	if (check_new_line(list->data, list->data_back, &new_line_idx))
		return (new_line_routine(list, new_line_idx));
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (buffer == 0)
		return (0);
	result = read_routine(list, buffer);
	free(buffer);
	return (result);
}
