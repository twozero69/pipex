/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_pipex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 01:37:00 by younglee          #+#    #+#             */
/*   Updated: 2022/05/07 19:59:45 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "pipex_bonus.h"
#include "get_next_line.h"
#include "libft.h"

static int	get_new_line_idx(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

static	void	write_here_doc(t_pipex *pipex)
{
	char	*line;
	size_t	cmp_len;
	int		new_line_idx;

	cmp_len = ft_strlen(pipex->limiter) + 1;
	while (TRUE)
	{
		line = get_next_line(0);
		print_clib_error("here_doc_pipex.c: get_next_line", pipex);
		new_line_idx = get_new_line_idx(line);
		if (new_line_idx != -1)
			line[new_line_idx] = '\0';
		if (ft_strncmp(pipex->limiter, line, cmp_len) == 0)
			break ;
		if (new_line_idx != -1)
			line[new_line_idx] = '\n';
		ft_putstr_fd(line, STDOUT_FILENO);
		print_clib_error("here_doc_pipex.c: ft_putstr_fd", pipex);
		free(line);
		print_clib_error("here_doc_pipex.c: free", pipex);
	}
	free(line);
	print_clib_error("here_doc_pipex.c: free", pipex);
}

void	here_doc_pipex(t_pipex *pipex)
{
	t_cmd	*curr_cmd;

	curr_cmd = &pipex->here_doc;
	pipe(curr_cmd->pipe_fd);
	print_clib_error("here_doc_pipex.c: pipe", pipex);
	curr_cmd->pid = fork();
	print_clib_error("here_doc_pipex.c: fork", pipex);
	if (curr_cmd->pid == 0)
	{
		dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO);
		print_clib_error("here_doc_pipex.c: dup2 pipe_fd[1]", pipex);
		write_here_doc(pipex);
		free_all(pipex);
		exit(0);
	}
	else if (curr_cmd->pid > 0)
	{
		waitpid(curr_cmd->pid, NULL, 0);
		curr_cmd->pid = 0;
	}
	close_one_fd(&curr_cmd->pipe_fd[1], "here_doc_pipex.c: close [1]", pipex);
}
