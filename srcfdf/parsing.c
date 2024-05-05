/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:18:10 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:43:49 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	ft_get_color_intensity(int value)
{
	int	red_intensity;
	int	blue_intensity;
	int	green_intensity;
	int	color;

	if (value < 0)
		value = 0;
	else if (value > 255)
		value = 255;
	red_intensity = value;
	blue_intensity = 255 - value;
	green_intensity = 255 - value;
	color = (red_intensity << 16) | (green_intensity << 8) | blue_intensity;
	return (color);
}

static int	ft_point_detected(t_env *env, char *line)
{
	int	i;
	int	altitude;

	i = 0;
	if (ft_strchr("+-", line[i]))
		i++;
	env->map[env->r][env->c].x = env->c;
	env->map[env->r][env->c].y = env->r;
	altitude = ft_atoi(&line[i]);
	env->map[env->r][env->c].z = altitude;
	while (ft_isdigit(line[i]) && line[i] != '\0')
		i++;
	if (line[i] == ',')
	{
		i += 3;
		env->map[env->r][env->c].color = ft_get_color(&line[i]);
		while (ft_isdigit(line[i]) || ft_strchr("abcdefABCDEF", line[i]))
			i++;
	}
	else
		env->map[env->r][env->c].color = ft_get_color_intensity(altitude);
	env->c++;
	return (i);
}

static void	ft_parse_line(t_env *env, char *line)
{
	int	step;

	step = 0;
	while (*line)
	{
		if (ft_isdigit(*line) || ft_strchr("+-", *line))
		{
			step = ft_point_detected(env, line);
			line += step;
		}
		else
			line++;
	}
	env->r++;
	env->c = 0;
}

static int	ft_parse(t_env *env)
{
	char	*line;
	int		fd;

	fd = open(env->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		ft_parse_line(env, line);
		free(line);
	}
	close(fd);
	env->r = env->rows / 2;
	env->c = env->cols / 2;
	return (1);
}

int	ft_parse_map(t_env *env)
{
	if (env->map == NULL && env->mat == NULL)
		return (-1);
	if (env->rows == 0 || env->cols == 0)
		return (-1);
	if (ft_parse(env) < 0)
		return (-1);
	return (1);
}
