#include "../../include/parsing.h"

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
		set_warning_message("\" can't be found\n");
		warning(NO_WARNINGS);
	}
	ft_strdel(&name);
	if (coord)
		ft_strdel(&coord);
	free(tmp);
	ft_putendl(param.name);
	// param_tag.close = match_tag(obj, param.name, param_tag.open, CLOSE_TAG);
}
