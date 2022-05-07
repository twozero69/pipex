/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:07:55 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 18:13:25 by younglee         ###   ########seoul.kr  */
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
		close_one_fd(&cmd->pipe_fd[0], "close_fd.c: cmd pipe_fd[0]", pipex);
		close_one_fd(&cmd->pipe_fd[1], "close_fd.c: cmd pipe_fd[1]", pipex);
		idx++;
	}
	close_one_fd(&pipex->here_doc.pipe_fd[0], \
	"close_fd.c: here_doc pipe_fd[0]", pipex);
	close_one_fd(&pipex->here_doc.pipe_fd[1], \
	"close_fd.c: here_doc pipe_fd[1]", pipex);
}

void	close_all_fd(t_pipex *pipex)
{
	close_one_fd(&pipex->input_fd, "close_fd.c: input_fd", pipex);
	close_one_fd(&pipex->output_fd, "close_fd.c: output_fd", pipex);
	close_all_pipe_fd(pipex);
}
