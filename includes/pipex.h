/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 02:13:02 by younglee          #+#    #+#             */
/*   Updated: 2022/05/05 05:30:06 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef struct s_pipex
{
	char	*exec_path;
	char	*input_path;
	char	*output_path;
	char	**cmd1_argv;
	char	**cmd2_argv;
	char	**cmd_path;
}t_pipex;

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex);
void	free_all(t_pipex *pipex);
void	exit_with_clib_error(char *msg, t_pipex *pipex);
void	exit_with_custom_error(int my_errno, t_pipex *pipex);

#endif
