/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:34:22 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 10:01:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_handle_angle(int keycode, t_env *env)
{
	if (keycode == XK_Right)
	{
		env->angle -= 0.2;
		ft_printf("[🔄]");
		ft_draw(env);
	}
	else if (keycode == XK_Left)
	{
		env->angle += 0.2;
		ft_printf("[🔄]");
		ft_draw(env);
	}
}

static void	ft_handl_altitude(int keycode, t_env *env)
{
	if (keycode == XK_Down)
	{
		env->altitude -= 0.4;
		ft_printf("[📉]");
		ft_draw(env);
	}
	else if (keycode == XK_Up)
	{
		env->altitude += 0.4;
		ft_printf("[📈]");
		ft_draw(env);
	}
}

static void	ft_handle_move(int keycode, t_env *env)
{
	if (keycode == XK_a)
	{
		env->origin.x -= 50;
		ft_printf("[◀️]");
		ft_draw(env);
	}
	else if (keycode == XK_d)
	{
		env->origin.x += 50;
		ft_printf("[▶️]");
		ft_draw(env);
	}
	else if (keycode == XK_w)
	{
		env->origin.y -= 50;
		ft_printf("[🔼]");
		ft_draw(env);
	}
	else if (keycode == XK_s)
	{
		env->origin.y += 50;
		ft_printf("[🔽]");
		ft_draw(env);
	}
}

int	ft_key_hook(int keycode, t_env *env)
{
	if (keycode == XK_Right || keycode == XK_Left)
		ft_handle_angle(keycode, env);
	else if (keycode == XK_Down || keycode == XK_Up)
		ft_handl_altitude(keycode, env);
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
		|| keycode == XK_d)
		ft_handle_move(keycode, env);
	else if (keycode == XK_Escape)
	{
		ft_free_env(env);
		exit(0);
	}
	return (0);
}
