/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:22:49 by momrane           #+#    #+#             */
/*   Updated: 2024/07/06 17:09:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoicolor(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		return (ft_err("Sign before color value are not allowed", -1));
	// if (str[i] == '0' && str[i + 1] != '\0')
	// 	return (ft_err("Invalid color value", -1));
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		if (res > 255)
			return (ft_err("Overflow of color value", -1));
		i++;
	}
	if (str[i] != '\0' && str[i] != '\n')
		return (ft_err("Invalid color value", -1));
	return (res);
}

int	ft_is_datafull(t_env *env)
{
	if (!env)
		return (NO);
	// if (env->data.so.path == NULL || env->data.no.path == NULL
	// 	|| env->data.ea.path == NULL || env->data.we.path == NULL)
	// 	return (NO);
	// if (env->data.floor.r == -1 || env->data.floor.g == -1
	// 	|| env->data.floor.b == -1)
	// 	return (NO);
	// if (env->data.ceil.r == -1 || env->data.ceil.g == -1
	// 	|| env->data.ceil.b == -1)
	// 	return (NO);
	if (env->img[NORTH].path == NULL || env->img[SOUTH].path == NULL
		|| env->img[EAST].path == NULL || env->img[WEST].path == NULL)
		return (NO);
	if (env->file.colors[FLOOR][R] == -1 || env->file.colors[FLOOR][G] == -1 || env->file.colors[FLOOR][B] == -1)
		return (NO);
	if (env->file.colors[CEIL][R] == -1 || env->file.colors[CEIL][G] == -1 || env->file.colors[CEIL][B] == -1)
		return (NO);
	// printf("data is full\n");
	return (YES);
}

static int	ft_get_path(t_env *env, char **split)
{
	int		id;
	char	*nl;

	if (!split || !split[0] || !split[1])
		return (ft_err("Failed to get path", FAILURE));
	if (ft_strcmp(split[0], "NO") == 0)
		id = NORTH;
	else if (ft_strcmp(split[0], "SO") == 0)
		id = SOUTH;
	else if (ft_strcmp(split[0], "WE") == 0)
		id = WEST;
	else if (ft_strcmp(split[0], "EA") == 0)
		id = EAST;
	else
		return (ft_err("Failed to get path", FAILURE));
	if (env->img[id].path)
		return (ft_err("Path already set", FAILURE));
	env->img[id].path = ft_strdup(split[1]);
	if (!env->img[id].path)
		return (ft_err("Failed to get path", FAILURE));
	nl = ft_strchr(env->img[id].path, '\n');
	if (nl)
		*nl = '\0';
	// env->file.count++;
	return (SUCCESS);
}

static int	ft_get_color(t_env *env, char **split)
{
	// t_color	*color;
	int		color;

	if (!ft_strcmp(split[0], "C"))
		color = CEIL;
	else if (!ft_strcmp(split[0], "F"))
		color = FLOOR;
	else
		return (ft_err("Failed to get color", FAILURE));
	if (env->file.colors[color][R] != -1 || env->file.colors[color][G] != -1 || env->file.colors[color][B] != -1)
		return (ft_err("Color already set", FAILURE));
	env->file.colors[color][R] = ft_atoicolor(split[1]);
	env->file.colors[color][G] = ft_atoicolor(split[2]);
	env->file.colors[color][B] = ft_atoicolor(split[3]);
	if (env->file.colors[color][R] == -1 || env->file.colors[color][G] == -1 || env->file.colors[color][B] == -1)
		return (ft_init_color(env->file.colors[color]), FAILURE);
	// env->file.count++;
	return (SUCCESS);
	/* t_color	*color;

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
	return (SUCCESS); */
}

static int	ft_parse_line(t_env *env, char *line)
{
	char	**split;
	int		ret;

	split = NULL;
	ret = FAILURE;
	if (line && (*line == '\0' || *line == '\n'))
	{
		// env->file.count++;
		return (SUCCESS);
	}
	else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		split = ft_splitmore(line, " ,");
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		split = ft_splitmore(line, " ");
	else
		return (ft_err("Not enough infos", FAILURE));
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
		if (line[i] != '\n' && line[i] != '\0')
		{
			if (ft_parse_line(env, &line[i]) == FAILURE)
			{
				free(line);
				return (FAILURE);
			}
		}
		env->file.count++;
		free(line);
	}
	return (SUCCESS);
}
