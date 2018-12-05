/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:54:28 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/05 16:54:29 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char		*ft_strjoin_mod(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&a);
	return (str);
}

char		*ft_strjoin_mod_rew(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&b);
	return (str);
}

int			array_length(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return i;
}