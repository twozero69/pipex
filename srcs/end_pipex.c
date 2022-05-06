/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:36 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 20:10:07 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "pipex.h"

void	end_pipex(char **envp, t_pipex *pipex)
{
	pipex->cmd2_pid = fork();
	print_clib_error("end_pipex.c: fork", pipex);
	if (pipex->cmd2_pid == 0)
	{
		pipex->output_fd = open(pipex->output_path, \
		O_WRONLY | O_CREAT | O_TRUNC, 0775);
		exit_with_clib_error(pipex->output_path, pipex);
		check_cmd_path(&pipex->cmd2_argv[0], pipex);
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		print_clib_error("end_pipex.c: dup2 pipe_fd[0]", pipex);
		dup2(pipex->output_fd, STDOUT_FILENO);
		print_clib_error("end_pipex.c: dup2 output_fd", pipex);
		execve(pipex->cmd2_argv[0], pipex->cmd2_argv, envp);
		print_clib_error("end_pipex.c: execve", pipex);
		free_all(pipex);
		exit(0);
	}
}
