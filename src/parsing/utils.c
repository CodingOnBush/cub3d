/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:27:50 by momrane           #+#    #+#             */
/*   Updated: 2024/07/10 11:00:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_color_is_empty(int color[3])
{
	if (color[R] == -1)
		return (YES);
	if (color[G] == -1)
		return (YES);
	if (color[B] == -1)
		return (YES);
	return (NO);
}

int	ft_is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (YES);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (YES);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (YES);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (YES);
	return (NO);
}

int	ft_is_color_line(char *line)
{
	if (ft_strncmp(line, "F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
		return (NO);
	line += 2;
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line))
		return (NO);
	if (ft_strchr(line, ',') == NULL)
		return (NO);
	line = ft_strchr(line, ',') + 1;
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line))
		return (NO);
	if (ft_strchr(line, ',') == NULL)
		return (NO);
	line = ft_strchr(line, ',') + 1;
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line))
		return (NO);
	if (ft_strchr(line, ',') != NULL)
		return (NO);
	return (YES);
}

int	ft_atoicolor(const char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		return (ft_err("Sign before color value are not allowed", -1));
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		if (res > 255)
			return (ft_err("Invalid color value", -1));
		i++;
	}
	if (str[i] != '\0' && str[i] != '\n')
		return (ft_err("Invalid color value", -1));
	return (res);
}

int	ft_all_data_collected(t_env *env)
{
	if (env->img[NORTH].path == NULL)
		return (NO);
	if (env->img[SOUTH].path == NULL)
		return (NO);
	if (env->img[WEST].path == NULL)
		return (NO);
	if (env->img[EAST].path == NULL)
		return (NO);
	if (ft_color_is_empty(env->colors[FLOOR]) == YES)
		return (NO);
	if (ft_color_is_empty(env->colors[CEIL]) == YES)
		return (NO);
	return (YES);
}
