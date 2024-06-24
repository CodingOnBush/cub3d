/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/24 13:10:58 by momrane          ###   ########.fr       */
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
		// printf("[%d]\t[%s]\n", row, env->file.content[row]);
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

static int	ft_create_map(t_env *env, char **content)
{
	char	**cpy;
	int		row;
	int		col;
	char	*line;

	env->map = (char **)malloc(sizeof(char *) * env->maph);
	if (!env->map)
		return (FAILURE);
	row = 0;
	while (row < env->maph)
	{
		env->map[row] = malloc(sizeof(char) * env->mapw);
		if (!env->map[row])
			return (ft_free_array(env->map, row), FAILURE);
		col = 0;
		line = *content;
		while (*line != '\0')
		{
			env->map[row][col] = *line;
			col++;
			line++;
		}
		while (col < env->mapw)
		{
			env->map[row][col] = '#';
			col++;
		}
		content++;
		row++;
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
			printf("%c", map[row][col]);
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

static int	ft_analyze_file(t_env *env)
{
	char	**content;
	char	**split;

	content = env->file.content;
	while (*content != NULL)
	{
		split = ft_split(*content, ' ');
		if (ft_get_infos(env, split) == STOP)
			break ;
		content++;
	}
	if (env->file.count != 6)
		return (ft_err("Wrong infos about game", FAILURE));
	ft_set_mapsizes(env, content);// ici on set les tailles de la map
	// printf("mapw = %d\n", env->mapw);
	// printf("maph = %d\n", env->maph);
	// ensuite on crée la map et on la remplit en se promenant dans le tableau content
	if (ft_create_map(env, content) == FAILURE)
		return (FAILURE);
	
	// if (ft_create_map(env, content) == FAILURE)
	// 	return (FAILURE);
	// ft_print_map(env);
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
	while (row < env->maph)
	{
		col = 0;
		while (col < env->mapw)
		{
			if (ft_strchr(" 01NSEW#", map[row][col]) == NULL)
				return (ft_err("Invalid character in map", FAILURE));
			col++;
		}
		row++;
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
	if (ft_check_map(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
