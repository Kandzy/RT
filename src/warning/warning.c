/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:09:30 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:09:30 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		tag_not_closed(int warning_code)
{
 	scene_tags_warning(warning_code);
	camera_tags_warning(warning_code);
	light_tag_warning(warning_code);
}

void		warning(int warning_code)
{
	tag_not_closed(warning_code);
}