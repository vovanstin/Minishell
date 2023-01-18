/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtin_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:01:50 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 23:26:45 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/buildtin.h"

int	check_prev_eq(t_local_env *local_env, char *argument, char *key)
{
	if (local_env == NULL || argument == NULL || key == NULL)
		return (0);
	if (get_env_val(local_env, key, NULL) == NULL)
		return (1);
	if (ft_strchr(argument, '=') == NULL)
		return (0);
	return (1);
}

int	parse_n_set_exp_arg(t_local_env *local_env, char *argument)
{
	int		i;
	char	*key;

	if (local_env == NULL || argument == NULL)
		return (0);
	i = 0;
	if (!ft_isalpha(argument[i]) && argument[i] != '_')
		return (0);
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]) && argument[i] != '_')
			return (0);
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(key, argument, i + 1);
	if (ft_strcmp(key, "_") != 0 && check_prev_eq(local_env, argument, key))
	{
		if (argument[i] != 0)
			set_env_val(local_env, key, &argument[i + 1]);
		else
			set_env_val(local_env, key, NULL);
	}
	free(key);
	return (1);
}

int	ft_export(t_cmd_param *cmd_param, t_local_env *local_env)
{
	int	i;

	if (cmd_param == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	i = 0;
	if (cmd_param->cmd_args[i] == NULL)
	{
		update_exp_str(local_env);
		ft_putstr_fd(local_env->exp_str, cmd_param->out_fd);
	}
	while (cmd_param->cmd_args[i])
	{
		if (parse_n_set_exp_arg(local_env, cmd_param->cmd_args[i]) == 0)
		{
			ft_putstr_fd("bash: export: `", STDERR);
			ft_putstr_fd(cmd_param->cmd_args[i], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*parse_n_get_key(char *argument)
{
	int		i;
	char	*key;

	if (argument == NULL)
		return (NULL);
	i = 0;
	if (!ft_isalpha(argument[i]) && argument[i] != '_')
		return (NULL);
	while (argument[i] || argument[i] == '=')
	{
		if (!ft_isalnum(argument[i]) && argument[i] != '_')
			return (NULL);
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(key, argument, i + 1);
	return (key);
}

int	ft_unset(t_cmd_param *cmd_param, t_local_env *local_env)
{
	int		i;
	char	*key;

	if (cmd_param == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (cmd_param->cmd_args[i])
	{
		key = parse_n_get_key(cmd_param->cmd_args[i]);
		if (key == NULL)
		{
			ft_putstr_fd("bash: unset: `", STDERR);
			ft_putstr_fd(cmd_param->cmd_args[i], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
			return (EXIT_FAILURE);
		}
		unset_env(local_env, key);
		free (key);
		i++;
	}
	return (EXIT_SUCCESS);
}
