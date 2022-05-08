/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:22:03 by younglee          #+#    #+#             */
/*   Updated: 2022/05/09 03:05:01 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "pipex.h"
#include "libft.h"

static void	check_argc(int argc, t_pipex *pipex)
{
	if (argc != 5)
		exit_with_custom_error(1, pipex);
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
			return ;
		}
		idx++;
	}
	exit_with_custom_error(3, pipex);
}

static void	make_cmd_array(int argc, char **argv, t_pipex *pipex)
{
	int	idx;

	pipex->cmd_count = argc - 3;
	pipex->cmd_array = (t_cmd *)malloc(pipex->cmd_count * sizeof(t_cmd));
	idx = 0;
	while (idx < pipex->cmd_count)
	{
		pipex->cmd_array[idx].cmd_argv = ft_split(argv[idx], ' ');
		pipex->cmd_array[idx].pipe_fd[0] = -1;
		pipex->cmd_array[idx].pipe_fd[1] = -1;
		pipex->cmd_array[idx].pid = 0;
		idx++;
	}
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	errno = 0;
	ft_memset(pipex, 0, sizeof(t_pipex));
	pipex->input_fd = -1;
	pipex->output_fd = -1;
	check_argc(argc, pipex);
	pipex->exec_path = argv[0];
	pipex->input_path = argv[1];
	pipex->output_path = argv[argc - 1];
	make_cmd_array(argc, argv + 2, pipex);
	get_cmd_path(envp, pipex);
}
