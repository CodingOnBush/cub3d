/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/21 11:45:01 by momrane          ###   ########.fr       */
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

// static void	ft_load_img(t_env *env, char *path, t_img *img)
// {
// 	img->mlx_img = mlx_xpm_file_to_image(file->mlx.mlx_ptr, path, &(img->w), &(img->h));
// 	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
// }

// static void	ft_load_textures(t_env *env)
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (file->buf[i].type == NORTH)
// 			ft_load_img(file, file->data.no, &file->buf[i]);
// 		else if (file->buf[i].type == SOUTH)
// 			ft_load_img(file, file->data.so, &file->buf[i]);
// 		else if (file->buf[i].type == EAST)
// 			ft_load_img(file, file->data.ea, &file->buf[i]);
// 		else if (file->buf[i].type == WEST)
// 			ft_load_img(file, file->data.we, &file->buf[i]);
// 	}
	
// }

// static void	ft_destroy_textures(t_env *env)
// {
// 	for (int i = 0; i < 4; i++)
// 		mlx_destroy_image(file->mlx.mlx_ptr, file->buf[i].mlx_img);
// }

// static int	render(t_env *c)
// {
// 	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->cst.width, c->cst.height);
// 	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);

// 	// c->buf[0].mlx_img = mlx_xpm_file_to_image(c->mlx.mlx_ptr, "redbrick.xpm", &(c->buf[0].w), &(c->buf[0].h));
// 	// c->buf[0].addr = mlx_get_data_addr(c->buf[0].mlx_img, &c->buf[0].bpp, &c->buf[0].line_len, &c->buf[0].endian);
	
// 	ft_load_textures(c);

// 	for (int col = 0; col < c->cst.width; col++)
// 		ft_draw(c, col);
// 	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
// 	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
// 	// mlx_destroy_image(c->mlx.mlx_ptr, c->buf[0].mlx_img);
// 	ft_destroy_textures(c);
// 	return (0);
// }

static void	ft_print_map(t_env env)
{
	int col = 0;
	int row = 0;

	while (col < env.map.maph)
	{
		row = 0;
		while (row < env.map.mapw)
			printf("%c", env.map.map[col][row++]);
		printf("\n");
		col++;
	}
}

static int	ft_launch_game(t_env *env)
{
	env->win.mlx = mlx_init();
	if (!(env->win.mlx))
		return (ft_err("mlx_init() failed", FAILURE));
	env->win.win = mlx_new_window(env->win.mlx, env->win.winw, env->win.winh, "❤️ CUB42D ❤️");
	if (!(env->win.win))
	{
		free(env->win.mlx);
		return (ft_err("mlx_new_window() failed", FAILURE));
	}
	// mlx_hook((void *)env.mlx.win_ptr, 2, 1L << 0, ft_key_hook, &env);
	// mlx_loop_hook(env.mlx.mlx_ptr, render, &env);
	// mlx_hook(env.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &env);
	// mlx_loop(env.mlx.mlx_ptr);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3d <map.file>\n", 2), FAILURE);
	ft_init_env(&env);
	if (ft_parsing(&env, av[1]) == FAILURE)
		return (ft_free_env(&env), FAILURE);


	printf("map size = %d x %d\n", env.map.mapw, env.map.maph);

	ft_print_map(env);
	
	// if (ft_launch_game(&env) == FAILURE)
	// 	return (FAILURE);
	

	

	

	ft_free_env(&env);
	return (SUCCESS);
}
