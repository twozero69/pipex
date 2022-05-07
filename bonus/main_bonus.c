/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:39:07 by younglee          #+#    #+#             */
/*   Updated: 2022/05/08 03:06:58 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		cmd_no;

	init_pipex(argc, argv, envp, &pipex);
	if (pipex.here_doc_flag)
	{
		here_doc_pipex(&pipex);
		cmd_no = 0;
	}
	else
	{
		start_pipex(envp, &pipex);
		cmd_no = 1;
	}
	while (cmd_no < pipex.cmd_count - 1)
	{
		middle_pipex(cmd_no, envp, &pipex);
		cmd_no++;
	}
	end_pipex(envp, &pipex);
	wait_all_child(&pipex);
	free_all(&pipex);
	return (0);
}
