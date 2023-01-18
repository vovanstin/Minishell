/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:24:39 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/24 00:14:29 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

int	close_fds(t_cmd_param *cmd_param, int *pipe_fd)
{
	if (cmd_param == NULL || pipe_fd == NULL)
		return (0);
	if (cmd_param->in_fd != 0)
		close(cmd_param->in_fd);
	if (cmd_param->out_fd != 1)
		close(cmd_param->out_fd);
	free(cmd_param->cmd_dir);
	cmd_param->cmd_dir = NULL;
	return (1);
}

int	child(char **args, t_cmd_param *cmd_param, t_local_env *local_env)
{
	dup2(cmd_param->in_fd, 0);
	dup2(cmd_param->out_fd, 1);
	update_env_mas(local_env);
	execve(cmd_param->cmd_dir, args, local_env->env_mas);
	perror(cmd_param->cmd_dir);
	if (cmd_param->cmd_dir)
		free(cmd_param->cmd_dir);
	return (0);
}

int	init_cmd_param(t_cmd_param *cmd_param)
{
	if (cmd_param == NULL)
		return (0);
	cmd_param->in_fd = STDIN;
	cmd_param->out_fd = STDOUT;
	cmd_param->cmd_dir = NULL;
	cmd_param->cmd_str = NULL;
	cmd_param->cmd_args = NULL;
	cmd_param->cmd_type = CMD_NOT_FOUND;
	return (1);
}

int	cmd_from_dir(t_cmd_param *cmd_param, t_local_env *local_env)
{
	int		status;
	char	**args;

	g_pid = fork();
	if (g_pid == 0)
	{
		args = add_zero_arg(cmd_param->cmd_args, cmd_param->cmd_str);
		return (child(args, cmd_param, local_env));
	}
	else if (g_pid > 0)
	{
		waitpid(g_pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	else
	{
		perror("Fork!");
		return (0);
	}
	return (status);
}

int	execute_commands(t_exec *exec, t_local_env *local_env, int *exit)
{
	int			status;
	int			pipe_fd[2];
	t_cmd_param	cmd_param;

	if (exec == NULL || local_env == NULL)
		return (0);
	status = EXIT_SUCCESS;
	while (exec && status == EXIT_SUCCESS)
	{
		init_cmd_param(&cmd_param);
		status = fill_cmd_param(exec, &cmd_param, &pipe_fd, local_env);
		if (cmd_param.cmd_type == CMD_NOT_FOUND && !status)
		{
			check_for_valid_path(&cmd_param, local_env);
			print_cmd_not_fnd(cmd_param.cmd_str);
			status = EXIT_FILE_NOT_FOUND;
		}
		else if (cmd_param.cmd_type == CMD_FROM_DIR)
			status = cmd_from_dir(&cmd_param, local_env);
		else if (cmd_param.cmd_type != CMD_NOPE)
			status = buildtin_cmd(&cmd_param, local_env, exit, exec);
		close_fds(&cmd_param, pipe_fd);
		exec = exec->next;
	}
	return (status);
}
