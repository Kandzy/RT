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

void	get_tag_inner_info(char *scene_txt, t_scene **scene, int i)
{
	t_tags	tag;
	
	tag.name = ft_strsub(scene_txt, i + 1,
			(int)(ft_strstr(&scene_txt[i], ">") - (&scene_txt[i] + 1)));
	if (!ft_strstr(tag.name, "/"))
	{
		tag.open = match_tag(scene_txt, tag.name, i, OPEN_TAG);
		tag.close = match_tag(scene_txt, tag.name, tag.open, CLOSE_TAG);
		if (tag.close == -1)
		{
			warning_tag_not_closed(tag.name);
			warning(TAG_NOT_CLOSED);
		}
		if (tag.close && ft_strcmp(tag.name, "scene") && ft_strcmp(tag.name, "object"))
			tag.in_tag = ft_strsub(scene_txt, tag.open + ft_strlen(tag.name) + 2,
			tag.close - (tag.open + ft_strlen(tag.name) + 2));
		if (tag.close && tag.in_tag && ft_strcmp(tag.name, "scene") && ft_strcmp(tag.name, "object"))
		{
			get_tag_inner_info(scene_txt, scene, 0);
			// printf("%s\n", tag.in_tag);
			ft_strdel(&tag.in_tag);
		}
	}
	// printf("%s\n", tag.name);
}

void	processing_objects(char *scene_txt, t_scene **scene)
{
	int		i;

	i = 0;
	// printf("%s\n",scene_txt);
	while (scene_txt[i] != '\0')
	{
		
		if (scene_txt[i] == '<')
		{
			get_tag_inner_info(scene_txt, scene, i);
		}
		i++;
	}
}

void	processing_scene(t_scene **scene)
{
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
	processing_objects(scene_txt, scene);
	// printf("%s\n",scene_txt);
	ft_strdel(&line);
	ft_strdel(&scene_txt);
	close(scene_fd);
}

int	main(int ac, char *av[])
{
	t_scene		*scene;
	if (ac > 0)
	{		
		if (run_scene(av[1]))
		{
			set_warning_file(av[1]);
			processing_scene(&scene);
		}
	}
	system("leaks rt | grep -iE \"leak\"");
	return (0);
}
