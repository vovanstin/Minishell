/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtin_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:04:09 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 18:04:23 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/buildtin.h"

int	is_num(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoll_byte(const char *str, int *result)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	if (str)
	{
		if (*str == '-' || *str == '+')
		{
			sign = (*str == '+') - (*str == '-');
			str++;
		}
		while (*str)
		{
			num = (num * 10) + (*str - '0');
			str++;
		}
	}
	else
		return (0);
	if (num <= ((unsigned long long)LLONG_MAX + (sign < 0)))
		*result = num & 0xFF;
	else
		return (0);
	return (1);
}

int	exit_parse(char *arg, int *result)
{
	int	i;

	if (arg == NULL || result == NULL)
		return (0);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] != 0 || i > (19 + (arg[0] == '-' || arg[0] == '+')))
		return (0);
	if (ft_atoll_byte(arg, result) == 0)
		return (0);
	return (1);
}

int	print_arg_fail(char *arg)
{
	ft_putstr_fd("bash: exit: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	return (0);
}

int	ft_exit(t_cmd_param *cmd_param, t_local_env *local_env)
{
	int	result;

	if (cmd_param == NULL || local_env == NULL || cmd_param->cmd_args == NULL)
		return (EXIT_FAILURE);
	result = EXIT_SUCCESS;
	ft_putstr_fd("exit\n", cmd_param->out_fd);
	if (cmd_param->cmd_args[0] == NULL)
		return (EXIT_SUCCESS);
	if (is_num(cmd_param->cmd_args[0])
		&& exit_parse(cmd_param->cmd_args[0], &result))
	{
		if (cmd_param->cmd_args[1] != NULL)
		{
			cmd_param->cmd_type = CMD_NOT_FOUND;
			ft_putstr_fd("bash: exit: too many arguments\n", STDERR);
			result = EXIT_FAILURE;
		}
	}
	else
	{
		result = 2;
		print_arg_fail(cmd_param->cmd_args[0]);
	}	
	return (result);
}
