/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 11:25:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_win_cross(t_cub3d *param)
{
	printf("Window closed with the red cross\n");
	ft_free_cube3d(param);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_cub3d *c)
{
	double	oldDirX = c->cst.dirX;
	double	oldPlaneX = c->cst.planeX;

	if (keycode == XK_Right)
	{
		c->cst.dirX = c->cst.dirX * cos(-c->cst.rs) - c->cst.dirY * sin(-c->cst.rs);
		c->cst.dirY = oldDirX * sin(-c->cst.rs) + c->cst.dirY * cos(-c->cst.rs);
		c->cst.planeX = c->cst.planeX * cos(-c->cst.rs) - c->cst.planeY * sin(-c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(-c->cst.rs) + c->cst.planeY * cos(-c->cst.rs);
	}
	else if (keycode == XK_Left)
	{
		//both camera direction and camera plane must be rotated
		c->cst.dirX = c->cst.dirX * cos(c->cst.rs) - c->cst.dirY * sin(c->cst.rs);
		c->cst.dirY = oldDirX * sin(c->cst.rs) + c->cst.dirY * cos(c->cst.rs);
		c->cst.planeX = c->cst.planeX * cos(c->cst.rs) - c->cst.planeY * sin(c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(c->cst.rs) + c->cst.planeY * cos(c->cst.rs);
	}
	else if (keycode == XK_Down)
	{
		printf("[%d]\n", c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)c->data.py]);
		if(c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)c->data.py] != '0')
		{
			printf("go\n");
			c->data.px -= c->cst.dirX * c->cst.ms;
		}
		printf("[%d]\n", c->data.map[(int)c->data.px][(int)(c->data.py - c->cst.dirY * c->cst.ms)]);
		if(c->data.map[(int)c->data.px][(int)(c->data.py - c->cst.dirY * c->cst.ms)] != '0')
		{
			printf("go\n");
			c->data.py -= c->cst.dirY * c->cst.ms;
		}
	}
	else if (keycode == XK_Up)
	{
		if(c->data.map[(int)(c->data.px + c->cst.dirX * c->cst.ms)][(int)(c->data.py)] != '0')
			c->data.px += c->cst.dirX * c->cst.ms;
		if(c->data.map[(int)c->data.px][(int)(c->data.py + c->cst.dirY * c->cst.ms)] != '0')
			c->data.py += c->cst.dirY * c->cst.ms;
	}
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_cube3d(c);
		exit(0);
	}
	return (0);
}
