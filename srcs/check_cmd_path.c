/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 01:11:06 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 07:36:01 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "pipex.h"
#include "libft.h"

void	check_cmd_path(char **cmd_name, t_pipex *pipex)
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
		print_clib_error("check_access.c: strjoin", pipex);
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
