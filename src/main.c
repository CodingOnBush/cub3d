/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/26 07:51:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3d <map.file>\n", 2), FAILURE);
	ft_init_env(&env);
	if (ft_parsing(&env, av[1]) == FAILURE)
		return (ft_free_env(&env), FAILURE);
	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, env.winw, env.winh, "victafa");
	ft_load_images(&env);
	mlx_hook((void *)env.win_ptr, 2, KeyPressMask, ft_key_pressed, &env);
	mlx_hook((void *)env.win_ptr, 3, KeyReleaseMask, ft_key_released, &env);
	mlx_hook(env.win_ptr, 17, ButtonPressMask, ft_win_cross, &env);
	mlx_loop_hook(env.mlx_ptr, ft_render, &env);
	mlx_loop(env.mlx_ptr);
	ft_free_env(&env);
	return (SUCCESS);
}


