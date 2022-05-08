/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:07:55 by younglee          #+#    #+#             */
/*   Updated: 2022/05/09 03:05:30 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "pipex.h"

void	close_one_fd(int *fd)
{
	if (*fd == -1)
		return ;
	errno = 0;
	close(*fd);
	*fd = -1;
}

static void	close_all_pipe_fd(t_pipex *pipex)
{
	int		idx;
	t_cmd	*cmd;

	idx = 0;
	while (idx < pipex->cmd_count)
	{
		cmd = &pipex->cmd_array[idx];
		close_one_fd(&cmd->pipe_fd[0]);
		close_one_fd(&cmd->pipe_fd[1]);
		idx++;
	}
}

void	close_all_fd(t_pipex *pipex)
{
	close_one_fd(&pipex->input_fd);
	close_one_fd(&pipex->output_fd);
	close_all_pipe_fd(pipex);
}
