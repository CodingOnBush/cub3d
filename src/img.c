/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:15:10 by allblue           #+#    #+#             */
/*   Updated: 2024/06/30 19:16:27 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_env *env, int col, int row, int color)
{
	t_img const	img = env->img[CANVAS];
	void		*box;

	if (col < 0 || col >= env->winw)
		return ;
	if (row < 0 || row >= env->winh)
		return ;
	box = img.addr + (row * img.llen + col * (img.bpp / 8));
	*(unsigned int *)box = color;
}

t_img	ft_get_texture(t_env *env)
{
	int	wall;

	if (env->ray.side == 1)
	{
		wall = NORTH;
		if (env->py <= env->ray.mapY)
			wall = SOUTH;
	}
	else
	{
		wall = EAST;
		if (env->px <= env->ray.mapX)
			wall = WEST;
	}
	return (env->img[wall]);
}

int	ft_get_tex_pixel(t_env *env, t_point tex)
{
	t_img const	img = ft_get_texture(env);
	void		*box;

	if (tex.x < 0 || tex.x >= img.imgw || tex.y < 0 || tex.y >= img.imgh)
		return (0);
	box = img.addr + (tex.y * img.llen + tex.x * (img.bpp / 8));
	return (*(int *)box);
}
