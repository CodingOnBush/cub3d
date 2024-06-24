/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 15:40:25 by momrane          ###   ########.fr       */
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

	while (row < env.maph)
	{
		col = 0;
		while (col < env.mapw)
		{
			printf("%c", map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
}


static void	ft_load_img(t_env *env, int type)
{
	t_img	*img;

	img = &(env->win.img[type]);
	// printf("path : %s\n", img->path);
	img->mlx_img = mlx_xpm_file_to_image(env->win.mlx_ptr, img->path, &(img->imgw), &(img->imgh));
	// printf("imgw: %d\n", img->imgw);
	// printf("imgh: %d\n", img->imgh);
	
	// printf("mlx_img: %p\n", img->mlx_img);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->llen, &img->endian);
	// printf("bpp: %d\n", img->bpp);
	// printf("llen: %d\n", img->llen);
	// printf("endian: %d\n", img->endian);
}

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
	t_img	*canva;

	canva = &(env->win.img[CANVAS]);
	canva->mlx_img = mlx_new_image(env->win.mlx_ptr, env->win.winw, env->win.winh);
	canva->addr = mlx_get_data_addr(canva->mlx_img, &canva->bpp, &canva->llen, &canva->endian);

	ft_load_img(env, NORTH);
	ft_load_img(env, SOUTH);
	ft_load_img(env, EAST);
	ft_load_img(env, WEST);

	// printf("file width: %d\n", env->win.winw);
	for (int col = 0; col < env->win.winw; col++)
	{
		// printf("coucou\n");
		ft_draw(env, col);
	}
	mlx_put_image_to_window(env->win.mlx_ptr, env->win.win_ptr, canva->mlx_img, 0, 0);
	
	mlx_destroy_image(env->win.mlx_ptr, canva->mlx_img);
	mlx_destroy_image(env->win.mlx_ptr, env->win.img[NORTH].mlx_img);
	mlx_destroy_image(env->win.mlx_ptr, env->win.img[SOUTH].mlx_img);
	mlx_destroy_image(env->win.mlx_ptr, env->win.img[EAST].mlx_img);
	mlx_destroy_image(env->win.mlx_ptr, env->win.img[WEST].mlx_img);
	
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
	ft_print_map(*env);
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
