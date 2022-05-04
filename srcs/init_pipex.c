/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:22:03 by younglee          #+#    #+#             */
/*   Updated: 2022/05/05 05:51:06 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "pipex.h"
#include "libft.h"

static void	check_argc_argv(int argc, char **argv, t_pipex *pipex)
{
	if (argc == 5)
		return ;
	exit_with_custom_error(1, pipex);
	while (*argv != NULL)
	{
		if (**argv == '\0')
			exit_with_custom_error(2, pipex);
		argv++;
	}
}

static void	get_cmd_path(char **envp, t_pipex *pipex)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		if (ft_strncmp(envp[idx], "PATH=", 5) == 0)
		{
			pipex->cmd_path = ft_split(envp[idx] + 5, ':');
			exit_with_clib_error(NULL, pipex);
			return ;
		}
		idx++;
	}
	exit_with_custom_error(3, pipex);
}

static void	get_cmd_exec_path(char **cmd_name, t_pipex *pipex)
{
	int		idx;
	char	*path;
	char	*term;

	idx = 0;
	while (pipex->cmd_path[idx] != NULL)
	{
		errno = 0;
		term = ft_strjoin(pipex->cmd_path[idx], "/");
		path = ft_strjoin(term, *cmd_name);
		free(term);
		exit_with_clib_error(NULL, pipex);
		if (access(path, X_OK) == 0)
		{
			free(*cmd_name);
			*cmd_name = path;
			return ;
		}
		free(path);
		idx++;
	}
	errno = 0;
	access(*cmd_name, X_OK);
	exit_with_clib_error(*cmd_name, pipex);
}

static void	check_access(t_pipex *pipex)
{
	access(pipex->input_path, R_OK);
	exit_with_clib_error(pipex->input_path, pipex);
	access(pipex->output_path, W_OK);
	exit_with_clib_error(pipex->output_path, pipex);
	get_cmd_exec_path(&pipex->cmd1_argv[0], pipex);
	get_cmd_exec_path(&pipex->cmd2_argv[0], pipex);
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	errno = 0;
	ft_memset(pipex, 0, sizeof(t_pipex));
	check_argc_argv(argc, argv, pipex);
	pipex->exec_path = argv[0];
	pipex->input_path = argv[1];
	pipex->cmd1_argv = ft_split(argv[2], ' ');
	exit_with_clib_error(NULL, pipex);
	pipex->cmd2_argv = ft_split(argv[3], ' ');
	exit_with_clib_error(NULL, pipex);
	pipex->output_path = argv[4];
	get_cmd_path(envp, pipex);
	check_access(pipex);
}
