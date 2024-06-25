/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 08:01:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_win_cross(t_env *env)
{
	printf("Window closed with the red cross\n");
	// ft_free_cube3d(param);
	ft_free_env(env);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_cub3d *c)
{
	double	stepHorizontalX;
	double	stepHorizontalY;
	double	stepVerticalX;
	double	stepVerticalY;

	stepHorizontalX = c->cst.planeX * c->cst.ms;
	stepHorizontalY = c->cst.planeY * c->cst.ms;
	stepVerticalX = c->cst.dirX * c->cst.ms;
	stepVerticalY = c->cst.dirY * c->cst.ms;
	if (keycode == XK_Right)
	{
		double oldDirX = c->cst.dirX;
		c->cst.dirX = c->cst.dirX * cos(-c->cst.rs) - c->cst.dirY * sin(-c->cst.rs);
		c->cst.dirY = oldDirX * sin(-c->cst.rs) + c->cst.dirY * cos(-c->cst.rs);
		double oldPlaneX = c->cst.planeX;
		c->cst.planeX = c->cst.planeX * cos(-c->cst.rs) - c->cst.planeY * sin(-c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(-c->cst.rs) + c->cst.planeY * cos(-c->cst.rs);
	}
	else if (keycode == XK_Left)
{
		double oldDirX = c->cst.dirX;
		c->cst.dirX = c->cst.dirX * cos(c->cst.rs) - c->cst.dirY * sin(c->cst.rs);
		c->cst.dirY = oldDirX * sin(c->cst.rs) + c->cst.dirY * cos(c->cst.rs);
		double oldPlaneX = c->cst.planeX;
		c->cst.planeX = c->cst.planeX * cos(c->cst.rs) - c->cst.planeY * sin(c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(c->cst.rs) + c->cst.planeY * cos(c->cst.rs);
	}
	else if (keycode == XK_a || keycode == XK_A)
	{
		if (c->data.map[(int)(c->data.px - stepHorizontalX)][(int)(c->data.py)] == '0')
			c->data.px -= stepHorizontalX;
		if (c->data.map[(int)(c->data.px)][(int)(c->data.py - stepHorizontalY)] == '0')
			c->data.py -= stepHorizontalY;
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		if (c->data.map[(int)(c->data.px + stepHorizontalX)][(int)(c->data.py)] == '0')
			c->data.px += stepHorizontalX;
		if (c->data.map[(int)(c->data.px)][(int)(c->data.py + stepHorizontalY)] == '0')
			c->data.py += stepHorizontalY;
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		if(c->data.map[(int)(c->data.px + stepVerticalX)][(int)(c->data.py)] == '0')
			c->data.px += stepVerticalX;
		if(c->data.map[(int)(c->data.px)][(int)(c->data.py + stepVerticalY)] == '0')
			c->data.py += stepVerticalY;
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		if(c->data.map[(int)(c->data.px - stepVerticalX)][(int)(c->data.py)] == '0')
			c->data.px -= stepVerticalX;
		if(c->data.map[(int)(c->data.px)][(int)(c->data.py - stepVerticalY)] == '0')
			c->data.py -= stepVerticalY;
	}
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_cube3d(c);
		exit(0);
	}
	return (0);
}

int	ft_key_hook2(int keycode, t_env *env)
{
	double	stepHorizontalX;
	double	stepHorizontalY;
	double	stepVerticalX;
	double	stepVerticalY;

	stepHorizontalX = env->ray.planeX * env->ray.ms;
	stepHorizontalY = env->ray.planeY * env->ray.ms;
	stepVerticalX = env->ray.dirX * env->ray.ms;
	stepVerticalY = env->ray.dirY * env->ray.ms;
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
		if (env->map[(int)(env->px - stepHorizontalX)][(int)(env->py)] == '0')
			env->px -= stepHorizontalX;
		if (env->map[(int)(env->px)][(int)(env->py - stepHorizontalY)] == '0')
			env->py -= stepHorizontalY;
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		if (env->map[(int)(env->px + stepHorizontalX)][(int)(env->py)] == '0')
			env->px += stepHorizontalX;
		if (env->map[(int)(env->px)][(int)(env->py + stepHorizontalY)] == '0')
			env->py += stepHorizontalY;
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		if(env->map[(int)(env->px + stepVerticalX)][(int)(env->py)] == '0')
			env->px += stepVerticalX;
		if(env->map[(int)(env->px)][(int)(env->py + stepVerticalY)] == '0')
			env->py += stepVerticalY;
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		if(env->map[(int)(env->px - stepVerticalX)][(int)(env->py)] == '0')
			env->px -= stepVerticalX;
		if(env->map[(int)(env->px)][(int)(env->py - stepVerticalY)] == '0')
			env->py -= stepVerticalY;
	}
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		// ft_free_cube3d(c);
		ft_free_env(env);
		exit(0);
	}
	return (0);
}
