/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:22:53 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 16:55:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_ns(t_env *env)
{
	if (env->pdir == 'N')
	{
		env->ray.planeX = -0.66;
		env->ray.planeY = 0;
		env->ray.dirX = 0;
		env->ray.dirY = -1;
	}
	else if (env->pdir == 'S')
	{
		env->ray.planeX = 0.66;
		env->ray.planeY = 0;
		env->ray.dirX = 0;
		env->ray.dirY = 1;
	}
}

static void	ft_set_we(t_env *env)
{
	if (env->pdir == 'W')
	{
		env->ray.planeX = 0;
		env->ray.planeY = -0.66;
		env->ray.dirX = 1;
		env->ray.dirY = 0;
	}
	else if (env->pdir == 'E')
	{
		env->ray.planeX = 0;
		env->ray.planeY = 0.66;
		env->ray.dirX = -1;
		env->ray.dirY = 0;
	}
}

void	ft_update_dir(t_env *env)
{
	ft_set_ns(env);
	ft_set_we(env);
}

int	ft_gettype(char *line)
{
	if (line == NULL)
		return (-1);
	while (*line && ft_iswhitespace(*line) == YES)
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NORTH);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SOUTH);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EAST);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WEST);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEIL);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	return (-1);
}

int	ft_rgb_isvalid(t_env *env)
{
	if (env->file.colors[FLOOR][R] < 0 || env->file.colors[FLOOR][R] > 255)
		return (NO);
	if (env->file.colors[FLOOR][G] < 0 || env->file.colors[FLOOR][G] > 255)
		return (NO);
	if (env->file.colors[FLOOR][B] < 0 || env->file.colors[FLOOR][B] > 255)
		return (NO);
	if (env->file.colors[CEIL][R] < 0 || env->file.colors[CEIL][R] > 255)
		return (NO);
	if (env->file.colors[CEIL][G] < 0 || env->file.colors[CEIL][G] > 255)
		return (NO);
	if (env->file.colors[CEIL][B] < 0 || env->file.colors[CEIL][B] > 255)
		return (NO);
	return (YES);
}
