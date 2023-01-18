/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:26:01 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/24 00:09:40 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "buildtin.h"
# include "pipex_types.h"
# include "parse.h"

# define EXIT_FILE_NOT_FOUND	(127)

int	g_pid;

char	**add_zero_arg(char **argv, char *arg);
int		execute_commands(t_exec *exec, t_local_env *local_env, int *exit);
char	*get_full_dir(char *str, t_local_env *loc_env);
int		fill_cmd_param(t_exec *exec, t_cmd_param *cmd_param,
			int (*pipe_fd)[2], t_local_env *local_env);
int		free_n_null_ptr(char **ptr);
int		safe_open(int *fd, char *file, int flags, int mode);
char	*find_cmd_dir(char **path, char *cmd_str, t_local_env *loc_env);
int		get_out_fd(t_inout inout, t_cmd_param *cmd_param, int (*pipe_fd)[2]);
int		get_in_fd(t_inout inout, t_inout *inout_arr, t_cmd_param *cmd_param,
			int (*pipe_fd)[2]);
int		check_for_valid_path(t_cmd_param *cmd_param, t_local_env *local_env);
int		print_cmd_not_fnd(char *cmd_str);

#endif