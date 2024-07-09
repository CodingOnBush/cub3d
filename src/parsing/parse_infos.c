/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:22:49 by momrane           #+#    #+#             */
/*   Updated: 2024/07/09 15:51:25 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_get_path(t_env *env, char *line, char *path)
{
	char	*nl;
	int		id;

	if ((path && path[0] == '\0') || !line)
		return (ft_err("Failed to get path", FAILURE));
	if (ft_strncmp(line, "NO ", 3) == 0)
		id = NORTH;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		id = SOUTH;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		id = WEST;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		id = EAST;
	else
		return (ft_err("Failed to get path", FAILURE));
	if (env->img[id].path)
		return (ft_err("Path already set", FAILURE));
	env->img[id].path = ft_strdup(path);
	if (!env->img[id].path)
		return (ft_err("Failed to get path", FAILURE));
	nl = ft_strchr(env->img[id].path, '\n');
	if (nl)
		*nl = '\0';
	return (SUCCESS);
}

static int	ft_get_color(t_env *env, char **split)
{
	int	color;

	if (!ft_strcmp(split[0], "C"))
		color = CEIL;
	else if (!ft_strcmp(split[0], "F"))
		color = FLOOR;
	else
		return (ft_err("Invalid color line", FAILURE));
	if (env->colors[color][R] != -1 || env->colors[color][G] != -1
		|| env->colors[color][B] != -1)
		return (ft_err("Color already set", FAILURE));
	env->colors[color][R] = ft_atoicolor(split[1]);
	env->colors[color][G] = ft_atoicolor(split[2]);
	env->colors[color][B] = ft_atoicolor(split[3]);
	if (env->colors[color][R] == -1 || env->colors[color][G] == -1
		|| env->colors[color][B] == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_parse_line(t_env *env, char *line)
{
	char	**split;
	int		ret;
	int		i;

	split = NULL;
	ret = FAILURE;
	if (ft_is_color_line(line) == YES)
		split = ft_splitmore(line, " ,");
	else if (ft_is_texture_line(line) == YES)
	{
		i = 3;
		while (line[i] == ' ')
			i++;
	}
	else
		return (ft_err("Not enough or invalid infos", FAILURE));
	if (ft_is_color_line(line) == YES && ft_splitlen(split) == 4)
		ret = ft_get_color(env, split);
	else if (ft_is_texture_line(line) == YES)
		ret = ft_get_path(env, line, &line[i]);
	else
		return (ft_free_split(split), ft_err("Line not conform", FAILURE));
	return (ft_free_split(split), ret);
}

static int	ft_parse_map_infos(t_env *env, int fd)
{
	char	*line;
	int		i;

	while (ft_all_data_collected(env) == NO)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (ft_all_data_collected(env) == NO)
				ft_err("Not enough infos", FAILURE);
			return (FAILURE);
		}
		env->mapstart++;
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '\0' && ft_parse_line(env, &line[i]) == FAILURE)
			return (free(line), FAILURE);
		free(line);
	}
	return (SUCCESS);
}

int	ft_parse_infos(t_env *env, char *cubfile)
{
	int	fd;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
	{
		ft_err_title();
		perror(cubfile);
		return (FAILURE);
	}
	if (ft_parse_map_infos(env, fd) == FAILURE)
	{
		close(fd);
		return (FAILURE);
	}
	if (ft_set_map_size(env, fd) == FAILURE)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
