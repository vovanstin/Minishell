/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:50:00 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 19:18:46 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	handle_ctrl_c(int i)
{
	(void)i;
	write(1, "\n", 1);
	if (g_pid > 0)
		kill(g_pid, SIGKILL);
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_ctrl_bs(int i)
{
	(void)i;
	if (g_pid > 0)
	{
		kill(g_pid, SIGKILL);
		ft_putstr_fd("Quit (core dumped)\n", 1);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int	ft_is_white_space(const char c)
{
	if ((c == ' ' || c == '\t')
		|| (c == '\r' || c == '\v' || c == '\f'))
		return (1);
	else
		return (0);
}
