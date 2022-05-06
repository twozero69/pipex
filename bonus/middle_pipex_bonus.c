/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_pipex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:26:56 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 08:15:25 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "pipex_bonus.h"

void	middle_pipex(int cmd_no, char **envp, t_pipex *pipex)
{
	t_cmd	*prev_cmd;
	t_cmd	*curr_cmd;

	prev_cmd = &pipex->cmd_array[cmd_no - 1];
	curr_cmd = &pipex->cmd_array[cmd_no];
	pipe(curr_cmd->pipe_fd);
	print_clib_error("middle_pipex.c: pipe", pipex);
	curr_cmd->pid = fork();
	print_clib_error("middle_pipex.c: fork", pipex);
	if (curr_cmd->pid == 0)
	{
		check_cmd_path(&curr_cmd->cmd_argv[0], pipex);
		dup2(prev_cmd->pipe_fd[0], STDIN_FILENO);
		print_clib_error("middle_pipex.c: dup2 pipe_fd[0]", pipex);
		dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO);
		print_clib_error("middle_pipex.c: dup2 pipe_fd[1]", pipex);
		execve(curr_cmd->cmd_argv[0], curr_cmd->cmd_argv, envp);
		print_clib_error("middle_pipex.c: execve", pipex);
		free_all(pipex);
		exit(0);
	}
	close_one_fd(&prev_cmd->pipe_fd[0], "middle_pipex.c: close [0]", pipex);
	close_one_fd(&curr_cmd->pipe_fd[1], "middle_pipex.c: close [1]", pipex);
}
