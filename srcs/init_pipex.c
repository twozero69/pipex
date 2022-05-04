/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:22:03 by younglee          #+#    #+#             */
/*   Updated: 2022/05/04 23:49:44 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "pipex.h"
#include "libft.h"

static void	check_argc(int argc, t_pipex *pipex)
{
	if (argc == 4)
		return ;
	exit_with_custom_error(1, pipex);
}

static void	check_argv_one(char *path, int mode, t_pipex *pipex)
{
	access(path, mode);
	exit_with_clib(pipex);
}

static void	check_argv(t_pipex *pipex)
{
	check_argv_one(pipex->inputpath, R_OK, pipex);
	check_argv_one(pipex->outputpath, W_OK, pipex);
	check_argv_one(pipex->cmd1, X_OK, pipex);
	check_argv_one(pipex->cmd2, X_OK, pipex);
}

void	init_pipex(int argc, char **argv, t_pipex *pipex)
{
	errno = 0;
	ft_memset(pipex, 0, sizeof(t_pipex));
	check_argc(argc, pipex);
	pipex->execpath = argv[0];
	pipex->inputpath = argv[1];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->outputpath = argv[4];
	check_argv(pipex);
}
