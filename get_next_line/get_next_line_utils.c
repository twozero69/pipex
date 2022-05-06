/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:20:46 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 01:28:22 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

t_line	*make_new_line(t_line *prev, int fd)
{
	t_line	*new_line;

	new_line = (t_line *)malloc(sizeof(t_line));
	if (new_line == 0)
		return (0);
	new_line->data = (char *)malloc(DATA_SIZE * sizeof(char));
	if (new_line->data == 0)
	{
		free(new_line);
		return (0);
	}
	new_line->data[0] = '\0';
	new_line->data_size = DATA_SIZE;
	new_line->data_back = 0;
	new_line->fd = fd;
	new_line->next = 0;
	new_line->prev = prev;
	return (new_line);
}

static int	extend_data(t_line *list, ssize_t copy_count)
{
	char	*new_data;
	size_t	new_size;
	size_t	idx;

	if (list->data_size >= list->data_back + copy_count + 1)
		return (1);
	if (copy_count > DATA_SIZE)
		new_size = list->data_back + copy_count + 1;
	else
		new_size = list->data_size * 2;
	new_data = (char *)malloc(new_size * sizeof(char));
	if (new_data == 0)
		return (0);
	idx = 0;
	while (idx < list->data_back)
	{
		new_data[idx] = list->data[idx];
		idx++;
	}
	new_data[list->data_back] = '\0';
	free(list->data);
	list->data = new_data;
	list->data_size = new_size;
	return (1);
}

int	my_strncpy(t_line *list, char *buffer, ssize_t copy_count)
{
	ssize_t	idx;

	if (extend_data(list, copy_count) == 0)
		return (0);
	idx = 0;
	while (idx < copy_count)
	{
		list->data[list->data_back] = buffer[idx];
		list->data_back++;
		idx++;
	}
	list->data[list->data_back] = '\0';
	return (1);
}

int	refresh_data(t_line *list, char *data, ssize_t n_l_idx, ssize_t rd_cnt)
{
	list->data = (char *)malloc(DATA_SIZE * sizeof(char));
	if (list->data == 0)
		return (0);
	list->data[0] = '\0';
	list->data_size = DATA_SIZE;
	list->data_back = 0;
	if (n_l_idx == -1)
		return (1);
	if (my_strncpy(list, &data[n_l_idx + 1], rd_cnt - n_l_idx - 1) == 0)
	{
		free(list->data);
		list->data = data;
		return (0);
	}
	return (1);
}

void	clear_line(t_line *list)
{
	t_line	*prev;
	t_line	*next;

	prev = list->prev;
	next = list->next;
	prev->next = next;
	if (next != 0)
		next->prev = prev;
	free(list->data);
	free(list);
}
