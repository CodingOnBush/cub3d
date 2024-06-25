/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:24:35 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 15:08:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_err(char *str, int ret)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (ret);
}

int	ft_splitlen(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

int	ft_get_id(char *str)
{
	if (ft_strncmp(str, "WE", 2) == 0)
		return (WEST);
	if (ft_strncmp(str, "EA", 2) == 0)
		return (EAST);
	if (ft_strncmp(str, "NO", 2) == 0)
		return (NORTH);
	if (ft_strncmp(str, "SO", 2) == 0)
		return (SOUTH);
	if (ft_strncmp(str, "C", 2) == 0)
		return (CEIL);
	if (ft_strncmp(str, "F", 2) == 0)
		return (FLOOR);
	return (-1);
}

void	ft_update_dir(t_env *env)
{
	if (env->pdir == 'E')
	{
		env->ray.planeX = 0.66;
		env->ray.planeY = 0;
		env->ray.dirX = 0;
		env->ray.dirY = 1;
	}
	else if (env->pdir == 'W')
	{
		env->ray.planeX = -0.66;
		env->ray.planeY = 0;
		env->ray.dirX = 0;
		env->ray.dirY = -1;
	}
	else if (env->pdir == 'N')
	{
		env->ray.planeX = 0;
		env->ray.planeY = 0.66;
		env->ray.dirX = -1;
		env->ray.dirY = 0;
	}
	else if (env->pdir == 'S')
	{
		env->ray.planeX = 0;
		env->ray.planeY = -0.66;
		env->ray.dirX = 1;
		env->ray.dirY = 0;
	}
}
