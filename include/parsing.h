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
# define TRUE 1
# define FALSE 0

int		run_scene(char *file, t_scene *sc);
int		read_scene_file(char *file);

#endif
