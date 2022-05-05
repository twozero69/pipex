/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:36 by younglee          #+#    #+#             */
/*   Updated: 2022/05/05 19:14:28 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"

void	end_pipex(t_pipex *pipex)
{
	pid_t	pid;

	pipex->output_fd = open(pipex->output_path, O_WRONLY);
	exit_with_clib_error(pipex->output_path, pipex);
	pid = fork();
	exit_with_clib_error("fork", pipex);
	if (pid > 0)
	{
		close_one_fd(&pipex->pipe_fd[1], pipex);
		waitpid(pid, NULL, 0);
		exit_with_clib_error("wait", pipex);
	}
	else if (pid == 0)
	{
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		dup2(pipex->output_fd, STDOUT_FILENO);
		close_one_fd(&pipex->pipe_fd[1], pipex);
		execv(pipex->cmd2_argv[0], pipex->cmd2_argv);
		free_all(pipex);
		exit(0);
	}
}
