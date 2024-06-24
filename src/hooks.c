/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 13:10:18 by momrane          ###   ########.fr       */
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
	else if (keycode == XK_Down)
	{
		if(env->map[(int)(env->px - env->ray.dirX * env->ray.ms)][(int)(env->py)] == '0')
			env->px -= env->ray.dirX * env->ray.ms;
		if(env->map[(int)(env->px)][(int)(env->py - env->ray.dirY * env->ray.ms)] == '0')
			env->py -= env->ray.dirY * env->ray.ms;
	}
	else if (keycode == XK_Up)
	{
		if(env->map[(int)(env->px + env->ray.dirX * env->ray.ms)][(int)(env->py)] == '0')
			env->px += env->ray.dirX * env->ray.ms;
		if(env->map[(int)(env->px)][(int)(env->py + env->ray.dirY * env->ray.ms)] == '0')
			env->py += env->ray.dirY * env->ray.ms;
	}
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_env(env);
		exit(0);
	}
	return (0);
}
