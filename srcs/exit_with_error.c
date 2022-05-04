/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:52:53 by younglee          #+#    #+#             */
/*   Updated: 2022/05/04 23:36:26 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "pipex.h"
#include "libft.h"

void	exit_with_custom_error(int my_errno, t_pipex *pipex)
{
	ft_putstr_fd("Custom error occur: ", 2);
	if (my_errno == 1)
		ft_putstr_fd("You must input four arguments.\n", 2);
	else if (my_errno == 2)
		ft_putstr_fd("", 2);
	else
		ft_putstr_fd("Invalid error no.\n", 2);
	free_all(pipex);
	exit(my_errno);
}

void	exit_with_clib_error(t_pipex *pipex)
{
	if (errno == 0)
		return ;
	perror(pipex->execpath);
	free_all(pipex);
	exit(errno);
}
