/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 02:13:02 by younglee          #+#    #+#             */
/*   Updated: 2022/05/04 23:39:24 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef struct s_pipex
{
	char	*execpath;
	char	*inputpath;
	char	*outputpath;
	char	*cmd1;
	char	*cmd2;
	// int		prev_pipe[2];
	// int		next_pipe[2];
}t_pipex;

void	init_pipex(int argc, char **argv, t_pipex *pipex);
void	free_all(t_pipex *pipex);
void	exit_with_clib_error(t_pipex *pipex);
void	exit_with_custom_error(int my_errno, t_pipex *pipex);

#endif
