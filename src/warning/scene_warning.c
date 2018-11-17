/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_warning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:05:48 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:05:49 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		scene_tags_warning(int warning_code)
{
	if (warning_code == SCENE_TAG_NOT_CLOSED)
		ft_putstr("\033[;33mWARNING: Tag <scene> not closed.\033[0m\n");
	if (warning_code == SCENE_TAG_NOT_OPENED)
		ft_putstr("\033[;33mWARNING: Scene closing tag was occured </scene>, scene\
 open tag <scene> do not exist.\033[0m\n");
}

