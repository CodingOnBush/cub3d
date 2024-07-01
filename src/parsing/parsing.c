/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:14:09 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 11:30:34 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_check_invalid_char(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	if (map == NULL || map[0] == NULL)
		return (ft_err("Map missing", FAILURE));
	col = 0;
	row = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph)
		{
			if (ft_strchr(" 01NSEW", map[col][row]) == NULL)
				return (ft_err("Invalid character in map", FAILURE));
			row++;
		}
		col++;
	}
	return (SUCCESS);
}

static void	ft_remove_all_spaces_at_end(t_env *env)
{
	int	row;
	int	col;

	row = 0;
	while (row < env->maph)
	{
		col = env->mapw - 1;
		while (col >= 0 && env->map[col][row] == ' ')
		{
			env->map[col][row] = ' ';
			col--;
		}
		row++;
	}
}

static int	ft_reverse_map(t_env *env)
{
	char	**cpy;
	int		row;
	int		col;

	cpy = (char **)malloc(sizeof(char *) * (env->mapw));
	if (!cpy)
		return (FAILURE);
	col = 0;
	while (col < env->mapw)
	{
		cpy[col] = malloc(sizeof(char) * env->maph);
		if (!cpy[col])
			return (ft_free_array(cpy, col), FAILURE);
		row = 0;
		while (row < env->maph)
		{
			cpy[col][row] = env->map[env->mapw - col - 1][row];
			row++;
		}
		col++;
	}
	ft_free_array(env->map, env->mapw);
	env->map = cpy;
	ft_remove_all_spaces_at_end(env);
	return (SUCCESS);
}

static int	ft_check_textures(t_env *env)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		printf("path = [%s]\n", env->img[i].path);
		if (ft_check_file_extension(env->img[i].path, ".xpm") == FAILURE)
			return (FAILURE);
		if (env->img[i].path == NULL)
			return (ft_err("Missing texture", FAILURE));
		fd = open(env->img[i].path, O_RDONLY);
		if (fd == -1)
			return (perror(env->img[i].path), FAILURE);
		close(fd);
		i++;
	}
	return (SUCCESS);
}

int	ft_parsing(t_env *env, char *cubfile)
{
	if (ft_check_file(cubfile) == FAILURE)
		return (FAILURE);
	if (ft_get_all_lines(env, cubfile) == FAILURE)
		return (FAILURE);
	if (ft_analyze_file(env) == FAILURE)
		return (FAILURE);
	if (ft_check_invalid_char(env) == FAILURE)
		return (FAILURE);
	ft_reverse_map(env);
	if (ft_find_player(env) == FAILURE)
		return (FAILURE);
	if (ft_map_is_closed(env) == FAILURE)
		return (FAILURE);
	if (ft_check_textures(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
