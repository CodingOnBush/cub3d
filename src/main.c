/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 15:42:10 by momrane          ###   ########.fr       */
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

static int	render(t_cub3d *c)
{
	c->buf.w = 0;
	c->buf.h = 0;
	c->img.w = 0;
	c->img.h = 0;
	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->cst.width, c->cst.height);
	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);
	c->buf.mlx_img = mlx_xpm_file_to_image(c->mlx.mlx_ptr, "redbrick.xpm", &(c->buf.w), &(c->buf.h));
	c->buf.addr = mlx_get_data_addr(c->buf.mlx_img, &c->buf.bpp, &c->buf.line_len, &c->buf.endian);
	for (int col = 0; col < c->cst.width; col++)
		ft_draw(c, col);
	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
	mlx_destroy_image(c->mlx.mlx_ptr, c->buf.mlx_img);
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

	// printf("0:0 = %c\n", cub.data.map[0][0]);
	// printf("0:1 = %c\n", cub.data.map[0][1]);
	// printf("0:2 = %c\n", cub.data.map[0][2]);

	// printf("0:0 = %c\n", cub.data.map[0][0]);
	// printf("1:0 = %c\n", cub.data.map[1][0]);
	// printf("2:0 = %c\n", cub.data.map[2][0]);

	
	mlx_hook((void *)cub.mlx.win_ptr, 2, 1L << 0, ft_key_hook, &cub);
	mlx_loop_hook(cub.mlx.mlx_ptr, render, &cub);
	mlx_hook(cub.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	

	ft_free_cube3d(&cub);
	return (SUCCESS);
}
