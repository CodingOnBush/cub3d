/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:51:21 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 21:21:53 by momrane          ###   ########.fr       */
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

static int	ft_flood_fill2(char **map, int px, int py, int mapw, int maph)
{
	if (px < 0 || px >= mapw || py < 0 || py >= maph)
		return (FAILURE);
	if (map[px][py] == ' ' || map[px][py] == '?')
		return (SUCCESS);
	if (map[px][py] == '1')
		map[px][py] = '?';
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

static void	ft_flood_fill_wall(char **map, int wx, int wy, int mapw, int maph)
{
	if (wx < 0 || wx >= mapw || wy < 0 || wy >= maph)
		return ;
	map[wx][wy] = '%';
	ft_flood_fill(map, wx + 1, wy, mapw, maph);
	ft_flood_fill(map, wx - 1, wy, mapw, maph);
	ft_flood_fill(map, wx, wy + 1, mapw, maph);
	ft_flood_fill(map, wx, wy - 1, mapw, maph);
	ft_flood_fill(map, wx - 1, wy - 1, mapw, maph);
	ft_flood_fill(map, wx + 1, wy + 1, mapw, maph);
	ft_flood_fill(map, wx - 1, wy + 1, mapw, maph);
	ft_flood_fill(map, wx + 1, wy - 1, mapw, maph);
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
	int		col;
	int		c;
	int		r;

	col = 0;
	while(env->map[col][py] != '1')
		col++;
	wx = col;
	wy = py;
	// env->map[wx][wy] = '&';
	// printf("env->map[wx][wy] = %c\n", env->map[wx][wy]);
	ft_flood_fill_wall(env->map, wx, wy, env->mapw, env->maph);
	// r = 0;
	// while (r < env->maph)
	// {
	// 	c = 0;
	// 	while (c < env->mapw)
	// 	{
	// 		printf("%c", env->map[c][r]);
	// 		c++;
	// 	}
	// 	printf("\n");
	// 	r++;
	// }
}

int	ft_map_is_closed(t_env *env)
{
	int const	px = env->px;
	int const	py = env->py;

	if (ft_check_rows(env) == FAILURE)
		return (ft_err("Map is not closed ROWS\n", FAILURE));
	if (ft_check_cols(env) == FAILURE)
		return (ft_err("Map is not closed COLS\n", FAILURE));
	if (ft_flood_fill(env->map, px, py, env->mapw, env->maph) == FAILURE)
		return (ft_err("Map is not closed\n", FAILURE));
	ft_replace_map(env->map, env->mapw, env->maph, 'x', '0');
	return (SUCCESS);
}
