/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:07:55 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 18:04:49 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "pipex.h"

void	close_one_fd(int *fd, char *msg, t_pipex *pipex)
{
	if (*fd == -1)
		return ;
	errno = 0;
	close(*fd);
	print_clib_error(msg, pipex);
	*fd = -1;
}

void	close_all_fd(t_pipex *pipex)
{
	close_one_fd(&pipex->input_fd, "close_all_fd: input_fd", pipex);
	close_one_fd(&pipex->output_fd, "close_all_fd: output_fd", pipex);
	close_one_fd(&pipex->pipe_fd[0], "close_all_fd: pipe_fd[0]", pipex);
	close_one_fd(&pipex->pipe_fd[1], "close_all_fd: pipe_fd[1]", pipex);
}
