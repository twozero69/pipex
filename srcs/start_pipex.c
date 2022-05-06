/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:46 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 09:26:05 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"

void	start_pipex(char **envp, t_pipex *pipex)
{
	pid_t	pid;

	pipe(pipex->pipe_fd);
	print_clib_error("start_pipex.c: pipe", pipex);
	pid = fork();
	print_clib_error("start_pipex.c: fork", pipex);
	if (pid == 0)
	{
		pipex->input_fd = open(pipex->input_path, O_RDONLY);
		exit_with_clib_error(pipex->input_path, pipex);
		dup2(pipex->input_fd, STDIN_FILENO);
		print_clib_error("start_pipex.c: dup2 input_fd", pipex);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		print_clib_error("start_pipex.c: dup2 pipe_fd[1]", pipex);
		check_cmd_path(&pipex->cmd1_argv[0], pipex);
		execve(pipex->cmd1_argv[0], pipex->cmd1_argv, envp);
		print_clib_error("start_pipex.c: execve", pipex);
		free_all(pipex);
		exit(0);
	}
}
