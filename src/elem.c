/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:04:52 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 18:26:41 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

t_elem	*prev_sep(t_elem *elem, int skip)
{
	if (elem && skip)
		elem = elem->prev;
	while (elem && elem->type < TRUNC)
		elem = elem->prev;
	return (elem);
}

int	is_last_valid_arg(t_elem *elem)
{
	t_elem	*prev;

	if (!elem || check_type(elem, CMD) || check_type(elem, ARG))
	{
		prev = prev_sep(elem, 0);
		if (!prev || check_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

void	next_alloc(char *line, int *i, t_elem	**elem)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	*elem = malloc(sizeof(t_elem));
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
	}
	(*elem)->str = malloc(sizeof(char) * (j - count + 1));
}

t_elem	*next_elem(char *line, int *i)
{
	t_elem	*elem;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	next_alloc(line, i, &elem);
	if (!elem || !elem->str)
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else
			elem->str[j++] = line[(*i)++];
	}
	elem->str[j] = '\0';
	return (elem);
}

t_elem	*get_elems(char *line)
{
	t_elem	*prev;
	t_elem	*next;
	int		i;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		next = next_elem(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
