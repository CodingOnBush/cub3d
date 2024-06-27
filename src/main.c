/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 09:29:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_launch_cub3d(char *cubfile)
{
	t_env	env;
	
	ft_init_env(&env);
	if (ft_parsing(&env, cubfile) == FAILURE)
		return (ft_free_env(&env), FAILURE);
	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, env.winw, env.winh, "victafa");
	if (ft_load_images(&env) == FAILURE)
		return (ft_free_env(&env), ft_err("Image loading failed", FAILURE));
	mlx_hook((void *)env.win_ptr, 2, KeyPressMask, ft_key_pressed, &env);
	mlx_hook((void *)env.win_ptr, 3, KeyReleaseMask, ft_key_released, &env);
	mlx_hook(env.win_ptr, 17, ButtonPressMask, ft_win_cross, &env);
	mlx_loop_hook(env.mlx_ptr, ft_render, &env);
	mlx_loop(env.mlx_ptr);
	ft_free_env(&env);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_err("Usage : ./cub3d <map.file>", FAILURE));
	return (ft_launch_cub3d(av[1]));
}
