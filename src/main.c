/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:32:32 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:32:33 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/rt.h"
#include "./../include/parsing.h"
#include "./../include/warning.h"

int	main(int ac, char *av[])
{
	t_scene		*scene;
	if (ac > 0)
	{	
		set_warning_file(av[1]);
		if (run_scene(av[1]))
		{
			processing_scene(&scene);
		}
	}
	system("leaks rt | grep -iE \"leak\"");
	return (0);
}
