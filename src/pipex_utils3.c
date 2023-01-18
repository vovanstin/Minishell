/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:42:02 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/24 00:06:13 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

char	**add_zero_arg(char **argv, char *arg)
{
	int		cnt;
	char	**new;

	if (argv == NULL || arg == NULL)
		return (0);
	cnt = 0;
	while ((argv)[cnt])
		cnt++;
	new = malloc(sizeof(char *) * (cnt + 2));
	if (new == NULL)
		return (0);
	new[0] = ft_strdup(arg);
	while (cnt >= 0)
	{
		new[cnt + 1] = (argv)[cnt];
		cnt--;
	}
	return (new);
}

int	get_open_flag(t_inout_type type)
{
	int	open_flag;

	if (type == FILE_TRUNC)
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	return (open_flag);
}

int	safe_open(int *fd, char *file, int flags, int mode)
{
	int	fd_tmp;

	if (file == NULL || fd == NULL)
		return (0);
	if (*fd > 1)
		close(*fd);
	if (mode == 0)
		fd_tmp = open(file, flags);
	else
		fd_tmp = open(file, flags, mode);
	if (fd_tmp < 0)
	{
		ft_putstr_fd("bash: ", STDERR);
		perror(file);
		return (0);
	}
	*fd = fd_tmp;
	return (1);
}

int	get_out_fd(t_inout inout, t_cmd_param *cmd_param, int (*pipe_fd)[2])
{
	int	open_flag;

	if (cmd_param == NULL || pipe_fd == NULL)
		return (0);
	if (inout.type != FILE_PIPE_OUT)
	{
		open_flag = get_open_flag(inout.type);
		if (!safe_open(&cmd_param->out_fd, inout.name,
				open_flag, 0664))
			return (0);
	}
	else
	{
		if (pipe(*pipe_fd) != 0)
		{
			perror("Pipe!");
			return (0);
		}
		if (cmd_param->out_fd == 1)
			cmd_param->out_fd = (*pipe_fd)[1];
		else
			close((*pipe_fd)[1]);
	}
	return (1);
}
