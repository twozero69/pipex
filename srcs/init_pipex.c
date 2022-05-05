/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:22:03 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 07:35:16 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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
			print_clib_error("cmd_path split", pipex);
			return ;
		}
		idx++;
	}
	exit_with_custom_error(3, pipex);
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	errno = 0;
	ft_memset(pipex, 0, sizeof(t_pipex));
	pipex->input_fd = -1;
	pipex->output_fd = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	check_argc_argv(argc, argv, pipex);
	pipex->exec_path = argv[0];
	pipex->input_path = argv[1];
	pipex->cmd1_argv = ft_split(argv[2], ' ');
	print_clib_error("cmd1_argv", pipex);
	pipex->cmd2_argv = ft_split(argv[3], ' ');
	print_clib_error("cmd2_argv", pipex);
	pipex->output_path = argv[4];
	get_cmd_path(envp, pipex);
}
