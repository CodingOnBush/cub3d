/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/13 19:30:14 by momrane          ###   ########.fr       */
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

int	ft_key_hook(int keycode, t_cub3d *c)
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
		printf("Escape key pressed, so byeee !\n");
		ft_free_cube3d(c);
		exit(0);
	}
	return (0);
}

int	render(t_cub3d *c)
{
	// if (c->mlx.win_ptr != NULL)
	// {
	// 	for (size_t j = 0; j < c->height; j++)
	// 	{
	// 		for (size_t i = 0; i < c->width; i++)
	// 		{
	// 			mlx_pixel_put(c->mlx.mlx_ptr, c->mlx.win_ptr, i, j, 0xFF0000);
	// 		}
	// 	}
	// }
	/*
	Too slow, we need to use the mlx_new_image() function
	*/

	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->width, c->height);
	/*
	Now that we've the image, we need to get a bunch of 
	informations about it in order to make the whole thing work.

	We'll especially need the address of the image in the shared memory,
	so that we are able to change the pixels of it directly.
	We'll also need additional informations to help us 
	with some calculations (bpp, line_len and endian member variables).
	*/

	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);
	/*
	Now that we've all the informations we need, we can start to draw on the image.
	
	Talking about return value, the mlx_get_data_addr function returns the actual 
	address of the image as a simple array of pixels.
	We're getting a pointer on char, which usually means we're going 
	to naviguate in the array one byte at a time (not one pixel 
	at a time, a pixel usually takes more than 
	one byte as we've seen before).
	*/
	
	

	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	c;

	c.width = 1300;
	c.height = 1300;
	c.mlx.mlx_ptr = mlx_init();
	if (!(c.mlx.mlx_ptr))
	{
		printf("Error : mlx_init() failed\n");
		return (FAILURE);
	}
	c.mlx.win_ptr = mlx_new_window(c.mlx.mlx_ptr, c.width, c.height,
			"window title");
	if (!(c.mlx.win_ptr))
	{
		printf("Error : mlx_new_window() failed\n");
		free(c.mlx.mlx_ptr);
		return (FAILURE);
	}
	mlx_key_hook(c.mlx.win_ptr, ft_key_hook, &c);
	mlx_loop_hook(c.mlx.mlx_ptr, render, &c);
	mlx_hook(c.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &c);
	mlx_loop(c.mlx.mlx_ptr);
	ft_free_cube3d(&c);
	return (SUCCESS);
}
