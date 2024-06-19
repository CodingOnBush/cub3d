/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 18:23:58 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static int	render(t_cub3d *c)
{
	c->buf.w = 0;
	c->img.w = 0;
	c->buf.h = 0;
	c->img.h = 0;
	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->cst.width, c->cst.height);
	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);
	
	c->buf.mlx_img = mlx_xpm_file_to_image(c->mlx.mlx_ptr, "redbrick.xpm", &(c->buf.w), &(c->buf.h));
	c->buf.addr = mlx_get_data_addr(c->buf.mlx_img, &c->buf.bpp, &c->buf.line_len, &c->buf.endian);
	
	ft_pixel_put(c, 0, 0, 0x00FF00);
	ft_pixel_put(c, 0, 1, 0x00FF00);
	ft_pixel_put(c, 1, 0, 0x00FF00);
	ft_pixel_put(c, 1, 1, 0x00FF00);
	

	// // printf("Rendering...\n");
	// printf("c->cst.width = %d\n", c->cst.width);
	for (int col = 0; col < c->cst.width; col++)
	{ 
		// ft_draw_column(c, col, ft_get_perp_wall_dist(c, col));
		printf("col = %d\n", col);
		ft_get_perp_wall_dist(c, col);
	}
	
	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	// mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->buf.mlx_img, 30, 30);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
	mlx_destroy_image(c->mlx.mlx_ptr, c->buf.mlx_img);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	ft_init_cst(&cub.cst);
	ft_init_ray(&cub.ray);
	ft_init_sim(&cub.sim);
	
	cub.sim.mapw = 24;
	cub.sim.maph = 24;
	cub.sim.px = 1;
	cub.sim.py = 1;

	cub.buf.w = 0;
	cub.buf.h = 0;
	cub.buf.addr = NULL;
	cub.buf.mlx_img = NULL;
	cub.buf.line_len = 0;
	cub.buf.bpp = 0;
	
	cub.img.w = 0;
	cub.img.h = 0;
	cub.img.mlx_img = NULL;
	cub.img.addr = NULL;
	cub.img.line_len = 0;
	cub.img.bpp = 0;

	ft_init_data(&cub.data);
	
	// printf("Parsing...\n");
	// if (ft_parsing(&cub, ac, av) == FAILURE)
	// 	return (FAILURE);
	
	
	cub.mlx.mlx_ptr = mlx_init();
	if (!(cub.mlx.mlx_ptr))
		return (printf("Error : mlx_init() failed\n"), FAILURE);
	cub.mlx.win_ptr = mlx_new_window(cub.mlx.mlx_ptr, cub.cst.width, cub.cst.height, "?");
	if (!(cub.mlx.win_ptr))
		return (printf("Error : mlx_new_window() failed\n"), free(cub.mlx.mlx_ptr), FAILURE);
	mlx_key_hook(cub.mlx.win_ptr, ft_key_hook, &cub);
	mlx_loop_hook(cub.mlx.mlx_ptr, render, &cub);
	mlx_hook(cub.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	return (ft_free_cube3d(&cub), SUCCESS);
}
