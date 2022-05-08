/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 01:11:06 by younglee          #+#    #+#             */
/*   Updated: 2022/05/09 02:29:58 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "pipex.h"
#include "libft.h"

static void	check_cmd_path(char **cmd_name, t_pipex *pipex)
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
		if (access(path, X_OK) == 0)
		{
			free(*cmd_name);
			*cmd_name = path;
			return ;
		}
		free(path);
		idx++;
	}
	exit_with_cmd_error(*cmd_name, pipex);
}

static void	check_cmd_wd(char *cmd_name, t_pipex *pipex)
{
	access(cmd_name, X_OK);
	exit_with_clib_error(cmd_name, pipex);
}

static int	get_slash_idx(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '/')
			return (idx);
		idx++;
	}
	return (-1);
}

void	check_cmd(char **cmd_name, t_pipex *pipex)
{
	if (*cmd_name == NULL)
		exit_with_cmd_error("", pipex);
	if (get_slash_idx(*cmd_name) == -1)
		check_cmd_path(cmd_name, pipex);
	else
		check_cmd_wd(*cmd_name, pipex);
}
