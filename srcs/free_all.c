/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:52:26 by younglee          #+#    #+#             */
/*   Updated: 2022/05/08 04:10:14 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

void	free_split_arr(char **split_arr)
{
	int	idx;

	if (split_arr == NULL)
		return ;
	idx = 0;
	while (split_arr[idx] != NULL)
	{
		free(split_arr[idx]);
		idx++;
	}
	free(split_arr);
}

static void	free_cmd_array(t_pipex *pipex)
{
	int		idx;
	t_cmd	*cmd;

	if (pipex->cmd_array == NULL)
		return ;
	idx = 0;
	while (idx < pipex->cmd_count)
	{
		cmd = &pipex->cmd_array[idx];
		free_split_arr(cmd->cmd_argv);
		idx++;
	}
	free(pipex->cmd_array);
	pipex->cmd_array = NULL;
}

void	free_all(t_pipex *pipex)
{
	close_all_fd(pipex);
	free_cmd_array(pipex);
	free_split_arr(pipex->cmd_path);
}
