/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:50:20 by younglee          #+#    #+#             */
/*   Updated: 2022/05/09 03:05:43 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	wait_all_child(t_pipex *pipex)
{
	pid_t	pid;
	int		idx;

	idx = 0;
	while (idx < pipex->cmd_count)
	{
		pid = pipex->cmd_array[idx].pid;
		if (pid != 0)
		{
			waitpid(pid, NULL, 0);
			pipex->cmd_array[idx].pid = -1;
		}
		idx++;
	}
}
