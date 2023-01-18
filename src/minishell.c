/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:53:59 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 23:41:18 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	free_struct(t_exec **exec, t_elem **elem)
{
	t_exec	*temp;

	while (*exec)
	{
		free((*exec)->inout);
		free((*exec)->cmd_args);
		temp = (*exec)->next;
		free(*exec);
		*exec = temp;
	}
	while (*elem)
	{
		free((*elem)->str);
		if ((*elem)->next)
		{
			*elem = (*elem)->next;
			free((*elem)->prev);
		}
		else
		{
			free(*elem);
			break ;
		}
	}
}

void	init(int *result, int *exit, t_local_env *local_env, char **env)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bs);
	*result = EXIT_SUCCESS;
	*exit = 0;
	(*local_env).env_lst = NULL;
	(*local_env).env_str = NULL;
	(*local_env).exp_str = NULL;
	init_local_env(local_env, env);
}

void	check_pipe(char **input)
{
	char	*temp;
	char	*input2;
	int		i;

	i = ft_strlen(*input) - 1;
	while (i != -1)
	{
		if (ft_is_white_space((*input)[i]))
			i--;
		else if ((*input)[i] == '|')
		{
			temp = *input;
			*input = ft_strjoin(*input, " ");
			free(temp);
			temp = *input;
			input2 = readline("> ");
			*input = ft_strjoin(*input, input2);
			free(temp);
			free(input2);
			i = ft_strlen(*input) - 1;
		}
		else
			break ;
	}
}

int	check_empty_line(char *input)
{
	int		i;

	i = 0;
	while (ft_is_white_space(input[i]))
		i++;
	if ((size_t)i != ft_strlen(input))
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_local_env	local_env;
	int			result;
	int			exit;

	if (argc < 0 || argv == NULL)
		return (0);
	init(&result, &exit, &local_env, env);
	while (exit == 0)
	{
		g_pid = -1;
		input = readline("$> ");
		check_pipe(&input);
		if (!input)
			break ;
		if (check_empty_line(input))
			add_history(input);
		parse(input, &local_env, &result, &exit);
	}
	free_env(&local_env);
	rl_clear_history();
	return (result);
}
