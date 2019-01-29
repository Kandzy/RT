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

void	processing_scene()
{
	t_scene		*scene;
	int			scene_fd;
	char		*line;
	char		*scene_txt;

	line = NULL;
	scene_txt = ft_strnew(0);
	scene_fd = open("src/scenes/simple.scene.obj", O_RDONLY);
	while (get_next_line(scene_fd, &line) > 0)
	{
		line = ft_strjoin_mod(line, "\n");
		scene_txt = ft_strconcat(scene_txt, line);
	}
	printf("%s\n",scene_txt);
	ft_strdel(&line);
	ft_strdel(&scene_txt);
	close(scene_fd);
}

int	main(int ac, char *av[])
{
	set_warning_file(av[1]);
	if (ac > 0)
	{		
		if (run_scene(av[1]))
		{
			processing_scene();
		}
	}
	system("leaks rt | grep -iE \"leak\"");
	return (0);
}
