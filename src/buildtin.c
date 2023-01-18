/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:24:39 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 22:19:10 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/buildtin.h"

int	check_inout_pipes(t_exec *crnt_exec)
{
	int	i;

	if (crnt_exec == NULL)
		return (0);
	i = 0;
	while (i < crnt_exec->inout_cnt)
	{
		if (crnt_exec->inout[i].type == FILE_PIPE_OUT)
			return (2);
		i++;
	}
	i = 0;
	while (i < crnt_exec->inout_cnt)
	{
		if (crnt_exec->inout[i].type == FILE_PIPE_IN)
			return (1);
		i++;
	}
	return (0);
}

int	buildtin_cmd(t_cmd_param *cmd_param, t_local_env *local_env, int *exit,
	t_exec *crnt_exec)
{
	static t_buildtin	*buildtin[BUILDTIN_CMD_CNT]
		= {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	int					result;
	int					is_pipe;

	if (cmd_param == NULL || local_env == NULL)
		return (0);
	if (cmd_param->cmd_args == NULL)
		return (0);
	if (cmd_param->cmd_type < CMD_ECHO || cmd_param->cmd_type > CMD_EXIT)
		return (0);
	result = buildtin[cmd_param->cmd_type](cmd_param, local_env);
	is_pipe = check_inout_pipes(crnt_exec);
	if (cmd_param->cmd_type == CMD_EXIT)
	{
		if (is_pipe == 0)
			*exit = 1;
		else if (is_pipe == 2)
			result = EXIT_SUCCESS;
	}
	return (result);
}

int	putstr_w_wo_n_fd(char *s, int fd, int n_key)
{
	int	len;

	if (s == NULL || (fd < 0))
		return (0);
	if (n_key != -1)
	{
		while (*s)
		{
			if (*s != '\n')
				write(fd, s, 1);
			s++;
		}
	}
	else
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	return (1);
}

int	ft_echo(t_cmd_param *cmd_param, t_local_env *local_env)
{
	int	i;
	int	n_key;

	i = 0;
	n_key = -1;
	if (cmd_param == NULL || cmd_param->cmd_args == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	while (cmd_param->cmd_args[i])
	{
		if (ft_strcmp(cmd_param->cmd_args[i], "-n") == 0)
			n_key = i;
		else
			break ;
		i++;
	}
	while (cmd_param->cmd_args[i])
	{
		if (i != n_key + 1)
			write(cmd_param->out_fd, " ", 1);
		putstr_w_wo_n_fd(cmd_param->cmd_args[i], cmd_param->out_fd, n_key);
		i++;
	}
	if (n_key == -1)
		write(cmd_param->out_fd, "\n", 1);
	return (EXIT_SUCCESS);
}

int	ft_env(t_cmd_param *cmd_param, t_local_env *local_env)
{
	if (cmd_param == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	update_env_str(local_env);
	ft_putstr_fd(local_env->env_str, cmd_param->out_fd);
	return (EXIT_SUCCESS);
}
