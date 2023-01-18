/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:09:48 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 23:05:16 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (i != index && line[i])
	{
		if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int	is_sep(char *line, int i)
{
	if (ft_strchr("<>|", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int	get_count(char *line, int *i, t_local_env *env, char *result)
{
	char	*var;
	int		count;

	count = 0;
	if (is_sep(line, *i))
		count += 2;
	if (line[*i] == '$' && quotes(line, *i) != 2)
	{
		var = gkl(line, i);
		if (!ft_strcmp(var, "?"))
			count += ft_strlen(result);
		else
			count += ft_strlen(get_env_val(env, var, NULL));
		free(var);
	}
	else
		(*i)++;
	count++;
	return (count);
}
