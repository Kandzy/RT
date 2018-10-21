/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:09:21 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:09:23 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "position.h"
# include "color.h"
# include "rotation.h"

typedef struct		s_object
{
	char			*object;
	t_color			color;
	int				incline;
	int				radius;
	int				height;
	t_position		pos;
	t_rotation		angle;
}					t_object;

#endif
