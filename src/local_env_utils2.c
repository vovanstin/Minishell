/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:54:44 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 18:00:27 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/local_env.h"

int	strcmp_ind(char *s1, char *s2, int *index)
{
	int	i;

	if (s1 == NULL || s2 == NULL || index == NULL)
		return (0);
	i = 0;
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		i++;
	}
	*index = i;
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

int	is_min_dif(t_dif_ind tmp, t_dif_ind min, t_env_lst *head, t_env_lst *next)
{
	int	result;

	if (head == NULL)
		return (0);
	if (ft_strcmp(head->key, "_") == 0)
		return (0);
	result = ((tmp.dif > 0 && (tmp.index > min.index \
		|| (tmp.index == min.index && tmp.dif < min.dif))) \
		|| (tmp.dif == min.dif && tmp.index == min.index \
		&& ft_strcmp(head->key, next->key) < 0));
	return (result);
}

t_env_lst	*get_next_alfor_lst(t_env_lst *head_lst, char *crnt_key)
{
	t_dif_ind	min;
	t_dif_ind	tmp;
	t_env_lst	*next_lst;

	if (head_lst == NULL)
		return (NULL);
	min.dif = 0xFF;
	min.index = 0;
	if (crnt_key == NULL)
		crnt_key = "";
	while (head_lst)
	{
		tmp.dif = strcmp_ind(head_lst->key, crnt_key, &tmp.index);
		if (is_min_dif(tmp, min, head_lst, next_lst))
		{
			min.dif = tmp.dif;
			next_lst = head_lst;
			min.index = tmp.index;
		}
		head_lst = head_lst->next;
	}
	if (min.dif == 0xFF)
		return (NULL);
	return (next_lst);
}

int	update_exp_str(t_local_env *loc_env)
{
	char		*tmp_str;
	char		*crnt_str;
	t_env_lst	*crnt_lst;

	if (loc_env == NULL || loc_env->env_lst == NULL)
		return (0);
	if ((loc_env->is_valid_flag & EXP_STR_MASK) == EXP_STR_MASK)
		return (1);
	crnt_lst = loc_env->env_lst;
	if (loc_env->exp_str != NULL)
		free (loc_env->exp_str);
	loc_env->exp_str = ft_strdup("");
	crnt_lst = get_next_alfor_lst(loc_env->env_lst, NULL);
	while (crnt_lst)
	{
		crnt_str = create_exp_str(crnt_lst->key, crnt_lst->val);
		tmp_str = ft_strjoin(loc_env->exp_str, crnt_str);
		if (crnt_str != NULL)
			free (crnt_str);
		free(loc_env->exp_str);
		loc_env->exp_str = tmp_str;
		crnt_lst = get_next_alfor_lst(loc_env->env_lst, crnt_lst->key);
	}
	loc_env->is_valid_flag = loc_env->is_valid_flag | EXP_STR_MASK;
	return (1);
}

int	free_ptr_mas(char **mas)
{
	int	i;

	if (mas == NULL)
		return (0);
	i = 0;
	while (mas[i])
	{
		free(mas[i]);
		i++;
	}
	free (mas);
	return (0);
}
