/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:07:55 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 08:14:00 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "pipex_bonus.h"

void	close_one_fd(int *fd, char *msg, t_pipex *pipex)
{
	if (*fd == -1)
		return ;
	errno = 0;
	close(*fd);
	print_clib_error(msg, pipex);
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
		close_one_fd(&cmd->pipe_fd[0], "close_fd.c: line 42", pipex);
		close_one_fd(&cmd->pipe_fd[1], "close_fd.c: line 43", pipex);
		idx++;
	}
}

void	close_all_fd(t_pipex *pipex)
{
	close_one_fd(&pipex->input_fd, "close_fd.c: input_fd", pipex);
	close_one_fd(&pipex->output_fd, "close_fd.c: output_fd", pipex);
	close_all_pipe_fd(pipex);
}
