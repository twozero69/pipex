/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:52:26 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 08:18:41 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex_bonus.h"

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
		print_clib_error("free_all.c: free cmd_argv", pipex);
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
