/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:46:16 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 19:07:15 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

t_exec	*create_exec(t_elem *elem, int *index_inout, int *i)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->next = NULL;
	if (!exec)
		return (NULL);
	exec->cmd_str = NULL;
	exec->cmd_args = malloc(sizeof(char *) * (get_arg_count(elem) + 1));
	exec->cmd_args[get_arg_count(elem)] = NULL;
	exec->inout_cnt = get_redir_count(elem);
	exec->inout = malloc(sizeof(t_inout) * (exec->inout_cnt + 1));
	*index_inout = 0;
	exec->inout[exec->inout_cnt].type = DEFAULT;
	*i = 0;
	return (exec);
}

t_exec	*create_exec_pipe(t_elem *elem, t_exec **exec_old, int *index_inout,
	int *i)
{
	t_exec	*exec;

	(*exec_old)->next = malloc(sizeof(t_exec));
	if (!((*exec_old)->next))
		return (NULL);
	exec = (*exec_old)->next;
	exec->next = NULL;
	exec->cmd_str = NULL;
	exec->inout_cnt = get_redir_count(elem->next);
	exec->inout = malloc(sizeof(t_inout) * (exec->inout_cnt + 1));
	*index_inout = 0;
	exec->inout[exec->inout_cnt].type = DEFAULT;
	exec->inout[(*index_inout)++].type = FILE_PIPE_IN;
	exec->cmd_args = malloc(sizeof(char *)
			* (get_arg_count(elem->next) + 1));
	exec->cmd_args[get_arg_count(elem->next)] = NULL;
	*i = 0;
	return (exec);
}

void	comp_part(t_elem **elem, t_exec **exec, int *index_inout, int *i)
{
	if (check_type(*elem, CMD))
		(*exec)->cmd_str = (*elem)->str;
	else if (check_types(*elem, "TAIC"))
	{
		(*exec)->inout[*index_inout].name = (*elem)->next->str;
		(*exec)->inout[(*index_inout)++].type = get_type(*elem);
		*elem = (*elem)->next;
	}
	else
		(*exec)->cmd_args[(*i)++] = (*elem)->str;
}

t_exec	*comp(t_elem *elem)
{
	t_exec	*exec;
	t_exec	*start;
	int		i;
	int		index_inout;

	exec = NULL;
	start = exec;
	while (elem)
	{
		if (elem->prev == NULL)
		{
			exec = create_exec(elem, &index_inout, &i);
			start = exec;
		}
		if (check_type(elem, PIPE))
		{
			exec->inout[index_inout].type = FILE_PIPE_OUT;
			exec = create_exec_pipe(elem, &exec, &index_inout, &i);
		}
		else
			comp_part(&elem, &exec, &index_inout, &i);
		elem = elem->next;
	}
	return (start);
}

void	parse(char *line, t_local_env *local_env, int *result, int *exit)
{
	t_elem	*temp;
	t_elem	*elem;
	t_exec	*exec;

	exec = NULL;
	elem = NULL;
	line = space_line(line, local_env, *result);
	elem = get_elems(line);
	free(line);
	args_sort(&elem);
	temp = elem;
	while (temp)
	{
		if (check_type(temp, ARG))
			type_arg(temp);
		temp = temp->next;
	}
	if (elem != NULL && line_check(elem))
		exec = comp(elem);
	*result = execute_commands(exec, local_env, exit);
	free_struct(&exec, &elem);
}
