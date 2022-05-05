/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:52:26 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 01:23:16 by younglee         ###   ########seoul.kr  */
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

void	free_all(t_pipex *pipex)
{
	free_split_arr(pipex->cmd1_argv);
	free_split_arr(pipex->cmd2_argv);
	free_split_arr(pipex->cmd_path);
	close_all_fd(pipex);
}
