/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 17:19:11 by momrane          ###   ########.fr       */
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
	for (int col = 0; col < c->cst.width; col++)
	{ 
		// ft_draw_column(c, col, ft_get_perp_wall_dist(c, col));
		ft_get_perp_wall_dist(c, col);
	}
	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
	mlx_destroy_image(c->mlx.mlx_ptr, c->buf.mlx_img);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	env;

	ft_init_cst(&env.cst);
	ft_init_ray(&env.ray);
	ft_init_sim(&env.sim);
	env.sim.mapw = 24;
	env.sim.maph = 24;
	env.sim.px = 22;
	env.sim.py = 12;

	env.buf.w = 0;
	env.buf.h = 0;
	env.buf.addr = NULL;
	env.buf.mlx_img = NULL;
	env.buf.line_len = 0;
	env.buf.bpp = 0;
	
	env.img.w = 0;
	env.img.h = 0;
	env.img.mlx_img = NULL;
	env.img.addr = NULL;
	env.img.line_len = 0;
	env.img.bpp = 0;
	
	
	env.mlx.mlx_ptr = mlx_init();
	if (!(env.mlx.mlx_ptr))
		return (printf("Error : mlx_init() failed\n"), FAILURE);
	env.mlx.win_ptr = mlx_new_window(env.mlx.mlx_ptr, env.cst.width, env.cst.height, "?");
	if (!(env.mlx.win_ptr))
		return (printf("Error : mlx_new_window() failed\n"), free(env.mlx.mlx_ptr), FAILURE);
	mlx_key_hook(env.mlx.win_ptr, ft_key_hook, &env);
	mlx_loop_hook(env.mlx.mlx_ptr, render, &env);
	mlx_hook(env.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &env);
	mlx_loop(env.mlx.mlx_ptr);
	return (ft_free_cube3d(&env), SUCCESS);
}
