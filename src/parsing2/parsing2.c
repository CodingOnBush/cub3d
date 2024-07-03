#include "../inc/cub3d.h"

static int	ft_parse_map(t_env *env, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("line: [%s]\n", line);
		free(line);
	}
	return (SUCCESS);
}

int	ft_parsing2(t_env *env, char *filepath)
{
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_err("Impossible to open this file", FAILURE);
		printf("[%s]\n", filepath);
		return (FAILURE);
	}
	if (ft_parse_map_infos(env, fd) == FAILURE)
		return (close(fd), FAILURE);
	printf("Map infos parsed successfully\n");
	if (ft_parse_map(env, fd) == FAILURE)
		return (close(fd), FAILURE);
	close(fd);
	return (FAILURE);
}
