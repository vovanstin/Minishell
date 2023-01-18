/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:55:19 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 20:34:57 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/local_env.h"

char	*create_exp_str(char *key, char *val)
{
	int		key_len;
	int		val_len;
	char	*env_str;

	if (key == NULL)
		return (0);
	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	if (key_len == 0)
		return (NULL);
	env_str = malloc(sizeof(char)
			* (11 + key_len + 1 + 1 + val_len + 1 + 1 + 1));
	if (env_str == NULL)
		return (0);
	ft_strlcpy(env_str, "declare -x ", 11 + 1);
	ft_strlcpy(&env_str[11], key, key_len + 1);
	if (val == NULL)
		ft_strlcpy(&env_str[11 + key_len], "\n", 1 + 1);
	else
	{
		ft_strlcpy(&env_str[11 + key_len], "=\"", 2 + 1);
		ft_strlcpy(&env_str[11 + key_len + 2], val, val_len + 1);
		ft_strlcpy(&env_str[11 + key_len + val_len + 2], "\"\n", 2 + 1);
	}
	return (env_str);
}

int	update_env_mas(t_local_env *loc_env)
{
	char		update_bit;

	if (loc_env == NULL)
		return (0);
	update_bit = (loc_env->is_valid_flag & ENV_MAS_MASK) == 0;
	if (update_bit)
	{
		update_env_str(loc_env);
		if (loc_env->env_mas != NULL)
			free_ptr_mas(loc_env->env_mas);
		loc_env->env_mas = ft_split(loc_env->env_str, '\n');
	}
	loc_env->is_valid_flag = loc_env->is_valid_flag | ENV_MAS_MASK;
	return (1);
}

int	update_path_mas(t_local_env *local_env)
{
	char	update_bit;
	char	*path_str;

	if (local_env == NULL)
		return (0);
	update_bit = (local_env->is_valid_flag & PATH_MAS_MASK) == 0;
	if (update_bit)
	{
		path_str = get_env_val(local_env, "PATH", NULL);
		free_ptr_mas(local_env->path_mas);
		if (path_str != NULL)
			local_env->path_mas = ft_split(path_str, ':');
		else
			local_env->path_mas = ft_split("/", ':');
	}
	local_env->is_valid_flag = local_env->is_valid_flag | PATH_MAS_MASK;
	return (1);
}

int	update_env_str(t_local_env *loc_env)
{
	char		*tmp_str;
	char		*crnt_str;
	t_env_lst	*crnt_lst;

	if (loc_env == NULL || loc_env->env_lst == NULL)
		return (0);
	if ((loc_env->is_valid_flag & ENV_STR_MASK) == ENV_STR_MASK)
		return (1);
	crnt_lst = loc_env->env_lst;
	if (loc_env->env_str != NULL)
		free (loc_env->env_str);
	loc_env->env_str = ft_strdup("");
	while (crnt_lst)
	{
		crnt_str = create_env_str(crnt_lst->key, crnt_lst->val);
		if (crnt_str == NULL)
			return (0);
		tmp_str = ft_strjoin(crnt_str, loc_env->env_str);
		free (crnt_str);
		free(loc_env->env_str);
		loc_env->env_str = tmp_str;
		crnt_lst = crnt_lst->next;
	}
	loc_env->is_valid_flag = loc_env->is_valid_flag | ENV_STR_MASK;
	return (1);
}
