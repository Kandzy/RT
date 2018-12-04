/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:58:07 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 10:58:09 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARNING_H
# define WARNING_H

# include "external.h"

# define NO_WARNINGS 0
# define CUSTOM_WARNING 1
# define CAMERA_DO_NOT_EXIST 2
# define TAG_NOT_CLOSED 3
# define INPUT_NOT_CORRECT 4
# define LIGHT_DO_NOT_EXIST 6
# define NO_TPL_OBJECT 9

typedef struct		s_warning
{
	char			*message;
	int				line;
}					t_warning;

void		scene_tags_warning(int warning_code);
void		light_tag_warning(int warning_code);
void		camera_tags_warning(int warning_code);
void		no_object_warning(int warning_code);
void		warning_tag_not_closed(char *tag);
void		not_correct_input(int warning_code);
void		no_closing_tag_warning(int warning_code);
void		warning(int warning_code);
void		set_warning_message(char *param);
void		set_warning_line(int line);
int			get_warning_line();

#endif
