/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:17:36 by younglee          #+#    #+#             */
/*   Updated: 2022/05/09 00:48:07 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "pipex.h"

void	end_pipex(char **envp, t_pipex *pipex)
{
	t_cmd	*prev_cmd;
	t_cmd	*curr_cmd;

	prev_cmd = &pipex->cmd_array[pipex->cmd_count - 2];
	curr_cmd = &pipex->cmd_array[pipex->cmd_count - 1];
	curr_cmd->pid = fork();
	if (curr_cmd->pid == 0)
	{
		errno = 0;
		if (pipex->here_doc_flag)
			pipex->output_fd = open(pipex->output_path, HERE_DOC_OPEN, 0644);
		else
			pipex->output_fd = open(pipex->output_path, NORMAL_OPEN, 0644);
		exit_with_clib_error(pipex->output_path, pipex);
		check_cmd(&curr_cmd->cmd_argv[0], pipex);
		dup2(prev_cmd->pipe_fd[0], STDIN_FILENO);
		dup2(pipex->output_fd, STDOUT_FILENO);
		close_one_fd(&curr_cmd->pipe_fd[0]);
		execve(curr_cmd->cmd_argv[0], curr_cmd->cmd_argv, envp);
		free_all(pipex);
		exit(0);
	}
	close_one_fd(&prev_cmd->pipe_fd[0]);
	close_one_fd(&curr_cmd->pipe_fd[0]);
	close_one_fd(&curr_cmd->pipe_fd[1]);
}
