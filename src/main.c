/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 13:56:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_render(t_env *env)
{
	int	col;

	
	col = 0;
	while (col < env->winw)
	{
		ft_draw(env, col);
		col++;
	}
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[CANVAS].mlx_img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3d <map.file>\n", 2), FAILURE);
	
	
	ft_init_env(&env);
	if (ft_parsing(&env, av[1]) == FAILURE)
		return (ft_free_env(&env), FAILURE);
	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, env.winw, env.winh, "cub3d");

	env.img[CANVAS].mlx_img = mlx_new_image(env.mlx_ptr, env.winw, env.winh);
	env.img[CANVAS].addr = mlx_get_data_addr(env.img[CANVAS].mlx_img, &env.img[CANVAS].bpp, &env.img[CANVAS].llen, &env.img[CANVAS].endian);
	env.img[NORTH].mlx_img = mlx_xpm_file_to_image(env.mlx_ptr, env.img[NORTH].path, &env.img[NORTH].imgw, &env.img[NORTH].imgh);
	env.img[NORTH].addr = mlx_get_data_addr(env.img[NORTH].mlx_img, &env.img[NORTH].bpp, &env.img[NORTH].llen, &env.img[NORTH].endian);
	env.img[SOUTH].mlx_img = mlx_xpm_file_to_image(env.mlx_ptr, env.img[SOUTH].path, &env.img[SOUTH].imgw, &env.img[SOUTH].imgh);
	env.img[SOUTH].addr = mlx_get_data_addr(env.img[SOUTH].mlx_img, &env.img[SOUTH].bpp, &env.img[SOUTH].llen, &env.img[SOUTH].endian);
	env.img[WEST].mlx_img = mlx_xpm_file_to_image(env.mlx_ptr, env.img[WEST].path, &env.img[WEST].imgw, &env.img[WEST].imgh);
	env.img[WEST].addr = mlx_get_data_addr(env.img[WEST].mlx_img, &env.img[WEST].bpp, &env.img[WEST].llen, &env.img[WEST].endian);
	env.img[EAST].mlx_img = mlx_xpm_file_to_image(env.mlx_ptr, env.img[EAST].path, &env.img[EAST].imgw, &env.img[EAST].imgh);
	env.img[EAST].addr = mlx_get_data_addr(env.img[EAST].mlx_img, &env.img[EAST].bpp, &env.img[EAST].llen, &env.img[EAST].endian);
	
	mlx_hook((void *)env.win_ptr, 2, 1L << 0, ft_key_hook, &env);
	mlx_loop_hook(env.mlx_ptr, ft_render, &env);
	mlx_hook(env.win_ptr, 17, 1L << 2, ft_win_cross, &env);
	mlx_loop(env.mlx_ptr);
	
	

	// ft_free_cube3d(&cub);
	ft_free_env(&env);
	return (SUCCESS);
}
