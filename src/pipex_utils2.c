/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:40:31 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 23:07:08 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

int	is_buildtin(char *cmd_str, t_cmd_type *cmd_type)
{
	static const char	buildtin_names[BUILDTIN_CMD_CNT][BUILDTIN_CMD_MAX_LEN]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	if (cmd_str == NULL || cmd_type == NULL)
		return (0);
	*cmd_type = CMD_ECHO;
	while (*cmd_type != CMD_NOT_FOUND)
	{
		if (ft_strcmp(cmd_str, buildtin_names[*cmd_type]) == 0)
			break ;
		(*cmd_type)++;
	}
	return (1);
}

int	free_n_null_ptr(char **ptr)
{
	if (ptr == NULL)
		return (0);
	if (*ptr != NULL)
		free (*ptr);
	*ptr = NULL;
	return (1);
}

int	get_cmd_type(t_cmd_type	*cmd_type, char **cmd_dir, t_local_env *local_env
	, t_exec *e)
{
	int	i;

	if (cmd_type == NULL || local_env == NULL || cmd_dir == NULL)
		return (0);
	if (e->cmd_str == NULL)
	{
		i = 0;
		while (e->inout[i].type != DEFAULT && e->inout[i].type != FILE_CINPUT)
			i++;
		if (e->inout[i].type == FILE_CINPUT)
		{
			*cmd_type = CMD_NOPE;
			return (1);
		}
	}
	if (!is_buildtin(e->cmd_str, cmd_type))
		return (0);
	update_path_mas(local_env);
	if (*cmd_type == CMD_NOT_FOUND)
	{
		*cmd_dir = find_cmd_dir(local_env->path_mas, e->cmd_str, local_env);
		if (*cmd_dir != NULL)
			*cmd_type = CMD_FROM_DIR;
	}
	return (1);
}

int	get_in_out_fd(t_exec *exec, t_cmd_param *cmd_param,
	int (*pipe_fd)[2], int i)
{
	if ((*exec).inout[i].type <= 3)
	{
		if (!get_out_fd((*exec).inout[i], cmd_param, pipe_fd))
		{
			cmd_param->cmd_type = CMD_NOPE;
			return (EXIT_FAILURE);
		}
	}
	else if (!get_in_fd((*exec).inout[i], (*exec).inout, cmd_param, pipe_fd))
	{
		cmd_param->cmd_type = CMD_NOPE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	fill_cmd_param(t_exec *exec, t_cmd_param *cmd_param,
	int (*pipe_fd)[2], t_local_env *local_env)
{
	t_cmd_type	cmd_type;
	char		*cmd_dir;
	int			i;

	cmd_dir = NULL;
	cmd_param->cmd_type = CMD_NOT_FOUND;
	if (exec == NULL || cmd_param == NULL
		|| *pipe_fd == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while ((*exec).inout[i].type != DEFAULT)
	{
		if (get_in_out_fd(exec, cmd_param, pipe_fd, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (!get_cmd_type(&cmd_type, &cmd_dir, local_env, exec))
		return (EXIT_FAILURE);
	cmd_param->cmd_str = exec->cmd_str;
	if (cmd_param->cmd_dir != NULL)
		free(cmd_param->cmd_dir);
	cmd_param->cmd_dir = cmd_dir;
	cmd_param->cmd_type = cmd_type;
	cmd_param->cmd_args = exec->cmd_args;
	return (EXIT_SUCCESS);
}
