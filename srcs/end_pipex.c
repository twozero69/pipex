/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:36 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 07:40:35 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"

void	end_pipex(char **envp, t_pipex *pipex)
{
	pipex->output_fd = open(pipex->output_path, O_WRONLY | O_CREAT | O_TRUNC, \
	0664);
	exit_with_clib_error(pipex->output_path, pipex);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	print_clib_error("end_pipex.c: dup2 pipe_fd[0]", pipex);
	dup2(pipex->output_fd, STDOUT_FILENO);
	print_clib_error("end_pipex.c: dup2 output_fd", pipex);
	close_one_fd(&pipex->pipe_fd[1], "end_pipex.c: pipe_fd[1]", pipex);
	check_cmd_path(&pipex->cmd2_argv[0], pipex);
	execve(pipex->cmd2_argv[0], pipex->cmd2_argv, envp);
	print_clib_error("end_pipex.c: execve", pipex);
}
