/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:51:21 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 12:12:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_flood_fill(char **map, int px, int py, int mapw, int maph)
{
	if (px < 0 || px >= mapw || py < 0 || py >= maph)
		return (FAILURE);
	if (map[px][py] == '1' || map[px][py] == 'x')
		return (SUCCESS);
	if (map[px][py] == '0')
		map[px][py] = 'x';
	else
		return (FAILURE);
	if (ft_flood_fill(map, px + 1, py, mapw, maph) == FAILURE)
		return (FAILURE);
	if (ft_flood_fill(map, px - 1, py, mapw, maph) == FAILURE)
		return (FAILURE);
	if (ft_flood_fill(map, px, py + 1, mapw, maph) == FAILURE)
		return (FAILURE);
	if (ft_flood_fill(map, px, py - 1, mapw, maph) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	ft_replace_map(char **map, int mapw, int maph, char c1, char c2)
{
	int	row;
	int	col;

	col = 0;
	while (col < mapw)
	{
		row = 0;
		while (row < maph)
		{
			if (map[col][row] == c1)
				map[col][row] = c2;
			row++;
		}
		col++;
	}
}

static int	ft_check_cols(t_env *env)
{
	int	col;
	int	row;

	col = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph && ft_iswhitespace(env->map[col][row]) == YES)
			row++;
		if (row == env->maph)
			return (FAILURE);
		col++;
	}
	return (SUCCESS);
}

static int    ft_check_rows(t_env *env)
{
    int    row;
    int    col;

    row = 0;
    while (row < env->maph)
    {
        col = 0;
        if (env->map[col][row] && env->map[col][row] == '\0')
            return (ft_err("Map is not closed\n", FAILURE));
        while (col < env->mapw && env->map[col][row] && env->map[col][row] == ' ')
            col++;
        if (col == env->mapw)
            return (FAILURE);
        row++;
    }
    return (SUCCESS);
}

int	ft_map_is_closed(t_env *env)
{
	int const	px = env->px;
	int const	py = env->py;

	if (ft_check_rows(env) == FAILURE)
		return (ft_err("Empty line in map\n", FAILURE));
	if (ft_check_cols(env) == FAILURE)
		return (ft_err("Map is not closed COLS\n", FAILURE));
	if (ft_flood_fill(env->map, px, py, env->mapw, env->maph) == FAILURE)
		return (ft_err("Map is not closed\n", FAILURE));
	ft_replace_map(env->map, env->mapw, env->maph, 'x', '0');
	return (SUCCESS);
}
