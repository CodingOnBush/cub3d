/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/13 14:23:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_win_cross(t_cub3d *param)
{
	printf("Window closed with the red cross\n");
	ft_free_cube3d(param);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_cub3d *param)
{
	if (keycode == XK_Right || keycode == XK_Left)
		printf("Right or Left key pressed\n");
	else if (keycode == XK_Down || keycode == XK_Up)
		printf("Down or Up key pressed\n");
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
		|| keycode == XK_d)
		printf("W, S, A or D key pressed\n");
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed so byeee !\n");
		ft_free_cube3d(param);
		exit(0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	cub3d;

	(void)ac;
	(void)av;
	cub3d.mlx_ptr = mlx_init();
	cub3d.win_ptr = mlx_new_window(cub3d.mlx_ptr, 300, 300, "cube3d");
	mlx_key_hook(cub3d.win_ptr, ft_key_hook, &cub3d);
	mlx_hook(cub3d.win_ptr, 17, 1L << 2, ft_win_cross, &cub3d);
	mlx_loop(cub3d.mlx_ptr);
	ft_free_cube3d(&cub3d);
	return (0);
}
