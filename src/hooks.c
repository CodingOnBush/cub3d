/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 08:21:53 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_win_cross(t_env *env)
{
	printf("Window closed with the red cross\n");
	ft_free_env(env);
	exit(0);
	return (0);
}

int	ft_key_pressed(int keycode, t_env *env)
{
	if (keycode == XK_Right)
		env->rotright = 1;
	else if (keycode == XK_Left)
		env->rotleft = 1;
	else if (keycode == XK_a || keycode == XK_A)
		env->left = 1;
	else if (keycode == XK_d || keycode == XK_D)
		env->right = 1;
	else if (keycode == XK_w || keycode == XK_W)
		env->up = 1;
	else if (keycode == XK_s || keycode == XK_S)
		env->down = 1;
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_env(env);
		exit(0);
	}
	return (0);
}

int	ft_key_released(int keycode, t_env *env)
{
	if (keycode == XK_Right)
		env->rotright = 0;
	else if (keycode == XK_Left)
		env->rotleft = 0;
	else if (keycode == XK_a || keycode == XK_A)
		env->left = 0;
	else if (keycode == XK_d || keycode == XK_D)
		env->right = 0;
	else if (keycode == XK_w || keycode == XK_W)
		env->up = 0;
	else if (keycode == XK_s || keycode == XK_S)
		env->down = 0;
	return (0);
}
