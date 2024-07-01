/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:49 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 15:50:54 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*ms0.5 rs0.2*/
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

static void	ft_init_file(t_file *file)
{
	int	i;

	i = 0;
	file->content = NULL;
	file->width = 0;
	file->rows = 0;
	while (i < 2)
	{
		file->colors[i][R] = 1;
		file->colors[i][G] = 1;
		file->colors[i][B] = 1;
		i++;
	}
	file->count = 0;
}

void	ft_init_env(t_env *env)
{
	int	i;

	ft_init_file(&env->file);
	env->map = NULL;
	i = 0;
	while (i < 5)
		ft_init_img(&env->img[i++]);
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
	ft_init_ray(&env->ray);
}