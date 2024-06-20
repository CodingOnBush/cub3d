/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 18:16:49 by vvaudain         ###   ########.fr       */
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
		double oldDirX = c->cst.dirX;
		c->cst.dirX = c->cst.dirX * cos(c->cst.rs) - c->cst.dirY * sin(c->cst.rs);
		c->cst.dirY = oldDirX * sin(c->cst.rs) + c->cst.dirY * cos(c->cst.rs);
		double oldPlaneX = c->cst.planeX;
		c->cst.planeX = c->cst.planeX * cos(c->cst.rs) - c->cst.planeY * sin(c->cst.rs);
		c->cst.planeY = oldPlaneX * sin(c->cst.rs) + c->cst.planeY * cos(c->cst.rs);
	}
	else if (keycode == XK_a || keycode == XK_A)
	{
		if (c->data.map[(int)(c->data.px - c->cst.planeX * c->cst.ms)][(int)(c->data.py)] == '0')
			c->data.px -= c->cst.planeX * c->cst.ms;
		if (c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.planeY * c->cst.ms)] == '0')
			c->data.py -= c->cst.planeY * c->cst.ms;
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		if (c->data.map[(int)(c->data.px + c->cst.planeX * c->cst.ms)][(int)(c->data.py)] == '0')
			c->data.px += c->cst.planeX * c->cst.ms;
		if (c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.planeY * c->cst.ms)] == '0')
			c->data.py += c->cst.planeY * c->cst.ms;
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		if(c->data.map[(int)(c->data.px + c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
			c->data.px += c->cst.dirX * c->cst.ms;
		if(c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.dirY * c->cst.ms)] == '0')
			c->data.py += c->cst.dirY * c->cst.ms;
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		if(c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
			c->data.px -= c->cst.dirX * c->cst.ms;
		if(c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.dirY * c->cst.ms)] == '0')
			c->data.py -= c->cst.dirY * c->cst.ms;
	}
	// else if (keycode == XK_Escape)
	// {
	// 	printf("Escape key pressed, so byeee !\n");
	// 	ft_free_cube3d(c);
	// 	exit(0);
	// }
	// else if (keycode == XK_Down)
	// {
	// 	if(c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
	// 		c->data.px -= c->cst.dirX * c->cst.ms;
	// 	if(c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.dirY * c->cst.ms)] == '0')
	// 		c->data.py -= c->cst.dirY * c->cst.ms;
	// }
	// else if (keycode == XK_Up)
	// {
	// 	if(c->data.map[(int)(c->data.px + c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
	// 		c->data.px += c->cst.dirX * c->cst.ms;
	// 	if(c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.dirY * c->cst.ms)] == '0')
	// 		c->data.py += c->cst.dirY * c->cst.ms;
	// }
	else if (keycode == XK_Escape)
	{
		printf("Escape key pressed, so byeee !\n");
		ft_free_cube3d(c);
		exit(0);
	}
	return (0);
}
