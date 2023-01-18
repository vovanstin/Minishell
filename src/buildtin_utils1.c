/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtin_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:00:52 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/24 01:33:40 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/buildtin.h"

char	*precess_dir(char *dst, char *dir)
{
	int		len;
	char	*tmp;

	if (dst == NULL || dir == NULL)
		return (0);
	if (ft_strcmp(dir, "..") == 0)
	{
		len = ft_strlen(dst);
		while (len)
		{
			if (dst[len] == '/')
			{
				dst[len] = 0;
				return (dst);
			}	
			len--;
		}
	}
	else if (ft_strcmp(dir, ".") == 0)
		return (dst);
	tmp = ft_strjoin(dst, "/");
	free(dst);
	dst = ft_strjoin(tmp, dir);
	free(tmp);
	return (dst);
}

char	*get_full_dir(char *str, t_local_env *loc_env)
{
	char	*dir;
	char	**dir_mas;
	int		i;

	if (str == NULL || loc_env == NULL || !ft_strcmp(str, ""))
		return (ft_strdup(get_env_val(loc_env, "HOME", NULL)));
	dir_mas = ft_split(str, '/');
	if (dir_mas == NULL)
		return (0);
	i = 0;
	if (str[0] == '/')
		dir = ft_strdup("/");
	else if (ft_strcmp(*dir_mas, "~") == 0 && ++i)
		dir = ft_strdup(get_env_val(loc_env, "HOME", NULL));
	else
		dir = ft_strdup(get_env_val(loc_env, "PWD", NULL));
	if (dir == NULL)
		return (0);
	while (dir_mas[i])
	{
		dir = precess_dir(dir, dir_mas[i]);
		i++;
	}
	free_ptr_mas(dir_mas);
	return (dir);
}

int	ch_env_dir(char *new_dir, t_local_env *local_env)
{
	char	*crnt_dir;

	if (new_dir == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	crnt_dir = get_env_val(local_env, "PWD", NULL);
	if (crnt_dir == NULL)
		return (0);
	set_env_val(local_env, "OLDPWD", crnt_dir);
	set_env_val(local_env, "PWD", new_dir);
	free (new_dir);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd_param *cmd_param, t_local_env *l_env)
{
	char	*full;

	if (cmd_param == NULL || cmd_param->cmd_args == NULL || l_env == NULL)
		return (EXIT_FAILURE);
	if (cmd_param->cmd_args[0] != NULL && cmd_param->cmd_args[1] != NULL)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", STDERR);
		return (EXIT_FAILURE);
	}
	full = get_full_dir(cmd_param->cmd_args[0], l_env);
	if (full == NULL)
		return (EXIT_FAILURE);
	if (chdir(full) == EXIT_SUCCESS && ch_env_dir(full, l_env) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("bash: cd: ", STDERR);
		ft_putstr_fd(cmd_param->cmd_args[0], STDERR);
		if (access(cmd_param->cmd_args[0], 0) != 0)
			ft_putstr_fd(": No such file or directory\n", STDERR);
		else
			ft_putstr_fd(": Not a directory\n", STDERR);
	}
	free(full);
	return (EXIT_FAILURE);
}

int	ft_pwd(t_cmd_param *cmd_param, t_local_env *local_env)
{
	char	*dir;

	if (cmd_param == NULL || local_env == NULL)
		return (EXIT_FAILURE);
	dir = get_env_val(local_env, "PWD", NULL);
	if (dir == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd(dir, cmd_param->out_fd);
	ft_putstr_fd("\n", cmd_param->out_fd);
	return (EXIT_SUCCESS);
}
