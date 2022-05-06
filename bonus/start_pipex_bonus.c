/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:46 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 08:15:17 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "pipex_bonus.h"

void	start_pipex(char **envp, t_pipex *pipex)
{
	t_cmd	*curr_cmd;

	curr_cmd = &pipex->cmd_array[0];
	pipe(curr_cmd->pipe_fd);
	print_clib_error("start_pipex.c: pipe", pipex);
	curr_cmd->pid = fork();
	print_clib_error("start_pipex.c: fork", pipex);
	if (curr_cmd->pid == 0)
	{
		pipex->input_fd = open(pipex->input_path, O_RDONLY);
		exit_with_clib_error(pipex->input_path, pipex);
		check_cmd_path(&curr_cmd->cmd_argv[0], pipex);
		dup2(pipex->input_fd, STDIN_FILENO);
		print_clib_error("start_pipex.c: dup2 input_fd", pipex);
		dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO);
		print_clib_error("start_pipex.c: dup2 pipe_fd[1]", pipex);
		execve(curr_cmd->cmd_argv[0], curr_cmd->cmd_argv, envp);
		print_clib_error("start_pipex.c: execve", pipex);
		free_all(pipex);
		exit(0);
	}
	close_one_fd(&curr_cmd->pipe_fd[1], "start_pipex.c: close [1]", pipex);
}
