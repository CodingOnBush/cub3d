/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 16:52:12 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>
#include <stdbool.h>

static int	ft_win_cross(t_cub3d *param)
{
	printf("Window closed with the red cross\n");
	ft_free_cube3d(param);
	exit(0);
	return (0);
}

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

double posX = 22, posY = 12;  //col and y start position


static void	ft_pixel_put(t_img img, int col, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + col * (img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_key_hook(int keycode, t_cub3d *c)
{
	if (keycode == XK_Right)
	{
		double oldDirX = c->cst.dirX;
		c->cst.dirX = c->cst.dirX * cos(-c->cst.rs) - c->cst.dirY * sin(-c->cst.rs);
		c->cst.dirY = oldDirX * sin(-c->cst.rs) + c->cst.dirY * cos(-c->cst.rs);
		double oldPlaneX = c->cst.planeX;
		c->cst.planeX = c->cst.planeX * cos(-c->cst.rs) - c->cst.planeY * sin(-c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(-c->cst.rs) + c->cst.planeY * cos(-c->cst.rs);
	}
	else if (keycode == XK_Left)
	{
		 //both camera direction and camera plane must be rotated
		double oldDirX = c->cst.dirX;
		c->cst.dirX = c->cst.dirX * cos(c->cst.rs) - c->cst.dirY * sin(c->cst.rs);
		c->cst.dirY = oldDirX * sin(c->cst.rs) + c->cst.dirY * cos(c->cst.rs);
		double oldPlaneX = c->cst.planeX;
		c->cst.planeX = c->cst.planeX * cos(c->cst.rs) - c->cst.planeY * sin(c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(c->cst.rs) + c->cst.planeY * cos(c->cst.rs);
	}
	else if (keycode == XK_Down)
	{
		if(worldMap[(int)(posX - c->cst.dirX * c->cst.ms)][(int)posY] == false)
			posX -= c->cst.dirX * c->cst.ms;
		if(worldMap[(int)posX][(int)(posY - c->cst.dirY * c->cst.ms)] == false)
			posY -= c->cst.dirY * c->cst.ms;
	}
	else if (keycode == XK_Up)
	{
		if(worldMap[(int)(posX + c->cst.dirX * c->cst.ms)][(int)(posY)] == false)
			posX += c->cst.dirX * c->cst.ms;
		if(worldMap[(int)(posX)][(int)(posY + c->cst.dirY * c->cst.ms)] == false)
			posY += c->cst.dirY * c->cst.ms;
	}
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_cube3d(c);
		exit(0);
	}
	else if (keycode == XK_a)
	{
		c->cst.planeY += 0.2;
	}
	else if (keycode == XK_s)
	{
		c->cst.planeY -= 0.2;
	}
	
	printf("posX = %f, posY = %f\n", posX, posY);
	printf("planeX = %f, planeY = %f\n", c->cst.planeX, c->cst.planeY);
	printf("dirX = %f, dirY = %f\n\n", c->cst.dirX, c->cst.dirY);
	printf("planeX = %f, planeY = %f\n", c->cst.planeX, c->cst.planeY);
	printf("degrees = %f\n", atan(sqrt(pow(c->cst.planeX, 2) + pow(c->cst.planeY, 2))) * 180 / M_PI);
	return (0);
}

int	render(t_cub3d *c)
{
	int	w = 64;
	int	h = 64;
	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->cst.width, c->cst.height);
	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);
	
	c->buf.mlx_img = mlx_xpm_file_to_image(c->mlx.mlx_ptr, "redbrick.xpm", &w, &h);
	c->buf.addr = mlx_get_data_addr(c->buf.mlx_img, &c->buf.bpp, &c->buf.line_len, &c->buf.endian);
	
	for (int col = 0; col < c->cst.width; col++)
	{
		double cameraX = ((2 * col) / (double)c->cst.width) - 1;
		double rayDirX = c->cst.dirX + c->cst.planeX * cameraX;
		double rayDirY = c->cst.dirY + c->cst.planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		double	sideDistX;
		double	sideDistY;
		double	deltaDistX;
		double	deltaDistY;
		
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);

		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		
		

		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;

		if(rayDirX < 0)
			stepX = -1;
		else
			stepX = 1;
		
		if(rayDirY < 0)
			stepY = -1;
		else
			stepY = 1;

			
		
		if(rayDirX < 0)
			sideDistX = (posX - mapX) * deltaDistX;
		else
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;

		if(rayDirY < 0)
			sideDistY = (posY - mapY) * deltaDistY;
		else
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		

		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in col-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
			  sideDistX += deltaDistX;
			  mapX += stepX;
			  side = 0;
			}
			else
			{
			  sideDistY += deltaDistY;
			  mapY += stepY;
			  side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		ft_draw_column(c, col, perpWallDist);
	}


	/*
	
	static void	ft_pixel_put(t_img img, int col, int y, int color)
	char	*dst;

	dst = img.addr + (y * img.line_len + col * (img.bpp / 8));
	*(unsigned int *)dst = color;
	
	*/
	
	// char *tmp;
	// int i = 0;
	// for (int x = 0; x < 64; x++)
	// {
	// 	for (int y = 0; y < 64; y++)
	// 	{
	// 		tmp = (unsigned int *)(c->buf.addr + (y * c->buf.line_len + x * (c->buf.bpp / 8)));
	// 		ft_pixel_put(c->img, x, y, *(unsigned int *)tmp);
	// 		i++;
	// 	}
	// }

	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);
	mlx_destroy_image(c->mlx.mlx_ptr, c->buf.mlx_img);

	
	return (0);
}

/*

double c->cst.planeX = 0, c->cst.planeY = 0.66;

*/


int	main(int ac, char **av)
{
	t_cub3d	env;

	env.cst.width = 640;
	env.cst.height = 480;
	env.cst.ms = 0.5;
	env.cst.rs = 0.5;
	
	env.cst.planeX = 0;
	env.cst.planeY = 0.66;
	env.cst.dirX = -1;
	env.cst.dirY = 0;
	
	if (ft_parsing(ac, av, &env, &(env.data)) == FAILURE)
		return (FAILURE);
	env.mlx.mlx_ptr = mlx_init();
	if (!(env.mlx.mlx_ptr))
	{
		printf("Error : mlx_init() failed\n");
		return (FAILURE);
	}
	env.mlx.win_ptr = mlx_new_window(env.mlx.mlx_ptr, env.cst.width, env.cst.height,
			"window title");
	if (!(env.mlx.win_ptr))
	{
		printf("Error : mlx_new_window() failed\n");
		free(env.mlx.mlx_ptr);
		return (FAILURE);
	}
	mlx_key_hook(env.mlx.win_ptr, ft_key_hook, &env);
	mlx_loop_hook(env.mlx.mlx_ptr, render, &env);
	mlx_hook(env.mlx.win_ptr, 17, 1L << 2, ft_win_cross, &env);
	mlx_loop(env.mlx.mlx_ptr);
	ft_free_cube3d(&env);
	return (SUCCESS);
}
