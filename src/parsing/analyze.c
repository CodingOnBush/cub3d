/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:50:57 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 11:49:18 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_infos_error(t_env *env)
{
	if (ft_rgb_isvalid(env) == NO)
		return (ft_err("Invalid color", FAILURE));
	else if (env->file.count < 6)
		return (ft_err("Map infos not conform", FAILURE));
	else if (env->file.count >= 7)
		return (ft_err("Too much infos about game", FAILURE));
	return (SUCCESS);
}

static int	ft_set_mapsizes(t_env *env, char **content)
{
	int	len;

	while (*content != NULL && **content == '\0')
		content++;
	while (*(content) != NULL)
	{
		len = ft_strlen(*(content));
		if (len > env->mapw)
			env->mapw = len;
		(content)++;
		env->maph++;
	}
	if (env->mapw == 0 || env->maph == 0)
		return (ft_err("Map missing", FAILURE));
	if (env->mapw < 3 || env->maph < 3)
		return (ft_err("Map too small", FAILURE));
	return (SUCCESS);
}

static int	ft_set_mapsizes2(t_env *env, char **content)
{
	int	len;

	// if (content && *content)
	// 	printf("*content: [%s]\n", *content);
	while (*content != NULL && **content == '\0')
		content++;
	while (*(content) != NULL)
	{
		len = ft_strlen(*(content));
		if (len > env->mapw)
			env->mapw = len;
		(content)++;
		env->maph++;
	}
	if (env->mapw == 0 || env->maph == 0)
		return (ft_err("Map missing", FAILURE));
	if (env->mapw < 3 || env->maph < 3)
		return (ft_err("Map too small", FAILURE));
	return (SUCCESS);
}

static void	ft_print_content(char **content)
{
	int i = 0;

	printf("CONTENTTTTTTTTTTTTTTTTTTTTTTTTTT:\n");
	while (content[i] != NULL)
	{
		printf("%s\n", content[i]);
		i++;
	}
}

static void	ft_fill_map(t_env *env, char **content)
{
	char	**map;
	int		row;
	int		col;

	ft_print_content(content);
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

static int	ft_create_map(t_env *env)
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
	return (SUCCESS);
}

void ft_print_split(char **split)
{
	int i = 0;
	int j = 0;

	while (split[i] != NULL)
	{
		printf("%s  ", split[i]);
		i++;
	}
	printf("\n");
}

static void	print_data(t_env *env)
{
	printf("north texture	: [%s]\n", env->img[NORTH].path);
	printf("south texture	: [%s]\n", env->img[SOUTH].path);
	printf("west texture	: [%s]\n", env->img[WEST].path);
	printf("east texture	: [%s]\n", env->img[EAST].path);
	printf("floor color	: %d %d %d\n", env->file.colors[FLOOR][R], env->file.colors[FLOOR][G], env->file.colors[FLOOR][B]);
	printf("ceil color	: %d %d %d\n", env->file.colors[CEIL][R], env->file.colors[CEIL][G], env->file.colors[CEIL][B]);
}

// static char	**ft_jump_to_map(t_env *env)
// {
// 	char	**split;
// 	char	**content;

// 	content = env->file.content;
// 	while (*(content) != NULL)
// 	{
// 		if (ft_gettype(*content) == CEIL || ft_gettype(*content) == FLOOR)
// 			split = ft_splitmore(*content, " ,");
// 		else
// 			split = ft_splitmore(*content, " ");
// 		if (ft_get_infos(env, split) == STOP)
// 			break ;
// 		content++;
// 	}
// 	return (content);
// }

static void	ft_print_map(char **map, int mapw, int maph)
{
	int	row;
	int	col;

	row = 0;
	while (row < maph)
	{
		col = 0;
		while (col < mapw)
		{
			printf("[%c]", map[col][row]);
			col++;
		}
		printf("\n");
		row++;
	}
}

static char	*ft_skip_empty_lines(t_env *env, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_err("Missing map", FAILURE), NULL);
	while (line != NULL)
	{
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		if (line[0] != '\0')
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

static int	ft_set_map_size(t_env *env, int fd)
{
	char	*line;
	int		empty;

	line = ft_skip_empty_lines(env, fd);
	if (!line)
		return (FAILURE);
	empty = 0;
	while (line != NULL)
	{
		env->maph++;
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		printf("line : [%s]\n", line);
		if (line[0] == '\0')
			empty++;
		else
			empty = 0;
		if (ft_strlen(line) > env->mapw)
			env->mapw = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	env->maph = env->maph - empty;
	return (SUCCESS);
}

int	ft_analyze_file(t_env *env, char *filepath)
{
	char	**content;
	char	**split;
	int		fd;
	char	*line;
	int		row;
	char	*nl;
	int		empty;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (ft_err_title(), perror(filepath), FAILURE);
	if (ft_parse_map_infos(env, fd) == FAILURE)
		return (close(fd), FAILURE);
	if (ft_field_empty(env) == YES)
		return (ft_err("A field is missing", FAILURE));
	
	/* Tester ici a fond les data >< */
	print_data(env);
	
	if (ft_set_map_size(env, fd) == FAILURE)
		return (close(fd), FAILURE);
	close(fd);

	printf("mapw [%d]\n", env->mapw);
	printf("maph [%d]\n", env->maph);
	
	if (ft_create_map(env) == FAILURE)
		return (FAILURE);
	ft_print_map(env->map, env->mapw, env->maph);



	// printf("next line : [%s]\n", get_next_line(fd));

	// if (ft_set_sizes(env, fd) == FAILURE)
	// 	return (close(fd), FAILURE);
	// close(fd);
	// printf("mapw: %d\n", env->mapw);
	// printf("maph: %d\n", env->maph);
	// fd = open(filepath, O_RDONLY);
	// if (fd == -1)
	// 	return (ft_err_title(), perror(filepath), FAILURE);
	// while (env->file.count > 0)
	// {
	// 	line = get_next_line(fd);
	// 	if (!line)
	// 		break ;
	// 	free(line);
	// 	env->file.count--;
	// }
	// printf("next line: [%s]\n", get_next_line(fd));
	// row = 0;
	// while(1)
	// {
	// 	line = get_next_line(fd);
	// 	if (!line)
	// 		break ;
	// 	printf("line: [%s]\n", line);
	// 	nl = ft_strchr(line, '\n');
	// 	if (nl)
	// 		*nl = '\0';
	// 	env->map[row] = line;
	// 	row++;
	// }
	// close(fd);
	// printf("mapw: %d\n", env->mapw);
	// printf("maph: %d\n", env->maph);
	// ft_print_map(env->map, env->mapw, env->maph);
	// ft_fill_map(env, env->file.content + env->file.count);
	// if (ft_check_infos_error(env) == FAILURE)
	// 	return (FAILURE);
	return (SUCCESS);
}
