/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:39:07 by younglee          #+#    #+#             */
/*   Updated: 2022/05/05 19:05:20 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipex(argc, argv, envp, &pipex);
	start_pipex(&pipex);
	end_pipex(&pipex);
	free_all(&pipex);
	return (0);
}
