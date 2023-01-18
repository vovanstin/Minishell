/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:52:01 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 17:54:09 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/local_env.h"

int	get_key_n_len(char **env_ptr, char **key, int *key_len)
{
	*key_len = 0;
	while ((*env_ptr)[*key_len] != '=' && (*env_ptr)[*key_len] != 0)
		(*key_len)++;
	*key = (char *)malloc(*key_len + 1);
	if (*key == NULL)
		return (0);
	return (1);
}

int	copy_env(t_local_env *loc_env, char **env_ptr)
{
	char			*key;
	char			*val;
	int				key_len;
	t_env_lst		*new_env_lst;

	if (loc_env == NULL || env_ptr == NULL)
		return (0);
	if (loc_env->env_lst != NULL)
		free_env(loc_env);
	while (*env_ptr && get_key_n_len(env_ptr, &key, &key_len))
	{
		ft_strlcpy(key, *env_ptr, key_len + 1);
		val = &(*env_ptr)[key_len + 1];
		new_env_lst = set_env_val(loc_env, key, val);
		if (new_env_lst == NULL)
		{
			free_env(loc_env);
			return (0);
		}
		free(key);
		env_ptr++;
	}
	loc_env->is_valid_flag = 0;
	return (1);
}

char	*get_env_val(t_local_env *loc_env, char *key, t_env_lst **env_list)
{
	t_env_lst	*crnt_env;

	if (env_list != NULL)
		*env_list = NULL;
	if (loc_env == NULL || key == NULL)
		return (0);
	crnt_env = loc_env->env_lst;
	while (crnt_env)
	{
		if (ft_strcmp(key, crnt_env->key) == 0)
		{
			if (env_list != NULL)
				*env_list = crnt_env;
			return (crnt_env->val);
		}
		crnt_env = crnt_env->next;
	}
	return (NULL);
}

t_env_lst	*env_lst_add_front(t_env_lst **head_env, char *key, char *val)
{
	t_env_lst	*new_env;

	if (head_env == NULL || key == NULL)
		return (0);
	new_env = malloc(sizeof (t_env_lst));
	if (new_env == NULL)
		return (0);
	new_env->key = ft_strdup(key);
	if (new_env->key == NULL)
	{
		free (new_env);
		return (0);
	}
	new_env->val = val;
	if (val != NULL)
		new_env->val = ft_strdup(val);
	if (new_env->val == NULL && val != NULL)
	{
		free (new_env->key);
		free (new_env);
		return (0);
	}
	new_env->next = *head_env;
	*head_env = new_env;
	return (new_env);
}

char	*create_env_str(char *key, char *val)
{
	int		key_len;
	int		val_len;
	char	*env_str;

	if (val == NULL)
		return (ft_strdup(""));
	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	if (key_len == 0)
		return (NULL);
	if (val_len == 0)
		env_str = malloc(sizeof(char) * (key_len + 2 + 1));
	else
		env_str = malloc(sizeof(char) * (key_len + val_len + 3 + 1));
	if (env_str == NULL)
		return (0);
	ft_strlcpy(env_str, key, key_len + 1);
	ft_strlcpy(&env_str[key_len], "=\n", 3);
	if (val != NULL)
	{
		ft_strlcpy(&env_str[key_len + 1], val, val_len + 1);
		ft_strlcpy(&env_str[key_len + val_len + 1], "\n", 1 + 1);
	}
	return (env_str);
}
