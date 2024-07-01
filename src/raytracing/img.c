/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:08 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 15:28:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_env *env, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= env->winw || r < 0 || r >= env->winh)
		return ;
	dst = env->img[CANVAS].addr + (r * env->img[CANVAS].llen + c
			* (env->img[CANVAS].bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_get_texpixel(t_env *env, int texx, int texy)
{
	t_img	tex;
	char	*color;
	int		wall;

	if (env->ray.side == 1)
	{
		wall = NORTH;
		if (env->py <= env->ray.mapy)
			wall = SOUTH;
	}
	else
	{
		wall = EAST;
		if (env->px <= env->ray.mapx)
			wall = WEST;
	}
	tex = env->img[wall];
	if (texx < 0 || texx >= tex.imgw || texy < 0 || texy >= tex.imgh)
		return (0);
	color = (tex.addr + (texy * tex.llen + texx * (tex.bpp / 8)));
	return (*(unsigned int *)color);
}

int	ft_get_texx(t_env *env)
{
	double	wallx;
	int		texx;

	if (env->ray.side == 0)
		wallx = env->py + env->ray.adjacent * env->ray.raydir.y;
	else
		wallx = env->px + env->ray.adjacent * env->ray.raydir.x;
	wallx -= floor((wallx));
	texx = (int)(wallx * (double)(env->img[NORTH].imgw));
	if (env->ray.side == 0 && env->ray.raydir.x > 0)
		texx = TEXH - texx - 1;
	if (env->ray.side == 1 && env->ray.raydir.y < 0)
		texx = env->img[NORTH].imgw - texx - 1;
	return (texx);
}
