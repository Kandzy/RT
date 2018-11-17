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

# define SCENE_TAG_NOT_CLOSED 1
# define CAMERA_DO_NOT_EXIST 2
# define CAMERA_TAG_NOT_CLOSED 3
# define CAMERA_TAG_NOT_OPENED 4
# define SCENE_TAG_NOT_OPENED 5
# define LIGHT_DO_NOT_EXIST 6
# define LIGHT_TAG_NOT_OPENED 7
# define LIGHT_TAG_NOT_CLOSED 8

void		scene_tags_warning(int warning_code);
void		light_tag_warning(int warning_code);
void		camera_tags_warning(int warning_code);
void		tag_not_closed(int warning_code);
void		warning(int warning_code);

#endif
