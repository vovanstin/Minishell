/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:01:14 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 17:41:08 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	type_arg(t_elem *elem)
{
	if (ft_strncmp(elem->str, "", 3) == 0)
		elem->type = EMPTY;
	else if (ft_strncmp(elem->str, ">", 3) == 0)
		elem->type = TRUNC;
	else if (ft_strncmp(elem->str, ">>", 3) == 0)
		elem->type = APPEND;
	else if (ft_strncmp(elem->str, "<", 3) == 0)
		elem->type = INPUT;
	else if (ft_strncmp(elem->str, "<<", 3) == 0)
		elem->type = CINPUT;
	else if (ft_strncmp(elem->str, "|", 3) == 0)
		elem->type = PIPE;
	else if (elem->prev == NULL || elem->prev->type >= TRUNC)
		elem->type = CMD;
	else
		elem->type = ARG;
}

int	check_type(t_elem *elem, int type)
{
	if (elem && elem->type == type)
		return (1);
	else
		return (0);
}

int	check_types(t_elem *elem, char *types)
{
	if (ft_strchr(types, ' ') && check_type(elem, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && check_type(elem, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && check_type(elem, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && check_type(elem, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && check_type(elem, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && check_type(elem, INPUT))
		return (1);
	else if (ft_strchr(types, 'C') && check_type(elem, CINPUT))
		return (1);
	else if (ft_strchr(types, 'P') && check_type(elem, PIPE))
		return (1);
	return (0);
}

int	get_type(t_elem *elem)
{
	if (check_type(elem, TRUNC))
		return (FILE_TRUNC);
	else if (check_type(elem, APPEND))
		return (FILE_APPEND);
	else if (check_type(elem, INPUT))
		return (FILE_INPUT);
	else if (check_type(elem, CINPUT))
		return (FILE_CINPUT);
	else
		return (DEFAULT);
}
