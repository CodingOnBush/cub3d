/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/25 09:29:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// int worldMap[24][24]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// static void	ft_load_img(t_cub3d *cub, char *path, t_img *img)
// {
// 	img->mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, path, &(img->w), &(img->h));
// 	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->llen, &img->endian);
// }

// static void	ft_load_textures(t_cub3d *cub)
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (cub->buf[i].type == NORTH)
// 			ft_load_img(cub, cub->data.no, &cub->buf[i]);
// 		else if (cub->buf[i].type == SOUTH)
// 			ft_load_img(cub, cub->data.so, &cub->buf[i]);
// 		else if (cub->buf[i].type == EAST)
// 			ft_load_img(cub, cub->data.ea, &cub->buf[i]);
// 		else if (cub->buf[i].type == WEST)
// 			ft_load_img(cub, cub->data.we, &cub->buf[i]);
// 	}
	
// }

// static void	ft_destroy_textures(t_cub3d *cub)
// {
// 	for (int i = 0; i < 4; i++)
// 		mlx_destroy_image(cub->mlx.mlx_ptr, cub->buf[i].mlx_img);
// }

static int	render(t_cub3d *c)
{
	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->cst.width, c->cst.height);
	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.llen, &c->img.endian);

	// c->buf[0].mlx_img = mlx_xpm_file_to_image(c->mlx.mlx_ptr, "redbrick.xpm", &(c->buf[0].w), &(c->buf[0].h));
	// c->buf[0].addr = mlx_get_data_addr(c->buf[0].mlx_img, &c->buf[0].bpp, &c->buf[0].line_len, &c->buf[0].endian);
	
	// ft_load_textures(c);

	for (int col = 0; col < c->cst.width; col++)
		ft_draw(c, col);
	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
	// mlx_destroy_image(c->mlx.mlx_ptr, c->buf[0].mlx_img);
	// ft_destroy_textures(c);
	return (0);
}

static int	render2(t_env *env)
{

	env->img[CANVAS].mlx_img = mlx_new_image(env->mlx_ptr, env->winw, env->winh);
	env->img[CANVAS].addr = mlx_get_data_addr(env->img[CANVAS].mlx_img, &env->img[CANVAS].bpp, &env->img[CANVAS].llen, &env->img[CANVAS].endian);

	env->img[NORTH].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[NORTH].path, &env->img[NORTH].imgw, &env->img[NORTH].imgh);
	env->img[NORTH].addr = mlx_get_data_addr(env->img[NORTH].mlx_img, &env->img[NORTH].bpp, &env->img[NORTH].llen, &env->img[NORTH].endian);

	env->img[SOUTH].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[SOUTH].path, &env->img[SOUTH].imgw, &env->img[SOUTH].imgh);
	env->img[SOUTH].addr = mlx_get_data_addr(env->img[SOUTH].mlx_img, &env->img[SOUTH].bpp, &env->img[SOUTH].llen, &env->img[SOUTH].endian);

	env->img[WEST].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[WEST].path, &env->img[WEST].imgw, &env->img[WEST].imgh);
	env->img[WEST].addr = mlx_get_data_addr(env->img[WEST].mlx_img, &env->img[WEST].bpp, &env->img[WEST].llen, &env->img[WEST].endian);

	env->img[EAST].mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, env->img[EAST].path, &env->img[EAST].imgw, &env->img[EAST].imgh);
	env->img[EAST].addr = mlx_get_data_addr(env->img[EAST].mlx_img, &env->img[EAST].bpp, &env->img[EAST].llen, &env->img[EAST].endian);


	for (int col = 0; col < env->winw; col++)
	{
		ft_draw2(env, col);
	}
	


	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[CANVAS].mlx_img, 0, 0);
	
	// mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[NORTH].mlx_img, 0, 0);
	// mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[SOUTH].mlx_img, env->img[SOUTH].imgw * 1, 0);
	// mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[WEST].mlx_img, env->img[WEST].imgw * 2, 0);
	// mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img[EAST].mlx_img, env->img[EAST].imgw * 3, 0);

	mlx_destroy_image(env->mlx_ptr, env->img[CANVAS].mlx_img);
	mlx_destroy_image(env->mlx_ptr, env->img[NORTH].mlx_img);
	mlx_destroy_image(env->mlx_ptr, env->img[SOUTH].mlx_img);
	mlx_destroy_image(env->mlx_ptr, env->img[WEST].mlx_img);
	mlx_destroy_image(env->mlx_ptr, env->img[EAST].mlx_img);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;
	t_env	env;

	if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3d <map.file>\n", 2), FAILURE);
	
		
	// if (ft_init_cub3d(&cub) == FAILURE)
	// 	return (FAILURE);
	// if (ft_parsing(&cub, ac, av) == FAILURE)
	// 	return (FAILURE);
	// mlx_hook((void *)cub.mlx.win_ptr, 2, 1L << 0, ft_key_hook, &cub);
	// mlx_loop_hook(cub.mlx.mlx_ptr, render, &cub);
	// mlx_hook(cub.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &cub);
	// mlx_loop(cub.mlx.mlx_ptr);

	
	
	ft_init_env(&env);
	if (ft_parsing2(&env, av[1]) == FAILURE)
		return (FAILURE);
	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, env.winw, env.winh, "cub3d");
	mlx_hook((void *)env.win_ptr, 2, 1L << 0, ft_key_hook2, &env);
	mlx_loop_hook(env.mlx_ptr, render2, &env);
	mlx_hook(env.win_ptr, 17, 1L << 2, ft_win_cross, &env);
	mlx_loop(env.mlx_ptr);
	
	

	// ft_free_cube3d(&cub);
	ft_free_env(&env);
	return (SUCCESS);
}
