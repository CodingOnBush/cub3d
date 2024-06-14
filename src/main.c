/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:36:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/14 17:13:49 by momrane          ###   ########.fr       */
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


#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
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

double posX = 22, posY = 12;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

double time = 0; //time of current frame
double oldTime = 0; //time of previous frame

double moveSpeed = 0.1; //the constant value is in squares/second
double rotSpeed = 0.1; //the constant value is in radians/second

// void	img_pix_put(t_img *img, int x, int y, int color)
// {
//     char    *pixel;

//     pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
//     *(int *)pixel = color;
// }

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


void	vertLine(int x, int drawStart, int drawEnd, t_img img)
{
	int color = 0x00FF00;
	for (int y = 0; y < drawStart; y++)
	{
		img_pix_put(&img, x, y, 0xFF0000);
	}
	
	for(int y = drawStart; y < drawEnd; y++)
	{
		img_pix_put(&img, x, y, color);
	}

	for (int y = drawEnd; y < screenHeight; y++)
	{
		img_pix_put(&img, x, y, 0x0000FF);
	}
}

int	ft_key_hook(int keycode, t_cub3d *c)
{
	if (keycode == XK_Right)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	else if (keycode == XK_Left)
	{
		 //both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	else if (keycode == XK_Down)
	{

		if(worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == false)
			posX -= dirX * moveSpeed;
		if(worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == false)
			posY -= dirY * moveSpeed;
	}
	else if (keycode == XK_Up)
	{
		if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == false)
			posX += dirX * moveSpeed;
		if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == false)
			posY += dirY * moveSpeed;
	}
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
	c->img.mlx_img = mlx_new_image(c->mlx.mlx_ptr, c->width, c->height);
	c->img.addr = mlx_get_data_addr(c->img.mlx_img, &c->img.bpp, &c->img.line_len, &c->img.endian);
	
	
	for (size_t x = 0; x < screenWidth; x++)
	{
      double cameraX = 2 * x / (double)screenWidth - 1; 
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      int mapX = (int)(posX);
      int mapY = (int)(posY);
      double sideDistX;
      double sideDistY;
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      double perpWallDist;
      int stepX;
      int stepY;
      int hit = 0;
      int side;
      
	  if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
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
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
       if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY); 
	  
      int lineHeight = (int)(screenHeight / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      
	  if(drawStart < 0)
	  	drawStart = 0;
      
	  int drawEnd = lineHeight / 2 + screenHeight / 2;
      
	  if(drawEnd >= screenHeight)
	  	drawEnd = screenHeight - 1;
		
		vertLine(x, drawStart, drawEnd, c->img);
	}
	

	// img_pix_put(&c->img, screenHeight/2, screenWidth/2, 0xFF0000);


	mlx_put_image_to_window(c->mlx.mlx_ptr, c->mlx.win_ptr, c->img.mlx_img, 0, 0);
	mlx_destroy_image(c->mlx.mlx_ptr, c->img.mlx_img);

	
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	c;

	c.width = screenWidth;
	c.height = screenHeight;
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
