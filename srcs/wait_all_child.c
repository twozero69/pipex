/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:50:20 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 20:44:24 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	print_error_child(char **cmd_argv)
{
	ft_putstr_fd("The child process end error:", 2);
	while (*cmd_argv != NULL)
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(*cmd_argv, 2);
		cmd_argv++;
	}
	ft_putchar_fd('\n', 2);
}

void	wait_all_child(t_pipex *pipex)
{
	waitpid(pipex->cmd1_pid, NULL, WNOHANG | WUNTRACED);
	waitpid(pipex->cmd2_pid, NULL, WNOHANG | WUNTRACED);
}
