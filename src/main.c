/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 14:24:22 by momrane          ###   ########.fr       */
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

static void	ft_print_map(t_env env)
{
	int 	col = 0;
	int 	row = 0;
	char	**map = env.map;

	while (col < env.maph)
	{
		row = 0;
		while (row < env.mapw)
		{
			printf("%c", map[col][row]);
			row++;
		}
		printf("\n");
		col++;
	}
}


// static void	ft_load_img(t_cub3d *cub, char *path, t_img *img)
// {
// 	img->mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, path, &(img->w), &(img->h));
// 	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
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

static int	render(t_env *env)
{
	env->win.img->mlx_img = mlx_new_image(env->win.mlx_ptr, env->file.width, env->file.height);
	env->win.img[0].addr = mlx_get_data_addr(env->win.img->mlx_img, &env->win.img[0].bpp, &env->win.img[0].llen, &env->win.img[0].endian);

	// env->buf[0].mlx_img = mlx_xpm_file_to_image(env->win.mlx_ptr, "redbrick.xpm", &(env->buf[0].w), &(env->buf[0].h));
	// env->buf[0].addr = mlx_get_data_addr(env->buf[0].mlx_img, &env->buf[0].bpp, &env->buf[0].line_len, &env->buf[0].endian);
	
	// ft_load_textures(env);

	for (int col = 0; col < env->file.width; col++)
		ft_draw(env, col);
	mlx_put_image_to_window(env->win.mlx_ptr, env->win.win_ptr, env->win.img->mlx_img, 0, 0);
	mlx_destroy_image(env->win.mlx_ptr, env->win.img->mlx_img);
	// mlx_destroy_image(env->win.mlx_ptr, env->buf[0].mlx_img);
	// ft_destroy_textures(env);
	return (0);
}

static int	ft_launch_game(t_env *env)
{
	printf("Launching game...\n");
	env->win.mlx_ptr = mlx_init();
	if (!(env->win.mlx_ptr))
		return (ft_err("mlx_init() failed", FAILURE));
	env->win.win_ptr = mlx_new_window(env->win.mlx_ptr, env->win.winw, env->win.winh, "❤️ CUB42D ❤️");
	if (!(env->win.win_ptr))
	{
		free(env->win.mlx_ptr);
		return (ft_err("mlx_new_window() failed", FAILURE));
	}
	mlx_hook((void *)env->win.win_ptr, 2, 1L << 0, ft_key_hook, env);
	mlx_loop_hook(env->win.mlx_ptr, render, env);
	mlx_hook(env->win.win_ptr, 17, 1L << 2, ft_win_cross, env);
	mlx_loop(env->win.mlx_ptr);
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
	// ft_print_map(env);
	
	if (ft_launch_game(&env) == FAILURE)
		return (FAILURE);
	
	ft_free_env(&env);
	return (SUCCESS);
}
