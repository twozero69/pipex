/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:39:07 by younglee          #+#    #+#             */
/*   Updated: 2022/05/04 20:39:56 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"

int	main(int argc, char **argv)
{
	t_pipex	pipex;

	init_pipex(&pipex, argc, argv);
	head(&pipex);
	middle(&pipex);
	end(&pipex);
	free_all(&pipex);
	return (0);
}
