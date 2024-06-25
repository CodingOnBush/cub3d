/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:49 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 15:12:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_init_ray(t_ray *ray)
{
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->perpWallDist = 0;
	
	// WEST
	// ray->planeX = 0;
	// ray->planeY = 0.66;
	// ray->dirX = -1;
	// ray->dirY = 0;
	
	// SOUTH
	// ray->planeX = -0.66;
	// ray->planeY = 0;
	// ray->dirX = 0;
	// ray->dirY = -1;

	// EAST
	// ray->planeX = 0;
	// ray->planeY = -0.66;
	// ray->dirX = 1;
	// ray->dirY = 0;

	// NORTH
	ray->planeX = 0.66;
	ray->planeY = 0;
	ray->dirX = 0;
	ray->dirY = 1;
	
	ray->ms = 0.5;
	ray->rs = 0.05;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->texCol = 0;
}

static void	ft_init_img(t_img *img)
{
	img->path = NULL;
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->llen = 0;
	img->endian = 0;
	img->imgw = 64;
	img->imgh = 64;
}

static void	ft_init_file(t_file *file)
{
	int i;

	file->content = NULL;
	file->width = 0;
	file->height = 0;
	i = 0;
	while (i < 2)
	{
		file->colors[i][R] = -1;
		file->colors[i][G] = -1;
		file->colors[i][B] = -1;
		i++;
	}
	file->count = 0;
}

void	ft_init_env(t_env *env)
{
	int	i;

	ft_init_file(&env->file);
	env->map = NULL;
	env->mapw = 0;
	env->maph = 0;
	env->px = 0;
	env->py = 0;
	env->winw = 900;
	env->winh = 900;
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	i = 0;
	while (i < 5)
	{
		ft_init_img(&env->img[i]);
		i++;
	}
	ft_init_ray(&env->ray);
}
