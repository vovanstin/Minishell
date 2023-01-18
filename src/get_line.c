/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:06:36 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 23:05:12 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

char	*gkl(char *line, int *i)
{
	char	*key;
	int		j;
	int		k;
	int		result;

	k = ++(*i);
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\"' && line[*i])
		(*i)++;
	result = (*i) - k;
	key = malloc(sizeof(char) * (result + 1));
	if (!key)
		return (NULL);
	while (j < result)
		key[j++] = line[k++];
	key[j] = '\0';
	return (key);
}

char	*space_alloc(char *line, t_local_env *env, char *result)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
		count += get_count(line, &i, env, result);
	new = malloc(sizeof(char) * (count + 1));
	free(result);
	if (!new)
		return (NULL);
	return (new);
}

void	enter_line(char **new, int *j, char *line, int is_free)
{
	int	i;

	i = 0;
	while (line && *(line + i))
	{
		if (quotes(*new, *j) == 0 && is_sep(line, i))
		{
			(*new)[(*j)++] = ' ';
			(*new)[(*j)++] = line[i++];
			if (quotes(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
				(*new)[(*j)++] = line[i++];
			(*new)[(*j)++] = ' ';
		}
		else
			(*new)[(*j)++] = line[i++];
	}
	if (is_free)
		free(line);
}

void	add_sep(char **new, char *line, int *i, int *j)
{
	if (quotes(line, *i) == 0 && is_sep(line, *i))
	{
		(*new)[(*j)++] = ' ';
		(*new)[(*j)++] = line[(*i)++];
		if (quotes(line, *i) == 0 && (line[*i] == '>' || line[*i] == '<'))
			(*new)[(*j)++] = line[(*i)++];
		(*new)[(*j)++] = ' ';
	}
	else
		(*new)[(*j)++] = line[(*i)++];
}

char	*space_line(char *line, t_local_env *env, int result)
{
	char	*new;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line, env, ft_itoa(result));
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$')
		{
			var = gkl(line, &i);
			if (!ft_strcmp(var, "?"))
				enter_line(&new, &j, ft_itoa(result), 1);
			else
				enter_line(&new, &j, get_env_val(env, var, NULL), 0);
			free(var);
		}
		else
			add_sep(&new, line, &i, &j);
	}
	new[j] = '\0';
	free(line);
	return (new);
}
