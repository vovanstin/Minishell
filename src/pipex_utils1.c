/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:37:59 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 17:40:50 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

int	print_cinput_warn(char *stop_seq)
{
	ft_putstr_fd("bash: warning: here-document\
	delimited by end-of-file (wanted `", STDERR);
	ft_putstr_fd(stop_seq, STDERR);
	ft_putstr_fd("')\n", STDERR);
	return (1);
}

int	process_cinput(int target_fd, char *stop_seq)
{
	char	*line;
	int		init_iter;

	init_iter = 1;
	while (init_iter || (line != NULL && ft_strcmp(line, stop_seq) != 0))
	{
		if (!init_iter)
		{
			ft_putstr_fd(line, target_fd);
			ft_putstr_fd("\n", target_fd);
			free (line);
		}
		else
			init_iter = 0;
		line = readline("> ");
	}
	if (line == NULL)
		print_cinput_warn(stop_seq);
	else
		free (line);
	return (0);
}

int	process_files_input(t_inout inout, int cin_pipe[2], t_cmd_param *cmd_param)
{
	if (inout.type == FILE_CINPUT)
	{
		if (pipe(cin_pipe) != 0)
		{
			perror("Pipe!");
			return (0);
		}
		process_cinput(cin_pipe[1], inout.name);
		close(cin_pipe[1]);
		cmd_param->in_fd = cin_pipe[0];
	}
	else if (!safe_open(&cmd_param->in_fd, inout.name, O_RDONLY, 0))
		return (0);
	return (1);
}

int	get_in_fd(t_inout inout, t_inout *inout_arr, t_cmd_param *cmd_param,
		int (*pipe_fd)[2])
{
	int	i;
	int	cin_pipe[2];

	if (cmd_param == NULL || pipe_fd == NULL)
		return (0);
	if (inout.type != FILE_PIPE_IN)
	{
		if (process_files_input(inout, cin_pipe, cmd_param) == 0)
			return (0);
	}
	else
	{
		i = 1;
		while (inout_arr[i].type != DEFAULT)
		{
			if (inout_arr[i].type >= FILE_INPUT)
			{
				close((*pipe_fd)[0]);
				break ;
			}
			i++;
		}
		cmd_param->in_fd = (*pipe_fd)[0];
	}
	return (1);
}

char	*find_cmd_dir(char **path, char *cmd_str, t_local_env *loc_env)
{
	char	*tmp;
	char	*dir;
	int		i;

	i = 0;
	dir = NULL;
	if (ft_strchr(cmd_str, '/') != NULL)
	{
		dir = get_full_dir(cmd_str, loc_env);
		if (access(dir, 0) != 0)
		{
			free(dir);
			dir = NULL;
		}
	}
	while (path[i] && dir == NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		dir = ft_strjoin(tmp, cmd_str);
		free(tmp);
		if (access(dir, 0) != 0)
			free_n_null_ptr(&dir);
		i++;
	}
	return (dir);
}
