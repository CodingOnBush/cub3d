/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:24:35 by momrane           #+#    #+#             */
/*   Updated: 2024/06/26 15:23:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_err(char *str, int ret)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error 🚨\n↳ ", 2);
	ft_putstr_fd(RESET, 2);
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
	if (!str)
		return (-1);
	if (ft_strcmp(str, "WE") == 0)
		return (WEST);
	if (ft_strcmp(str, "EA") == 0)
		return (EAST);
	if (ft_strcmp(str, "NO") == 0)
		return (NORTH);
	if (ft_strcmp(str, "SO") == 0)
		return (SOUTH);
	if (ft_strcmp(str, "C") == 0)
		return (CEIL);
	if (ft_strcmp(str, "F") == 0)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
