#include "../inc/cub3d.h"

static void	ft_pixel_put(t_img img, int col, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + col * (img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_column(t_cub3d *c, int x, double perpWallDist)
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	i;

	i = 0;
	lineHeight = (int)(c->cst.height / perpWallDist);
	drawStart = (-lineHeight / 2) + (c->cst.height / 2);
	drawEnd = lineHeight / 2 + c->cst.height / 2;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= c->cst.height)
		drawEnd = c->cst.height - 1;
	while (i < drawStart)
	{
		ft_pixel_put(c->img, x, i, 0xFFFFFF);
		i++;
	}
	while (i < drawEnd)
	{
		printf("address: %p\n", c->buf.addr);
		printf("line_len: %d\n", c->buf.line_len);
		printf("i * line_len: %d\n", i * c->buf.line_len);
		ft_pixel_put(c->img, x, i, *(unsigned int *)(c->buf.addr + (i * c->buf.line_len + x * (c->buf.bpp / 8))));
		i++;
	}
	while (i < c->cst.height)
	{
		ft_pixel_put(c->img, x, i, 0xFFFFFF);
		i++;
	}
}
