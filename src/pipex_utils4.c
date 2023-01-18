/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:40:37 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 23:40:53 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

int	print_path_err(char *tmp_path1, char *tmp_path2, char *cmd_str)
{
	if (tmp_path1 == NULL || tmp_path2 == NULL || cmd_str == NULL)
		return (0);
	ft_putstr_fd("Command '", STDERR);
	ft_putstr_fd(cmd_str, STDERR);
	ft_putstr_fd("' is available in the following places\n * ", STDERR);
	ft_putstr_fd(tmp_path1, STDERR);
	ft_putstr_fd("\n * ", STDERR);
	ft_putstr_fd(tmp_path2, STDERR);
	ft_putstr_fd("\nThe command could not be located because '/bin:/usr/bin'\
is not included in the PATH environment variable.\n", STDERR);
	return (1);
}

int	check_for_valid_path(t_cmd_param *cmd_param, t_local_env *local_env)
{
	char	*tmp_path1;
	char	*tmp_path2;
	char	*path_val;

	if (cmd_param == NULL || local_env == NULL)
		return (0);
	path_val = get_env_val(local_env, "PATH", NULL);
	if (path_val == NULL || ft_strcmp(path_val, "") == 0)
		return (1);
	update_path_mas(local_env);
	tmp_path1 = ft_strjoin("/bin/", cmd_param->cmd_str);
	if (tmp_path1 == NULL)
		return (0);
	tmp_path2 = ft_strjoin("/usr/bin/", cmd_param->cmd_str);
	if (tmp_path2 == NULL)
	{
		free(tmp_path1);
		return (0);
	}
	if (access(tmp_path1, 0) == 0 && access(tmp_path2, 0) == 0)
		print_path_err(tmp_path1, tmp_path2, cmd_param->cmd_str);
	free (tmp_path1);
	free (tmp_path2);
	return (1);
}

int	print_cmd_not_fnd(char *cmd_str)
{
	if (cmd_str == NULL)
		return (0);
	ft_putstr_fd(cmd_str, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
	return (1);
}
