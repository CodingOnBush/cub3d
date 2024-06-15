#include "../inc/cub3d.h"

void	ft_draw_column(t_cub3d c, int x, double perpWallDist)
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	i;

	i = 0;
	lineHeight = (int)(c.cst.height / perpWallDist);
	drawStart = (-lineHeight / 2) + (c.cst.height / 2);
	drawEnd = lineHeight / 2 + c.cst.height / 2;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= c.cst.height)
		drawEnd = c.cst.height - 1;
	while (i < drawStart)
		ft_pixel_put(c.img, x, i++, 0xFF0000);
	while (i < drawEnd)
		ft_pixel_put(c.img, x, i++, 0x00FF00);
	while (i < c.cst.height)
		ft_pixel_put(c.img, x, i++, 0x00FF00);
}
