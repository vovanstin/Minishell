/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:24:39 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 18:36:23 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILDTIN_H
# define BUILDTIN_H

# include <unistd.h>
# include "pipex_types.h"
# include "local_env.h"
# include "../lib/libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <limits.h>

# define BUILDTIN_CMD_CNT		(7)
# define BUILDTIN_CMD_MAX_LEN	(7)

typedef int	t_buildtin(t_cmd_param *cmd_param, t_local_env *local_env);

int	buildtin_cmd(t_cmd_param *cmd_param, t_local_env *local_env,
		int *exit, t_exec *crnt_exec);
int	ft_echo(t_cmd_param *cmd_param, t_local_env *local_env);
int	ft_cd(t_cmd_param *cmd_param, t_local_env *local_env);
int	ft_pwd(t_cmd_param *cmd_param, t_local_env *local_env);
int	ft_export(t_cmd_param *cmd_param, t_local_env *local_env);
int	ft_unset(t_cmd_param *cmd_param, t_local_env *local_env);
int	ft_env(t_cmd_param *cmd_param, t_local_env *local_env);
int	ft_exit(t_cmd_param *cmd_param, t_local_env *local_env);

#endif