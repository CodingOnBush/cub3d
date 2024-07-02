/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:34:53 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 18:05:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_rgb_to_int(int color[3])
{
	int	red;
	int	green;
	int	blue;

	red = color[0] << 16;
	green = color[1] << 8;
	blue = color[2];
	return (red | green | blue);
}

void	ft_replace_map(char **map, int mapw, int maph)
{
	int	row;
	int	col;

	col = 0;
	while (col < mapw)
	{
		row = 0;
		while (row < maph)
		{
			if (map[col][row] == 'x')
				map[col][row] = '0';
			row++;
		}
		col++;
	}
}

void	ft_err_title(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n↳ ", 2);
	ft_putstr_fd(RESET, 2);
}
