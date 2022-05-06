/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:20:30 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 01:29:06 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>

# define HASH_SIZE 50
# define DATA_SIZE 100
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

typedef struct s_line
{
	char			*data;
	size_t			data_size;
	size_t			data_back;
	int				fd;
	struct s_line	*next;
	struct s_line	*prev;
}	t_line;

char	*get_next_line(int fd);

t_line	*make_new_line(t_line *prev, int fd);
int		my_strncpy(t_line *list, char *buffer, ssize_t copy_count);
int		refresh_data(t_line *list, char *buf, ssize_t n_l_idx, ssize_t rd_cnt);
void	clear_line(t_line *list);

#endif
