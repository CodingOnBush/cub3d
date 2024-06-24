/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 14:01:23 by momrane          ###   ########.fr       */
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
		if (env->map[(int)(env->px - env->ray.planeX * env->ray.ms)][(int)(env->py)] == '0')
		{
			oldPx = env->px;
			env->px -= env->ray.planeX * env->ray.ms;
			if (env->px < 0)
				env->px = oldPx;
		}
		if (env->map[(int)(env->px)][(int)(env->py - env->ray.planeY * env->ray.ms)] == '0')
		{
			oldPy = env->py;	
			env->py -= env->ray.planeY * env->ray.ms;
			if (env->py < 0)
				env->py = oldPy;
		}
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		if (env->map[(int)(env->px + env->ray.planeX * env->ray.ms)][(int)(env->py)] == '0')
		{
			oldPx = env->px;
			env->px += env->ray.planeX * env->ray.ms;
			if (env->px > env->win.winw)
				env->px = oldPx;
		}
		if (env->map[(int)(env->px)][(int)(env->py + env->ray.planeY * env->ray.ms)] == '0')
		{
			oldPy = env->py;
			env->py += env->ray.planeY * env->ray.ms;
			if (env->py > env->win.winh)
				env->py = oldPy;
		}
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		if(env->map[(int)(env->px + env->ray.dirX * env->ray.ms)][(int)(env->py)] == '0')
		{
			oldPx = env->px;
			env->px += env->ray.dirX * env->ray.ms;
			if (env->px > env->win.winw)
				env->px = oldPx;
		}
		if(env->map[(int)(env->px)][(int)(env->py + env->ray.dirY * env->ray.ms)] == '0')
		{
			oldPy = env->py;
			env->py += env->ray.dirY * env->ray.ms;
			if (env->py > env->win.winh)
				env->py = oldPy;
		}
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		if(env->map[(int)(env->px - env->ray.dirX * env->ray.ms)][(int)(env->py)] == '0')
		{
			oldPx = env->px;
			env->px -= env->ray.dirX * env->ray.ms;
			if (env->px < 0)
				env->px = oldPx;
		}
		if(env->map[(int)(env->px)][(int)(env->py - env->ray.dirY * env->ray.ms)] == '0')
		{
			oldPy = env->py;
			env->py -= env->ray.dirY * env->ray.ms;
			if (env->py < 0)
				env->py = oldPy;
		}
	}
	// else if (keycode == XK_Escape)
	// {
	// 	printf("Escape key pressed, so byeee !\n");
	// 	ft_free_cube3d(env);
	// 	exit(0);
	// }
	// else if (keycode == XK_Down)
	// {
	// 	if(env->map[(int)(env->px - env->ray.dirX * env->ray.ms)][(int)(env->py)] == '0')
	// 		env->px -= env->ray.dirX * env->ray.ms;
	// 	if(env->map[(int)(env->px)][(int)(env->py - env->ray.dirY * env->ray.ms)] == '0')
	// 		env->py -= env->ray.dirY * env->ray.ms;
	// }
	// else if (keycode == XK_Up)
	// {
	// 	if(env->map[(int)(env->px + env->ray.dirX * env->ray.ms)][(int)(env->py)] == '0')
	// 		env->px += env->ray.dirX * env->ray.ms;
	// 	if(env->map[(int)(env->px)][(int)(env->py + env->ray.dirY * env->ray.ms)] == '0')
	// 		env->py += env->ray.dirY * env->ray.ms;
	// }
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_env(env);
		exit(0);
	}
	return (0);
}