/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:17:18 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/22 19:17:35 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_TYPES_H
# define PIPEX_TYPES_H

typedef enum e_std_fd
{
	STDIN = 0,
	STDOUT,
	STDERR
}	t_std_fd;

typedef enum e_cmd_type
{
	CMD_ECHO = 0,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_NOT_FOUND,
	CMD_FROM_DIR,
	CMD_NOPE
}	t_cmd_type;

typedef enum e_inout_type
{
	DEFAULT = 0,
	FILE_TRUNC,
	FILE_APPEND,
	FILE_PIPE_OUT,
	FILE_INPUT,
	FILE_CINPUT,
	FILE_PIPE_IN
}	t_inout_type;

typedef struct s_inout
{
	char			*name;
	t_inout_type	type;
}	t_inout;

typedef struct s_exec
{
	char			*cmd_str;
	char			**cmd_args;
	int				inout_cnt;
	t_inout			*inout;
	struct s_exec	*next;
}	t_exec;

typedef struct s_cmd_param
{
	int			in_fd;
	int			out_fd;
	char		*cmd_dir;
	char		*cmd_str;
	char		**cmd_args;
	t_cmd_type	cmd_type;
}	t_cmd_param;

#endif