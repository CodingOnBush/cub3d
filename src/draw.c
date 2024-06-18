/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:27:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/18 17:53:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_cub3d *cub, int c, int r, int color)
{
	char	*dst;

	if (c < 0 || c >= cub->cst.width || r < 0 || r >= cub->cst.height)
		return ;
	dst = cub->img.addr + (r * cub->img.line_len + c * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}

// static int	ft_get_pixel(t_cub3d *c, int row, int lineHeight)
// {
// 	t_img	tex;
// 	int		color;

// 	tex = c->buf;
// 	color = *(unsigned int *)(tex.addr + (row * tex.line_len + c->ray.texCol * (tex.bpp / 8)));
// 	c->ray.texCol = (c->ray.texCol + 1) % tex.w;
// 	return (color);
// }

static int	ft_get_color(t_cub3d *c, int x, int y)
{
	t_img	tex;
	int		color;

	tex = c->buf;
	if (x < 0 || x >= tex.w || y < 0 || y >= tex.h)
		return (0);
	color = *(unsigned int *)(tex.addr + (y * tex.line_len + x * (tex.bpp / 8)));
	return (color);
}

void	ft_draw_column(t_cub3d *c, int col, double perpWallDist)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		row;
	double	ratio;
	int		color;

	lineHeight = (int)(c->cst.height / perpWallDist);
	drawStart = (-lineHeight / 2) + (c->cst.height / 2);
	drawEnd = lineHeight / 2 + c->cst.height / 2;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= c->cst.height)
		drawEnd = c->cst.height - 1;


	
	
	
	row = 0;
	while (row < drawStart)
	{
		ft_pixel_put(c, col, row, 0xFFFFFF);
		row++;
	}
	ratio = (drawEnd - drawStart) / c->buf.h;
	if (ratio <= 0)
		ratio = 1;
	while (row < drawEnd)
	{
		color = ft_get_color(c, c->ray.texCol, (int)(row / ratio) % c->buf.h);
		ft_pixel_put(c, col, row, color);
		row++;
	}
	c->ray.texCol = (c->ray.texCol + 1) % c->buf.w;
	while (row < c->cst.height)
	{
		ft_pixel_put(c, col, row, 0xFFFFFF);
		row++;
	}
}

void	ft_draw_texture(t_cub3d *c, t_img tex, int zoom)
{
	char	*tmp;
	int tex_col;
	int tex_row;

	tex_col = 0;
	while (tex_col < tex.w)
	{
		tex_row = 0;
		while (tex_row < tex.h)
		{
			tmp = tex.addr + (tex_row * tex.line_len + tex_col * (tex.bpp / 8));
			for (int win_col = 0; win_col < zoom; win_col++)
			{
				for (int win_row = 0; win_row < zoom; win_row++)
				{
					ft_pixel_put(c, (tex_col * zoom) + win_col, (tex_row * zoom) + win_row, *(unsigned int *)tmp);
				}	
			}
			tex_row++;
		}
		tex_col++;
	}
}
