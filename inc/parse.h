/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:30:52 by cjanetta          #+#    #+#             */
/*   Updated: 2022/06/23 23:05:56 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define CINPUT 6
# define PIPE 7

# include "pipex.h"

typedef struct s_elem
{
	char			*str;
	int				type;
	struct s_elem	*prev;
	struct s_elem	*next;
}	t_elem;

void	type_arg(t_elem *elem);
int		check_type(t_elem *elem, int type);
int		check_types(t_elem *elem, char *types);
int		get_type(t_elem *elem);
t_elem	*prev_sep(t_elem *elem, int skip);
int		is_last_valid_arg(t_elem *elem);
t_elem	*get_elems(char *line);
char	*gkl(char *line, int *i);
int		quotes(char *line, int index);
int		is_sep(char *line, int i);
int		get_count(char *line, int *i, t_local_env *env, char *result);
char	*space_line(char *line, t_local_env *env, int result);
int		line_check(t_elem *elem);
void	change_elems_pos(t_elem **elem, t_elem **prev, t_elem **elemm);
void	args_sort(t_elem **elemm);
int		get_arg_count(t_elem *elem);
int		get_redir_count(t_elem *elem);
void	free_struct(t_exec **exec, t_elem **elem);
void	parse(char *line, t_local_env *local_env, int *result, int *exit);
void	handle_ctrl_c(int i);
void	handle_ctrl_bs(int i);
void	ft_skip_space(const char *str, int *i);
int		ft_is_white_space(const char c);

#endif