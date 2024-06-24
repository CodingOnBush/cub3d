/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 13:39:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_win_cross(t_env *param)
{
	printf("Window closed with the red cross\n");
	ft_free_env(param);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_env *env)
{
	double	oldPx;
	double	oldPy;
	if (keycode == XK_Right)
	{
		double oldDirX = env->ray.dirX;
		env->ray.dirX = env->ray.dirX * cos(-env->ray.rs) - env->ray.dirY * sin(-env->ray.rs);
		env->ray.dirY = oldDirX * sin(-env->ray.rs) + env->ray.dirY * cos(-env->ray.rs);
		double oldPlaneX = env->ray.planeX;
		env->ray.planeX = env->ray.planeX * cos(-env->ray.rs) - env->ray.planeY * sin(-env->ray.rs);
		env->ray.planeY = oldPlaneX * sin(-env->ray.rs) + env->ray.planeY * cos(-env->ray.rs);
	}
	else if (keycode == XK_Left)
{
		double oldDirX = env->ray.dirX;
		env->ray.dirX = env->ray.dirX * cos(env->ray.rs) - env->ray.dirY * sin(env->ray.rs);
		env->ray.dirY = oldDirX * sin(env->ray.rs) + env->ray.dirY * cos(env->ray.rs);
		double oldPlaneX = env->ray.planeX;
		env->ray.planeX = env->ray.planeX * cos(env->ray.rs) - env->ray.planeY * sin(env->ray.rs);
		env->ray.planeY = oldPlaneX * sin(env->ray.rs) + env->ray.planeY * cos(env->ray.rs);
	}
	else if (keycode == XK_a || keycode == XK_A)
	{
		if (c->data.map[(int)(c->data.px - c->cst.planeX * c->cst.ms)][(int)(c->data.py)] == '0')
		{
			oldPx = c->data.px;
			c->data.px -= c->cst.planeX * c->cst.ms;
			if (c->data.px < 0)
				c->data.px = oldPx;
		}
		if (c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.planeY * c->cst.ms)] == '0')
		{
			oldPy = c->data.py;	
			c->data.py -= c->cst.planeY * c->cst.ms;
			if (c->data.py < 0)
				c->data.py = oldPy;
		}
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		if (c->data.map[(int)(c->data.px + c->cst.planeX * c->cst.ms)][(int)(c->data.py)] == '0')
		{
			oldPx = c->data.px;
			c->data.px += c->cst.planeX * c->cst.ms;
			if (c->data.px > c->cst.width)
				c->data.px = oldPx;
		}
		if (c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.planeY * c->cst.ms)] == '0')
		{
			oldPy = c->data.py;
			c->data.py += c->cst.planeY * c->cst.ms;
			if (c->data.py > c->cst.height)
				c->data.py = oldPy;
		}
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		if(c->data.map[(int)(c->data.px + c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
		{
			oldPx = c->data.px;
			c->data.px += c->cst.dirX * c->cst.ms;
			if (c->data.px > c->cst.width)
				c->data.px = oldPx;
		}
		if(c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.dirY * c->cst.ms)] == '0')
		{
			oldPy = c->data.py;
			c->data.py += c->cst.dirY * c->cst.ms;
			if (c->data.py > c->cst.height)
				c->data.py = oldPy;
		}
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		if(c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
		{
			oldPx = c->data.px;
			c->data.px -= c->cst.dirX * c->cst.ms;
			if (c->data.px < 0)
				c->data.px = oldPx;
		}
		if(c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.dirY * c->cst.ms)] == '0')
		{
			oldPy = c->data.py;
			c->data.py -= c->cst.dirY * c->cst.ms;
			if (c->data.py < 0)
				c->data.py = oldPy;
		}
	}
	// else if (keycode == XK_Escape)
	// {
	// 	printf("Escape key pressed, so byeee !\n");
	// 	ft_free_cube3d(c);
	// 	exit(0);
	// }
	// else if (keycode == XK_Down)
	// {
	// 	if(c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
	// 		c->data.px -= c->cst.dirX * c->cst.ms;
	// 	if(c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.dirY * c->cst.ms)] == '0')
	// 		c->data.py -= c->cst.dirY * c->cst.ms;
	// }
	// else if (keycode == XK_Up)
	// {
	// 	if(c->data.map[(int)(c->data.px + c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
	// 		c->data.px += c->cst.dirX * c->cst.ms;
	// 	if(c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.dirY * c->cst.ms)] == '0')
	// 		c->data.py += c->cst.dirY * c->cst.ms;
	// }
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_env(env);
		exit(0);
	}
	return (0);
}
