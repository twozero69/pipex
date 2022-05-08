/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:26:56 by younglee          #+#    #+#             */
/*   Updated: 2022/05/09 00:47:38 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "pipex.h"

void	middle_pipex(int cmd_no, char **envp, t_pipex *pipex)
{
	t_cmd	*prev_cmd;
	t_cmd	*curr_cmd;

	if (pipex->here_doc_flag && cmd_no == 0)
		prev_cmd = &pipex->here_doc;
	else
		prev_cmd = &pipex->cmd_array[cmd_no - 1];
	curr_cmd = &pipex->cmd_array[cmd_no];
	pipe(curr_cmd->pipe_fd);
	curr_cmd->pid = fork();
	if (curr_cmd->pid == 0)
	{
		errno = 0;
		check_cmd(&curr_cmd->cmd_argv[0], pipex);
		dup2(prev_cmd->pipe_fd[0], STDIN_FILENO);
		dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO);
		close_one_fd(&curr_cmd->pipe_fd[0]);
		execve(curr_cmd->cmd_argv[0], curr_cmd->cmd_argv, envp);
		free_all(pipex);
		exit(0);
	}
	close_one_fd(&prev_cmd->pipe_fd[0]);
	close_one_fd(&curr_cmd->pipe_fd[1]);
}
