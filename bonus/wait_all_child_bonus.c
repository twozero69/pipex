/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_child_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:50:20 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 05:25:11 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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
			waitpid(pid, NULL, WNOHANG | WUNTRACED);
			pipex->cmd_array[idx].pid = -1;
		}
		idx++;
	}
}
