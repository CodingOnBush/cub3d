#include "../inc/cub3d.h"

static int	ft_get_path(t_env *env, char **split)
{
	t_img	*img;

	if (ft_strcmp(split[0], "NO") == 0)
		img = &(env->data.no);
	else if (ft_strcmp(split[0], "SO") == 0)
		img = &(env->data.so);
	else if (ft_strcmp(split[0], "WE") == 0)
		img = &(env->data.we);
	else if (ft_strcmp(split[0], "EA") == 0)
		img = &(env->data.ea);
	else
		return (ft_err("Failed to get path", FAILURE));
	if (img->path)
		return (ft_err("Path already set", FAILURE));
	img->path = ft_strdup(split[1]);
	if (!img->path)
		return (ft_err("Failed to get path", FAILURE));
	return (SUCCESS);
}

static int	ft_get_color(t_env *env, char **split)
{
	t_color	*color;

	if (!ft_strcmp(split[0], "C"))
		color = &(env->data.ceil);
	else if (!ft_strcmp(split[0], "F"))
		color = &(env->data.floor);
	else
		return (ft_err("Failed to get color", FAILURE));
	if (color->r != -1 || color->g != -1 || color->b != -1)
		return (ft_err("Color already set", FAILURE));
	color->r = ft_atoicolor(split[1]);
	color->g = ft_atoicolor(split[2]);
	color->b = ft_atoicolor(split[3]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		return (ft_init_color(color), FAILURE);
	return (SUCCESS);
}

static int	ft_parse_line(t_env *env, char *line)
{
	char	**split;
	int		ret;

	split = NULL;
	ret = FAILURE;
	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		split = ft_splitmore(line, " ,");
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		split = ft_splitmore(line, " ");
	if (ft_splitlen(split) == 4)
		ret = ft_get_color(env, split);
	else if (ft_splitlen(split) == 2)
		ret = ft_get_path(env, split);
	return (ft_free_split(split), ret);
}

int	ft_parse_map_infos(t_env *env, int fd)
{
	char	*line;
	int		i;

	while (ft_is_datafull(env) == NO)
	{
		line = get_next_line(fd);
		if (!line)
			return (FAILURE);
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '\n' || line[i] != '\0')
		{
			if (ft_parse_line(env, &line[i]) == FAILURE)
				return (free(line), FAILURE);
		}
		free(line);
	}
	return (SUCCESS);
}
