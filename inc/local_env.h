/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 20:07:32 by nomargen          #+#    #+#             */
/*   Updated: 2022/06/23 18:08:30 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LOCAL_ENV_H
# define LOCAL_ENV_H

# include <stdlib.h>
# include "../lib/libft/libft.h"
# include <stdio.h>

# define ENV_STR_MASK	(0b00000001)
# define EXP_STR_MASK	(0b00000010)
# define PATH_MAS_MASK	(0b00000100)
# define ENV_MAS_MASK	(0b00001000)

typedef struct s_env_lst
{
	char				*key;
	char				*val;
	struct s_env_lst	*next;
}	t_env_lst;

typedef struct s_local_env
{
	t_env_lst	*env_lst;
	char		*env_str;
	char		*exp_str;
	char		**path_mas;
	char		**env_mas;
	char		is_valid_flag;
}	t_local_env;

typedef struct s_dif_ind
{
	int	index;
	int	dif;
}	t_dif_ind;

int			init_local_env(t_local_env *loc_env, char **env_ptr);
char		*get_env_val(t_local_env *loc_env, char *key, t_env_lst **env_list);
t_env_lst	*set_env_val(t_local_env *loc_env, char *key, char *val);
int			unset_env(t_local_env *local_env, char *key);
int			print_env_fd(t_local_env *loc_env, int fd);
int			print_export_fd(t_local_env *loc_env, int fd);
int			update_env_str(t_local_env *loc_env);
int			update_exp_str(t_local_env *loc_env);
int			update_path_mas(t_local_env *local_env);
int			update_env_mas(t_local_env *local_env);
int			free_env(t_local_env *loc_env);
t_env_lst	*env_lst_add_front(t_env_lst **head_env, char *key, char *val);
int			copy_env(t_local_env *loc_env, char **env_ptr);
char		*create_exp_str(char *key, char *val);
char		*create_env_str(char *key, char *val);
int			free_ptr_mas(char **mas);

#endif