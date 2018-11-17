/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_warning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:05:29 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:05:32 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		camera_tags_warning(int warning_code)
{
	if (warning_code == CAMERA_DO_NOT_EXIST)
		ft_putstr("\033[;33mWARNING: Camera open tag <camera> and close tag \
</camera> do not exist.\033[0m\n");
	if (warning_code == CAMERA_TAG_NOT_CLOSED)
		ft_putstr("\033[;33mWARNING: Camera tag </camera> do not exist.\033[0m\n");
	if (warning_code == CAMERA_TAG_NOT_OPENED)
		ft_putstr("\033[;33mWARNING: Camera closing tag was occured </camera>, camera\
 open tag <camera> do not exist.\033[0m\n");
}
