/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 01:37:00 by younglee          #+#    #+#             */
/*   Updated: 2022/05/08 04:10:17 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include "get_next_line.h"
#include "libft.h"

static int	get_new_line_idx(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

static	void	write_here_doc(t_pipex *pipex)
{
	char	*line;
	size_t	cmp_len;
	int		new_line_idx;

	cmp_len = ft_strlen(pipex->limiter) + 1;
	while (TRUE)
	{
		line = get_next_line(0);
		new_line_idx = get_new_line_idx(line);
		if (new_line_idx != -1)
			line[new_line_idx] = '\0';
		if (ft_strncmp(pipex->limiter, line, cmp_len) == 0)
			break ;
		if (new_line_idx != -1)
			line[new_line_idx] = '\n';
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
	free(line);
}

void	here_doc_pipex(t_pipex *pipex)
{
	t_cmd	*curr_cmd;

	curr_cmd = &pipex->here_doc;
	pipe(curr_cmd->pipe_fd);
	curr_cmd->pid = fork();
	if (curr_cmd->pid == 0)
	{
		dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO);
		close_one_fd(&curr_cmd->pipe_fd[0]);
		write_here_doc(pipex);
		free_all(pipex);
		exit(0);
	}
	else if (curr_cmd->pid > 0)
	{
		waitpid(curr_cmd->pid, NULL, 0);
		curr_cmd->pid = 0;
	}
	close_one_fd(&curr_cmd->pipe_fd[1]);
}
