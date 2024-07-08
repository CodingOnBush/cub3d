/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:50:57 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 16:19:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_fill_row(t_env *env, char *line, int *row)
{
	int	col;

	if (ft_strchr(line, '\n') != NULL)
		*(ft_strchr(line, '\n')) = '\0';
	col = 0;
	while (line[col] != '\0')
	{
		env->map[col][*row] = line[col];
		col++;
	}
	*row = *row + 1;
	free(line);
}

static int	ft_fill_map(t_env *env, char *filepath)
{
	char	*line;
	int		fd;
	int		row;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (ft_err_title(), perror(filepath), FAILURE);
	line = get_next_line(fd);
	if (!line)
		return (ft_err("Missing map", FAILURE));
	while (env->mapstart > 0)
	{
		env->mapstart--;
		free(line);
		line = get_next_line(fd);
	}
	row = 0;
	while (line != NULL)
	{
		ft_fill_row(env, line, &row);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (close(fd), SUCCESS);
}

int	ft_create_map(t_env *env, char *filepath)
{
	int	row;
	int	col;

	env->map = (char **)malloc(sizeof(char *) * (env->mapw));
	if (!env->map)
		return (FAILURE);
	col = 0;
	while (col < env->mapw)
	{
		env->map[col] = malloc(sizeof(char) * env->maph);
		if (!env->map[col])
			return (ft_free_array(env->map, col), FAILURE);
		row = 0;
		while (row < env->maph)
		{
			env->map[col][row] = ' ';
			row++;
		}
		col++;
	}
	if (ft_fill_map(env, filepath) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
