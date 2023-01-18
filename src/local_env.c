/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:06:33 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 20:40:29 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/local_env.h"

t_env_lst	*set_env_val(t_local_env *loc_env, char *key, char *val)
{
	t_env_lst	*crnt_env;
	char		*tmp_val;

	if (loc_env == NULL || key == NULL)
		return (0);
	crnt_env = NULL;
	tmp_val = get_env_val(loc_env, key, &crnt_env);
	if (tmp_val == NULL && crnt_env == NULL)
		crnt_env = env_lst_add_front(&loc_env->env_lst, key, val);
	else
	{
		if (val != NULL)
		{
			tmp_val = ft_strdup(val);
			if (tmp_val == NULL)
				return (0);
		}
		else
			tmp_val = NULL;
		if (crnt_env->val != NULL)
			free (crnt_env->val);
		crnt_env->val = tmp_val;
	}
	loc_env->is_valid_flag = 0;
	return (crnt_env);
}

int	unset_env(t_local_env *local_env, char *key)
{
	t_env_lst	*crnt;
	t_env_lst	*prev;

	if (local_env == NULL || local_env->env_lst == NULL)
		return (0);
	get_env_val(local_env, key, &crnt);
	if (crnt == NULL)
		return (1);
	if (crnt == local_env->env_lst)
		local_env->env_lst = local_env->env_lst->next;
	else
	{
		prev = local_env->env_lst;
		while (prev && prev->next && prev->next != crnt)
			prev = prev->next;
		if (prev->next == crnt)
			prev->next = crnt->next;
	}
	if (crnt->key != NULL)
		free(crnt->key);
	if (crnt->val != NULL)
		free(crnt->val);
	free(crnt);
	local_env->is_valid_flag = 0;
	return (1);
}

int	null_env(t_local_env *loc_env)
{
	if (loc_env == NULL)
		return (0);
	loc_env->env_lst = NULL;
	loc_env->env_str = NULL;
	loc_env->exp_str = NULL;
	loc_env->path_mas = NULL;
	loc_env->env_mas = NULL;
	loc_env->is_valid_flag = 0;
	return (1);
}

int	init_local_env(t_local_env *loc_env, char **env_ptr)
{
	char	*shlvl_str;
	int		shlvl_int;

	if (loc_env == NULL || env_ptr == NULL)
		return (0);
	null_env(loc_env);
	copy_env(loc_env, env_ptr);
	shlvl_str = get_env_val(loc_env, "SHLVL", NULL);
	if (shlvl_str == NULL)
		return (0);
	shlvl_int = ft_atoi(shlvl_str) + 1;
	if (shlvl_int < 1)
		shlvl_int = 1;
	shlvl_str = ft_itoa(shlvl_int);
	set_env_val(loc_env, "SHLVL", shlvl_str);
	free (shlvl_str);
	return (1);
}

int	free_env(t_local_env *loc_env)
{
	t_env_lst	*crnt_lst;
	t_env_lst	*temp;

	if (loc_env == NULL)
		return (0);
	if (loc_env->env_str != NULL)
		free(loc_env->env_str);
	if (loc_env->exp_str != NULL)
		free(loc_env->exp_str);
	crnt_lst = loc_env->env_lst;
	while (crnt_lst)
	{
		if (crnt_lst->key != NULL)
			free(crnt_lst->key);
		if (crnt_lst->val != NULL)
			free(crnt_lst->val);
		temp = crnt_lst;
		crnt_lst = crnt_lst->next;
		free(temp);
	}
	free_ptr_mas(loc_env->env_mas);
	free_ptr_mas(loc_env->path_mas);
	null_env(loc_env);
	return (0);
}
