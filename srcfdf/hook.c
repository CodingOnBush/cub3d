/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:37:37 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:48:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	ft_win_cross(t_env *env)
{
	ft_free_env(env);
	exit(0);
	return (0);
}

static int	ft_mouse_hook(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		env->zoom += 0.4;
		ft_printf("[➕]");
		ft_draw(env);
	}
	else if (button == 5)
	{
		env->zoom -= 0.4;
		ft_printf("[➖]");
		ft_draw(env);
	}
	return (0);
}

void	ft_trigger_hooks(t_env *env)
{
	mlx_key_hook(env->win_ptr, ft_key_hook, env);
	mlx_mouse_hook(env->win_ptr, ft_mouse_hook, env);
	mlx_hook(env->win_ptr, 17, 1L << 2, ft_win_cross, env);
}
