/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:35:00 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:35:01 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"
# include "external.h"
# include "warning.h"
# include "error.h"
# define OBJ_TPL_PATH "src/scenes/objects/"
# define OBJ_TPL_EXTENTION ".scene.obj"
# define OPEN_TAG 1
# define CLOSE_TAG 2
# define TRUE 1
# define FALSE 0

typedef struct		s_tags
{
	int				open;
	int				close;
	char			*in_tag;
	char			*name;
	char			*obj_tpl;
}					t_tags;

typedef struct		s_param_val
{
	char			*name;
	char			*val;
}					t_param_val;

int		match_tag(char *scene, char *tag, int start_from, int mod);
char	*get_tpl_obj(char *obj);
int		find_tag_position(char *scene, char **to_find, int start_from);
void	set_param_in_tpl(t_param_val param, char **obj);
void	cut_params(char *scene, int com_fd);
int		read_scene_file(char *file);
int		run_scene(char *file, t_scene *sc);


/*
** Additional functionality
*/

char		*ft_strjoin_mod(char *a, char *b);
char		*ft_strjoin_mod_rew(char *a, char *b);
int			array_length(char **array);

#endif
