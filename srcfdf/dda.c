/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:47:20 by momrane           #+#    #+#             */
/*   Updated: 2024/02/29 17:21:35 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

// static int	ft_gradient(int c1, int c2, float factor)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = (int)(((c1 >> 16) & 0xff) + factor * (((c2 >> 16) & 0xff)
// 				- ((c1 >> 16) & 0xff)));
// 	g = (int)(((c1 >> 8) & 0xff) + factor * (((c2 >> 8) & 0xff)
// 				- ((c1 >> 8) & 0xff)));
// 	b = (int)((c1 & 0xff) + factor * ((c2 & 0xff) - (c1 & 0xff)));
// 	return ((r << 16) | (g << 8) | b);
// }

// static int ft_gradient(int color1, int color2, float factor)
// {
//     // Extract RGB components of color1
//     int r1 = (color1 >> 16) & 0xFF;
//     int g1 = (color1 >> 8) & 0xFF;
//     int b1 = color1 & 0xFF;

//     // Extract RGB components of color2
//     int r2 = (color2 >> 16) & 0xFF;
//     int g2 = (color2 >> 8) & 0xFF;
//     int b2 = color2 & 0xFF;

//     // Interpolate RGB components based on the factor
//     int r = (int)(r1 + factor * (r2 - r1));
//     int g = (int)(g1 + factor * (g2 - g1));
//     int b = (int)(b1 + factor * (b2 - b1));

//     // Construct the resulting color
//     int result_color = (r << 16) | (g << 8) | b;

//     return result_color;
// }


static int ft_gradient(int c1, int c2, float factor) {
    int r, g, b;

    r = (int)(((c1 >> 16) & 0xFF) + factor * (((c2 >> 16) & 0xFF) - ((c1 >> 16) & 0xFF)));
    g = (int)(((c1 >> 8) & 0xFF) + factor * (((c2 >> 8) & 0xFF) - ((c1 >> 8) & 0xFF)));
    b = (int)((c1 & 0xFF) + factor * ((c2 & 0xFF) - (c1 & 0xFF)));

    // Ensure RGB values are within the valid range
    r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
    g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
    b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

    return ((r << 16) | (g << 8) | b);
}




static float	ft_get_steps(float dx, float dy)
{
	int	steps;

	steps = abs((int)dy);
	if (abs((int)dx) > abs((int)dy))
		steps = abs((int)dx);
	return (steps);
}

static void	ft_draw_line(t_env *env, t_pt pt1, t_pt pt2)
{
	float	factor;
	float	steps;
	float	x;
	float	y;
	float	i;
	int		gradiant_color;

	x = pt1.x;
	y = pt1.y;
	i = 0;
	steps = ft_get_steps(pt2.x - pt1.x, pt2.y - pt1.y);
	while (i++ <= steps - 1)
	{
		factor = i / steps;
		gradiant_color = ft_gradient(pt1.color, pt2.color, factor);
		ft_put_pixel(env, (int)x, (int)y, gradiant_color);
		x += (pt2.x - pt1.x) / steps;
		y += (pt2.y - pt1.y) / steps;
	}
	i++;
}

void	ft_draw_dda(t_env *env, int r, int c)
{
	if (c < env->cols - 1)
		ft_draw_line(env, env->mat[r][c], env->mat[r][c + 1]);
	if (r < env->rows - 1)
		ft_draw_line(env, env->mat[r][c], env->mat[r + 1][c]);
}
