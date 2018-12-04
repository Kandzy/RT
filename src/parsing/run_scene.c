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

int			object_exists(char *obj, int fd)
{
	if (!ft_strcmp(obj, "scene"))
		return 1;
	if (fd <= 0)
	{
		set_warning_message("Object <");
		set_warning_message(obj);
		set_warning_message(">");
		set_warning_message(" undefined\n");
		return (0);
	}
	return 1;
}

char		*get_tpl_obj(char *obj)
{
	int		fig_obj_fd;
	char 	*obj_tpl;
	char	*line;
	char	*path;

	obj_tpl = ft_strnew(0);
	path = ft_strjoin(obj, OBJ_TPL_EXTENTION);
	path = ft_strjoin_mod_rew(OBJ_TPL_PATH, path);
	fig_obj_fd = open(path, O_RDONLY);
	if (!object_exists(obj, fig_obj_fd))
		warning(NO_TPL_OBJECT);
	if (fig_obj_fd > 0)
	{
		while (get_next_line(fig_obj_fd, &line) > 0)
		{
			line = ft_strjoin_mod(line, "\n");
			obj_tpl = ft_strconcat(obj_tpl, line);
		}
		close(fig_obj_fd);
		ft_strdel(&line);
	}
	ft_strdel(&path);
	return (obj_tpl);
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

void		set_param_in_tpl(t_param_val param, char **obj)
{
	t_tags	param_tag;
	char	*name;
	char	**tmp;
	char	*coord;

	coord = NULL;
	name = ft_strtrim(param.name);
	tmp = ft_strsplit(name, '-');
	if (array_length(tmp) == 2)
		coord = tmp[1];
	ft_strdel(&name);
	name = tmp[0];
	param_tag.open = match_tag(*obj, name, 0, OPEN_TAG);
	if (param_tag.open == -1)
	{
		set_warning_message("This parameter \"");
		set_warning_message(name);
		set_warning_message("\" cant be find\n");
		warning(NO_WARNINGS);
	}
	ft_strdel(&name);
	if (coord)
		ft_strdel(&coord);
	free(tmp);
	// param_tag.close = match_tag(obj, param.name, param_tag.open, CLOSE_TAG);
}

void		compile_params(char *to_split_param, char **obj, int nl)
{
	char	**tmp;
	t_param_val	param;
	int		i;
	char	*warning_param;

	set_warning_line(get_warning_line() + nl);
	tmp = ft_strsplit(to_split_param, ':');
	if (array_length(tmp) != 2)
	{
		warning_param = ft_strtrim(tmp[0]);
		printf("%s\n",warning_param);
		set_warning_message("Check your parameter \"");
		set_warning_message(warning_param);
		set_warning_message("...\" for correct input\n");
		warning(INPUT_NOT_CORRECT);
		ft_strdel(&warning_param);
	}
	else {
		param.name = tmp[0];
		param.val = tmp[1];
		set_param_in_tpl(param, obj);
	}
	i = 0;
	while (tmp[i])
	{
		ft_strdel(&tmp[i]);
		i++;
	}
	free(tmp);
	set_warning_line(get_warning_line() - nl);
}


void		parse_object(char *src, char *objname, char *obj, int com_fd)
{
	int			i;
	char		**params;
	int			nl;
	int			j;
	int			tmp_nl;

	nl = 0;
	if (!ft_strcmp(objname, "scene"))
		return ;
	params = ft_strsplit(src, ';');
	ft_putendl_fd(obj, com_fd);

	ft_strdel(&params[array_length(params) - 1]);
	i = 0;
	while (params[i])
	{
		j = 0;
		tmp_nl = 0;
		while (params[i][j] != '\0')
		{
			if (ft_isalnum(params[i][j]))
				break ;
			if (params[i][j] == '\n')
				tmp_nl++;
			j++;
		}
		compile_params(params[i], &obj, nl + tmp_nl);
		j = -1;
		while (params[i][++j] != '\0')
			if (params[i][j]== '\n')
				nl++;
		ft_strdel(&(params[i]));
		i++;
	}
	free(params);
}

void		tag_info_parse(char *scene, t_tags *tag, int i, int com_fd)
{
	tag->name = ft_strsub(scene, i+1, (ft_strstr(&scene[i], ">") - (&scene[i] + 1)));
	if (!ft_strstr(tag->name, "/"))
	{
		tag->open = match_tag(scene, tag->name, i, OPEN_TAG);
		tag->close = match_tag(scene, tag->name, tag->open, CLOSE_TAG);
		if (tag->close == -1)
		{
			warning_tag_not_closed(tag->name);
			warning(TAG_NOT_CLOSED);
		}
		if (tag->close && ft_strcmp(tag->name, "scene"))
			tag->in_tag = ft_strsub(scene, tag->open + ft_strlen(tag->name) + 2, tag->close - (tag->open + ft_strlen(tag->name) + 2));
		if (ft_strcmp(tag->name, "scene"))
			tag->obj_tpl = get_tpl_obj(tag->name);
		if (tag->close && tag->in_tag && ft_strcmp(tag->name, "scene"))
		{
			parse_object(tag->in_tag, tag->name, tag->obj_tpl, com_fd);
			ft_strdel(&tag->in_tag);
		}
		if (ft_strcmp(tag->name, "scene"))
			ft_strdel(&tag->obj_tpl);
	}
	ft_strdel(&tag->name);
}

void		cut_params(char *scene, int com_fd)
{
	int		i = 0;
	t_tags	tag;

	set_warning_line(1);	
	while (scene[i] != '\0')
	{
		if (scene[i] == '\n')
			set_warning_line(get_warning_line() + 1);
		if (scene[i] == '<')
		{
			tag_info_parse(scene, &tag, i, com_fd);
		}
		i++;
	}
	set_warning_line(0);
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
	ft_putendl_fd("<scene>", com_fd);
	if (read(fd, NULL, 0) < 0)
	{
		error(NO_FILE);
		return (FALSE);
	}
	txt_scene = ft_strnew(0);
	if (scene == NULL)
	{
		printf("scene run\n");
	}
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoin_mod(line, "\n");
		txt_scene = ft_strconcat(txt_scene, line);
	}
	cut_params(txt_scene, com_fd);
	ft_putendl_fd("</scene>", com_fd);
	ft_strdel(&txt_scene);
	ft_strdel(&comp_fn);
	ft_strdel(&line);
	return (TRUE);
}
