/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 02:13:02 by younglee          #+#    #+#             */
/*   Updated: 2022/05/06 20:03:12 by younglee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <sys/wait.h>

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
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	pid_t	cmd1_pid;
	pid_t	cmd2_pid;
}t_pipex;

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex);
void	free_all(t_pipex *pipex);
void	free_split_arr(char **split_arr);
void	check_cmd_path(char **cmd_name, t_pipex *pipex);
void	print_clib_error(char *msg, t_pipex *pipex);
void	exit_with_clib_error(char *msg, t_pipex *pipex);
void	exit_with_custom_error(int my_errno, t_pipex *pipex);
void	start_pipex(char **envp, t_pipex *pipex);
void	end_pipex(char **envp, t_pipex *pipex);
void	close_one_fd(int *fd, char *msg, t_pipex *pipex);
void	close_all_fd(t_pipex *pipex);
void	wait_all_child(t_pipex *pipex);

#endif
