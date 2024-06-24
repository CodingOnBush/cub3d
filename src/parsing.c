/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 15:41:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_check_file(char *file)
{
	int		fd;
	char	*ext;

	ext = ft_strchr(file, '.');
	if (!ext)
		return (ft_err("No file extension", FAILURE));
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (ft_err("Invalid file extension", FAILURE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	close(fd);
	return (SUCCESS);
}

static int	ft_count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static int	ft_get_all_lines(t_env *env, char *cubfile)
{
	int	fd;
	int	row;
	int	len;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
		return (perror(cubfile), FAILURE);
	env->file.height = ft_count_lines(cubfile);
	env->file.content = (char **)malloc(sizeof(char *) * (env->file.height
				+ 1));
	if (!env->file.content)
		return (FAILURE);
	row = 0;
	while (row < env->file.height)
	{
		env->file.content[row] = get_next_line(fd);
		len = ft_strlen(env->file.content[row]);
		if (len > 0 && env->file.content[row][len - 1] == '\n')
			env->file.content[row][len - 1] = '\0';
		row++;
	}
	env->file.content[row] = NULL;
	close(fd);
	return (SUCCESS);
}

static void	ft_print_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
	{
		printf("split is NULL\n");
		return ;
	}
	while (split[i])
	{
		printf("[%s] | ", split[i]);
		i++;
	}
	if (split[i] == NULL)
		printf("[NULL]");
	printf("\n\n");
}

static int	ft_get_infos(t_env *env, char **split)
{
	if (!split)
		return (GOON);
	if (!split[0])
		return (ft_free_split(split), GOON);
	if (ft_splitlen(split) == 2 && ft_get_id(split[0]) != -1)
	{
		env->file.texpath[ft_get_id(split[0])] = ft_strdup(split[1]);
		env->file.count++;
	}
	else if (ft_splitlen(split) == 4 && ft_get_id(split[0]) == CEIL || ft_get_id(split[0]) == FLOOR)
	{
		env->file.colors[ft_get_id(split[0])][R] = ft_atoi(split[1]);
		env->file.colors[ft_get_id(split[0])][G] = ft_atoi(split[2]);
		env->file.colors[ft_get_id(split[0])][B] = ft_atoi(split[3]);
		env->file.count++;
	}
	else
		return (ft_free_split(split), STOP);
	return (ft_free_split(split), GOON);
}

static int	ft_get_map(t_env *env, char *line)
{
	printf("line = [%s]\n", line);
	int	mapw;
	int	len;

	mapw = 0;
	while (line[mapw])
		mapw++;
	return (SUCCESS);
}

static void	ft_print_file_infos(t_env *env)
{
	printf("NO = [%s]\n", env->file.texpath[NORTH]);
	printf("SO = [%s]\n", env->file.texpath[SOUTH]);
	printf("WE = [%s]\n", env->file.texpath[WEST]);
	printf("EA = [%s]\n", env->file.texpath[EAST]);
	printf("FLOOR = [%d, %d, %d]\n", env->file.colors[FLOOR][R], env->file.colors[FLOOR][G], env->file.colors[FLOOR][B]);
	printf("CEIL = [%d, %d, %d]\n", env->file.colors[CEIL][R], env->file.colors[CEIL][G], env->file.colors[CEIL][B]);
}

static void	ft_free_array(char **array, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(array[i++]);
	free(array);
}

static int	ft_create_map(t_env *env)
{
	char	**cpy;
	int		row;
	int		col;

	env->map = (char **)malloc(sizeof(char *) * env->mapw);
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
	return (SUCCESS);
}

static void	ft_print_map(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	row = 0;
	while (row < env->maph)
	{
		col = 0;
		while (col < env->mapw)
		{
			printf("%c", map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
}

static void	ft_set_mapsizes(t_env *env, char **content)
{
	while (**content == '\n')
		content++;
	while (*content != NULL)
	{
		if (ft_strlen(*content) > env->mapw)
			env->mapw = ft_strlen(*content);
		content++;
		env->maph++;
	}
}

static void	ft_fill_map(t_env *env, char **content)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	row = 0;
	while (row < env->maph)
	{
		col = 0;
		while (col < env->mapw && content[row][col] != '\0')
		{
			map[col][row] = content[row][col];
			col++;
		}
		row++;
	}
}

static int	ft_analyze_file(t_env *env)
{
	char	**content;
	char	**split;

	content = env->file.content;
	env->file.texpath = (char **)malloc(sizeof(char *) * 5);
	if (!env->file.texpath)
		return (FAILURE);
	env->file.texpath[4] = NULL;
	while (*content != NULL)
	{
		split = ft_split(*content, ' ');
		if (ft_get_infos(env, split) == STOP)
			break ;
		content++;
	}
	if (env->file.count != 6)
		return (ft_err("Wrong infos about game", FAILURE));
	ft_set_mapsizes(env, content);
	if (ft_create_map(env) == FAILURE)
		return (FAILURE);
	ft_fill_map(env, content);
	return (SUCCESS);
}

static int	ft_check_map(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	if (map == NULL || map[0] == NULL)
		return (ft_err("Map empty", FAILURE));
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

static void	ft_find_player(t_env *env)
{
	char	**map;
	int		row;
	int		col;

	map = env->map;
	col = 0;
	while (col < env->mapw)
	{
		row = 0;
		while (row < env->maph)
		{
			if (ft_strchr("NSEW", map[col][row]) != NULL)
			{
				env->px = col;
				env->py = row;
				return ;
			}
			row++;
		}
		col++;
	}
}

static void	ft_set_images_path(t_env *env)
{
	t_img	*images;
	int		i;

	images = env->win.img;
	i = 0;
	while (i < 5)
	{
		images[i].path = ft_strdup(env->file.texpath[i]);
		i++;
	}
}

int	ft_parsing(t_env *env, char *cubfile)
{
	if (ft_check_file(cubfile) == FAILURE)
		return (FAILURE);
	if (ft_get_all_lines(env, cubfile) == FAILURE)
		return (FAILURE);
	if (ft_analyze_file(env) == FAILURE)
		return (FAILURE);
	if (ft_check_map(env) == FAILURE)
		return (FAILURE);
	
	// ft_print_file_infos(env);
	// ft_print_map(env);
	ft_find_player(env);
	ft_set_images_path(env);
	// printf("px = [%d], py = [%d]\n", env->px, env->py);
	return (SUCCESS);
}
