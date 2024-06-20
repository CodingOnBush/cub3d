/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:16 by momrane           #+#    #+#             */
/*   Updated: 2024/06/20 23:12:39 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_win_cross(t_env *param)
{
	printf("Window closed with the red cross\n");
	ft_free_env(param);
	exit(0);
	return (0);
}

// int	ft_key_hook(int keycode, t_env *c)
// {
// 	if (keycode == XK_Right)
// 	{
// 		double oldDirX = c->cst.dirX;
// 		c->cst.dirX = c->cst.dirX * cos(-c->cst.rs) - c->cst.dirY * sin(-c->cst.rs);
// 		c->cst.dirY = oldDirX * sin(-c->cst.rs) + c->cst.dirY * cos(-c->cst.rs);
// 		double oldPlaneX = c->cst.planeX;
// 		c->cst.planeX = c->cst.planeX * cos(-c->cst.rs) - c->cst.planeY * sin(-c->cst.rs);
// 		c->cst.planeY = oldPlaneX * sin(-c->cst.rs) + c->cst.planeY * cos(-c->cst.rs);
// 	}
// 	else if (keycode == XK_Left)
// {
// 		double oldDirX = c->cst.dirX;
// 		c->cst.dirX = c->cst.dirX * cos(c->cst.rs) - c->cst.dirY * sin(c->cst.rs);
// 		c->cst.dirY = oldDirX * sin(c->cst.rs) + c->cst.dirY * cos(c->cst.rs);
// 		double oldPlaneX = c->cst.planeX;
// 		c->cst.planeX = c->cst.planeX * cos(c->cst.rs) - c->cst.planeY * sin(c->cst.rs);
// 		c->cst.planeY = oldPlaneX * sin(c->cst.rs) + c->cst.planeY * cos(c->cst.rs);
// 	}
// 	else if (keycode == XK_Down)
// 	{
// 		if(c->data.map[(int)(c->data.px - c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
// 			c->data.px -= c->cst.dirX * c->cst.ms;
// 		if(c->data.map[(int)(c->data.px)][(int)(c->data.py - c->cst.dirY * c->cst.ms)] == '0')
// 			c->data.py -= c->cst.dirY * c->cst.ms;
// 	}
// 	else if (keycode == XK_Up)
// 	{
// 		if(c->data.map[(int)(c->data.px + c->cst.dirX * c->cst.ms)][(int)(c->data.py)] == '0')
// 			c->data.px += c->cst.dirX * c->cst.ms;
// 		if(c->data.map[(int)(c->data.px)][(int)(c->data.py + c->cst.dirY * c->cst.ms)] == '0')
// 			c->data.py += c->cst.dirY * c->cst.ms;
// 	}
// 	else if (keycode == XK_Escape)
// 	{
// 		printf("Escape key pressed, so byeee !\n");
// 		ft_free_env(c);
// 		exit(0);
// 	}
// 	return (0);
// }
