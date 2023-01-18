/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:54:35 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 19:10:20 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int	line_check(t_elem *elem)
{
	while (elem)
	{
		if (check_types(elem, "TAICP")
			&& (!elem->next || check_types(elem->next, "TAICP")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			if (elem->next)
				ft_putstr_fd(elem->next->str, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}

void	change_elems_pos(t_elem **elem, t_elem **prev, t_elem **elemm)
{
	while (is_last_valid_arg(*prev) == 0)
		*prev = (*prev)->prev;
	(*elem)->prev->next = (*elem)->next;
	if ((*elem)->next)
		(*elem)->next->prev = (*elem)->prev;
	(*elem)->prev = *prev;
	if (*prev)
		(*elem)->next = (*prev)->next;
	else
		(*elem)->next = *elemm;
	if (!(*prev))
		*prev = *elem;
	(*prev)->next->prev = *elem;
	if (!((*elemm)->prev))
		(*prev)->next = *elem;
	if ((*elemm)->prev)
		(*elemm) = (*elemm)->prev;
}

void	args_sort(t_elem **elemm)
{
	t_elem	*elem;
	t_elem	*prev;

	elem = *elemm;
	while (elem)
	{
		prev = prev_sep(elem, 0);
		if (check_type(elem, ARG) && check_types(prev, "TAIC"))
			change_elems_pos(&elem, &prev, elemm);
		elem = elem->next;
	}
}

int	get_arg_count(t_elem *elem)
{
	int	count;

	count = 0;
	while (elem && !check_type(elem, PIPE))
	{
		if (check_type(elem, ARG) || check_type(elem, EMPTY))
			count++;
		elem = elem->next;
	}
	return (count);
}

int	get_redir_count(t_elem *elem)
{
	int	count;

	count = 0;
	while (elem && !check_type(elem, PIPE))
	{
		if (check_types(elem, "TAIC"))
			count++;
		if (check_type(elem->prev, PIPE))
			count++;
		elem = elem->next;
	}
	if (check_type(elem, PIPE))
		count++;
	return (count);
}
