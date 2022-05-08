/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:52:53 by younglee          #+#    #+#             */
/*   Updated: 2022/05/08 19:13:37 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "pipex_bonus.h"
#include "libft.h"

void	exit_with_custom_error(int my_errno, t_pipex *pipex)
{
	ft_putstr_fd("Custom error occur: ", 2);
	if (my_errno == 1)
		ft_putstr_fd("You must input at least four arguments.\n", 2);
	else if (my_errno == 2)
		ft_putstr_fd("You need at least five inputs to use heredoc.\n", 2);
	else if (my_errno == 3)
		ft_putstr_fd("Empty string argument input.\n", 2);
	else if (my_errno == 4)
		ft_putstr_fd("PATH is missing from environment.\n", 2);
	else
		ft_putstr_fd("Invalid error no.\n", 2);
	free_all(pipex);
	exit(0);
}

static void	print_clib_error(char *msg, t_pipex *pipex)
{
	if (msg == NULL)
		perror(pipex->exec_path);
	else
	{
		ft_putstr_fd(pipex->exec_path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
	}
	errno = 0;
}

void	exit_with_clib_error(char *msg, t_pipex *pipex)
{
	if (errno == 0)
		return ;
	print_clib_error(msg, pipex);
	free_all(pipex);
	exit(0);
}

void	exit_with_cmd_error(char *cmd_name, t_pipex *pipex)
{
	ft_putstr_fd(pipex->exec_path, 2);
	ft_putstr_fd(": command not found: ", 2);
	ft_putendl_fd(cmd_name, 2);
	free_all(pipex);
	exit(0);
}
