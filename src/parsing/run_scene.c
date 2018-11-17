/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:32:34 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 14:32:35 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#define OPEN_TAG 1
#define CLOSE_TAG 2

/**
 * #include <sys/types.h>
 * #include <sys/uio.h>
 * #include <unistd.h>
*/

static char	*ft_strjoin_mod(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&a);
	return (str);
}

static char	*ft_strjoin_mod_rew(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&b);
	return (str);
}

int			find_tag_position(char *scene, char **to_find, int start_from)
{
	char	*current_ptr;
	char	*start_ptr;
	char	*occure_ptr;
	int		i;

	start_ptr = &scene[start_from];
	current_ptr = start_ptr;
	while (*current_ptr != '\0')
	{
		occure_ptr = current_ptr;
		if (*current_ptr == (*to_find)[0])
		{
			i = 0;
			while (*current_ptr == (*to_find)[i])
			{
				i++;
				if ((*to_find)[i] == '\0')
					return (start_from + (occure_ptr - start_ptr));
				current_ptr++;
			}
		}
		current_ptr++;
	}
	return (-1);
}

int			match_tag(char *scene, char *tag, int start_from, int mod)
{
	char	*to_find;
	int		position;

	if (mod == CLOSE_TAG)
	{
		to_find = ft_strjoin_mod_rew("</", ft_strjoin(tag, ">"));
	}
	if (mod == OPEN_TAG)
	{
		to_find = ft_strjoin_mod_rew("<", ft_strjoin(tag, ">"));
	}
	position = find_tag_position(scene, &to_find, start_from);
	ft_strdel(&to_find);
	return (position);
}

char		*get_tpl_obj(char *obj)
{
	int		fig_obj_fd;
	char 	*obj_tpl;
	char	*line;
	// char	*path;

	line = ft_strnew(0);
	obj_tpl = ft_strnew(0);
	// path = ft_strjoin(obj, OBJ_TPL_EXTENTION);
	// path = ft_strjoin_mod_rew(OBJ_TPL_PATH, path);
	fig_obj_fd = open("src/scenes/objects/sphere.scene.obj", O_RDONLY);
	if (fig_obj_fd > 0)
	{
		
		while (get_next_line(fig_obj_fd, &line) > 0)
		{
			line = ft_strjoin_mod(line, "\n");
			obj_tpl = ft_strconcat(obj_tpl, line);
		}
		close(fig_obj_fd);
	}
	ft_strdel(&line);
	// ft_strdel(&path);
	return (obj_tpl);
}

void		cut_params(char *scene, int com_fd)
{
	int		i = 0;
	char	*obj;
	
	while (scene[i] != '\0')
	{
		if (scene[i] == '<')
		{
			char *new = ft_strsub(scene, i+1, (ft_strstr(&scene[i], ">") - (&scene[i] + 1)));
			if (!ft_strstr(new, "/"))
			{
				int		start = match_tag(scene, new, i, OPEN_TAG);
				char *result = ft_strsub(scene, start + ft_strlen(new) + 2, match_tag(scene, new, start, CLOSE_TAG) - (start + ft_strlen(new) + 2));
				obj = get_tpl_obj(new);
				// ft_putendl_fd(result, com_fd);
				ft_strdel(&result);
				ft_strdel(&obj);
			}
			ft_strdel(&new);
		}
		i++;
	}
	
}

int			run_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*txt_scene;
	int		com_fd;
	char	*comp_fn;

	line = NULL;
	fd = open(file, O_RDWR);
	comp_fn = ft_strjoin(file, ".obj");
	com_fd = open(comp_fn, O_CREAT | O_RDWR | O_TRUNC , 0755);
	
	warning(CAMERA_DO_NOT_EXIST);
	if (read(fd, NULL, 0) < 0)
	{
		error(NO_FILE);
		return (FALSE);
	}
	txt_scene = ft_strnew(0);
	if (scene == NULL)
	{
		printf("BEGIN\n");
	}
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoin_mod(line, "\n");
		txt_scene = ft_strconcat(txt_scene, line);
	}
	
	cut_params(txt_scene, com_fd);
	ft_strdel(&txt_scene);
	ft_strdel(&comp_fn);
	ft_strdel(&line);
	return (TRUE);
}
