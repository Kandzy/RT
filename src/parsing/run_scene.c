#include "../../include/parsing.h"
#include "../../include/external.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static char	*ft_strjoin_mod(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&a);
	return (str);
}

int		run_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*txt_scene;
	

	line = NULL;
	txt_scene = ft_strjoin(txt_scene, "");
	fd = open(file, O_RDWR);
	printf("%s\n", file);
	if (scene == NULL)
	{
		printf("BEGIN\n");
	}
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoin_mod(line, "\n");
		txt_scene = ft_strconcat(txt_scene, line);
	}
	printf("%s\n", txt_scene);
	ft_strdel(&line);
	return (TRUE);
}