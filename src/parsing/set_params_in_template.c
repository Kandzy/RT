/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params_in_template.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 13:45:27 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/22 13:45:29 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void		coord_related_build(char **values, char *inp_val, char *coord)
{
	char	**value_rel_param;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	value_rel_param = ft_strsplit(*values, ',');
	if (!ft_strcmp(coord, "x"))
	{
		if (is_numeric(inp_val))
		{
			tmp = value_rel_param[0];
			value_rel_param[0] = ft_strdup(inp_val);
		}
		else
			not_numeric_warning(inp_val, coord);
	}
	else if (!ft_strcmp(coord, "y"))
	{
		if (is_numeric(inp_val))
		{
			tmp = value_rel_param[1];
			value_rel_param[1] = ft_strdup(inp_val);
		}
		else
			not_numeric_warning(inp_val, coord);
	}
	else if (!ft_strcmp(coord, "z"))
	{
		if (is_numeric(inp_val))
		{
			tmp = value_rel_param[2];
			value_rel_param[2] = ft_strdup(inp_val);
		} else
			not_numeric_warning(inp_val, coord);
	}
	else
	{
		set_warning_message("Unrecognized coordinate '");
		set_warning_message(coord);
		set_warning_message("' please check your input");
		warning(NO_WARNINGS);
		while (i < 3)
			ft_strdel(&value_rel_param[i++]);
		free(value_rel_param);
		return ;
	}
	if (tmp)
		ft_strdel(&tmp);
	ft_strdel(values);
	i = 0;
	*values = ft_strdup("");
	while (i < 3)
	{
		if (i < 2)
			tmp = ft_strjoin(value_rel_param[i], ",");
		else{
			tmp = ft_strjoin(value_rel_param[i], "");
		}
		*values = ft_strjoin_mod(*values, tmp);
		ft_strdel(&tmp);
		ft_strdel(&value_rel_param[i]);
		i++;
	}
	free(value_rel_param);
}

void		rebuild_object(char **obj, t_tags position, t_param_val param, char *coord)
{
	char *obj_1;
	char *obj_2;
	char *values;
	obj_1 = ft_strsub(*obj, 0, position.open + ft_strlen(param.name) + 2);
	obj_2 = ft_strsub(*obj, position.close, ft_strlen(*obj) - position.close);
	values = ft_strsub(*obj, position.open + ft_strlen(param.name) + 2,
	position.close - (position.open + ft_strlen(param.name) + 2));
	if (coord)
	{
		coord_related_build(&values, param.val, coord);
		obj_1 = ft_strjoin_mod(obj_1, values);
	}
	else
	{
		if (check_value(param.val, param.name))
			obj_1 = ft_strjoin_mod(obj_1, param.val);
		else
		{
			obj_1 = ft_strjoin_mod(obj_1, values);
		}
	}
	ft_strdel(obj);
	ft_strdel(&values);
	*obj = ft_strconcat(obj_1, obj_2);
	
}

void		set_param_in_tpl(t_param_val param, char **obj)
{
	t_tags	param_tag;
	char	*name;
	char	**tmp;
	char	*coord;
	
	coord = NULL;
	name = ft_strtrim(param.name);
	ft_strdel(&param.name);
	tmp = ft_strsplit(name, '-');
	if (array_length(tmp) == 2)
		coord = tmp[1];
	ft_strdel(&name);
	param.name = tmp[0];
	param_tag.open = match_tag(*obj, param.name, 0, OPEN_TAG);
	if (param_tag.open == -1)
	{
		set_warning_message("This parameter \"");
		set_warning_message(param.name);
		set_warning_message("\" can't be found\n");
		warning(NO_WARNINGS);
	}
	else
	{
		param_tag.close = match_tag(*obj, param.name, param_tag.open, CLOSE_TAG);
		rebuild_object(obj, param_tag, param, coord);
	}
	if (coord)
		ft_strdel(&coord);
	free(tmp);
	ft_strdel(&param.name);
	ft_strdel(&param.val);
}
