/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 15:57:47 by momrane          ###   ########.fr       */
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

static void	ft_load_img(t_cub3d *cub, char *path, t_img *img)
{
	img->mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, path, &(img->w), &(img->h));
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
}

static void	ft_load_textures(t_cub3d *cub)
{
	for (int i = 0; i < 4; i++)
	{
		if (cub->buf[i].type == NORTH)
			ft_load_img(cub, cub->data.no, &cub->buf[i]);
		else if (cub->buf[i].type == SOUTH)
			ft_load_img(cub, cub->data.so, &cub->buf[i]);
		else if (cub->buf[i].type == EAST)
			ft_load_img(cub, cub->data.ea, &cub->buf[i]);
		else if (cub->buf[i].type == WEST)
			ft_load_img(cub, cub->data.we, &cub->buf[i]);
	}
	
}

static void	ft_destroy_textures(t_cub3d *cub)
{
	for (int i = 0; i < 4; i++)
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->buf[i].mlx_img);
}

static int	render(t_cub3d *c)
{
	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->cst.width, c->cst.height);
	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);

	// c->buf[0].mlx_img = mlx_xpm_file_to_image(c->mlx.mlx_ptr, "redbrick.xpm", &(c->buf[0].w), &(c->buf[0].h));
	// c->buf[0].addr = mlx_get_data_addr(c->buf[0].mlx_img, &c->buf[0].bpp, &c->buf[0].line_len, &c->buf[0].endian);
	
	ft_load_textures(c);

	for (int col = 0; col < c->cst.width; col++)
		ft_draw(c, col);
	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
	// mlx_destroy_image(c->mlx.mlx_ptr, c->buf[0].mlx_img);
	ft_destroy_textures(c);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	if (ft_init_cub3d(&cub) == FAILURE)
		return (FAILURE);
	
	if (ft_parsing(&cub, ac, av) == FAILURE)
		return (FAILURE);
	
	// printf("map size = %d x %d\n", cub.data.mapw, cub.data.maph);

	// for (int c = 0; c < cub.data.maph; c++)
	// {
	// 	for (int r = 0; r < cub.data.mapw; r++)
	// 		printf("%c", cub.data.map[c][r]);
	// 	printf("\n");
	// }

	
	mlx_hook((void *)cub.mlx.win_ptr, 2, 1L << 0, ft_key_hook, &cub);
	mlx_loop_hook(cub.mlx.mlx_ptr, render, &cub);
	mlx_hook(cub.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	

	ft_free_cube3d(&cub);
	return (SUCCESS);
}
