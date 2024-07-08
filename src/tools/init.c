/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:49 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 16:46:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_init_ray(t_ray *ray)
{
	ray->raydir.x = 0;
	ray->raydir.y = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->sidedist.x = 0;
	ray->sidedist.y = 0;
	ray->deltadist.x = 0;
	ray->deltadist.y = 0;
	ray->adjacent = 0;
	ray->side = 0;
	ray->planex = 0.66;
	ray->planey = 0;
	ray->dirx = 0;
	ray->diry = 1;
	ray->ms = 0.055;
	ray->rs = 0.02;
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

static void	ft_init_color(int color[3])
{
	color[R] = -1;
	color[G] = -1;
	color[B] = -1;
}

static void	ft_set_values(t_env *env)
{
	env->map = NULL;
	env->mapstart = 0;
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->winw = 900;
	env->winh = 900;
	env->mapw = 0;
	env->maph = 0;
	env->px = 0;
	env->py = 0;
	env->pdir = 0;
	env->up = 0;
	env->down = 0;
	env->left = 0;
	env->right = 0;
	env->rotleft = 0;
	env->rotright = 0;
}

void	ft_init_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		ft_init_img(&env->img[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		ft_init_color(env->colors[i]);
		i++;
	}
	ft_set_values(env);
	ft_init_ray(&env->ray);
}
