/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:51:21 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 19:49:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

static int	ft_row_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	ft_col_is_empty(t_env *env, int col)
{
	int	row;

	row = 0;
	if (col < 0 || col >= env->mapw)
		return (FAILURE);
	while (row < env->maph)
	{
		if (env->map[col][row] != ' ')
			return (FAILURE);
		row++;
	}
	return (SUCCESS);
}

static int	ft_check_rows(t_env *env)
{
	int	row;

	row = 0;
	while (row < env->maph)
	{
		if (ft_row_is_empty(env->map[row]) == FAILURE)
			break;
		row++;
	}
	if (row == env->maph)
		return (FAILURE);
	row = env->mapw - 1;
	while (row >= 0)
	{
		if (ft_row_is_empty(env->map[row]) == FAILURE)
			break;
		row--;
	}
	if (row == 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_check_cols(t_env *env)
{
	int	col;

	col = 0;
	while(col < env->mapw)
	{
		if (ft_col_is_empty(env, col) == FAILURE)
			break;
		col++;
	}
	if (col == env->mapw)
		return (FAILURE);
	col = env->maph - 1;
	while (col > 0)
	{
		if (ft_col_is_empty(env, col) == FAILURE)
			break;
		col--;
	}
	if (col == 0)
		return (FAILURE);
	return (SUCCESS);
}

static void	ft_flood_fill_on_walls(t_env *env, int px, int py)
{
	char	*wall;
	int		wx;
	int		wy;

	wall = ft_strchr(env->map[px] + py, '1');
	if (!wall)
		return ;
	printf("wall found\n");
	env->map[px][py + (wall - env->map[px])] = 'x';
}

int	ft_map_is_closed(t_env *env)
{
	int		px;
	int		py;

	px = (int)env->px;
	py = (int)env->py;
	printf("player at %d %d\n", px, py);
	if (ft_check_rows(env) == FAILURE)
		return (ft_err("Map is not closed ROWS\n", FAILURE));
	if (ft_check_cols(env) == FAILURE)
		return (ft_err("Map is not closed COLS\n", FAILURE));
	if (ft_flood_fill(env->map, px, py, env->mapw, env->maph) == FAILURE)
		return (ft_err("Map is not closed\n", FAILURE));
	ft_replace_map(env->map, env->mapw, env->maph, 'x', '0');
	ft_flood_fill_on_walls(env, px, py);
	return (SUCCESS);
}
