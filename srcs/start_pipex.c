/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:46 by younglee          #+#    #+#             */
/*   Updated: 2022/05/05 19:12:56 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"

void	start_pipex(t_pipex *pipex)
{
	pid_t	pid;

	pipex->input_fd = open(pipex->input_path, O_RDONLY);
	exit_with_clib_error(pipex->input_path, pipex);
	pipe(pipex->pipe_fd);
	exit_with_clib_error("pipe", pipex);
	pid = fork();
	exit_with_clib_error("fork", pipex);
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		exit_with_clib_error("wait", pipex);
	}
	else if (pid == 0)
	{
		dup2(pipex->input_fd, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		execv(pipex->cmd1_argv[0], pipex->cmd1_argv);
		free_all(pipex);
		exit(0);
	}
}
