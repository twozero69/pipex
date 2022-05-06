/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:50:20 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 05:00:12 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	wait_all_child(t_pipex *pipex)
{
	waitpid(pipex->cmd1_pid, NULL, WNOHANG | WUNTRACED);
	waitpid(pipex->cmd2_pid, NULL, WNOHANG | WUNTRACED);
}
