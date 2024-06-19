/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/19 11:47:20 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	ft_check_file(char *file)
{
	int		fd;
	char	*ext;

	ext = ft_strchr(file, '.');
	if (ext == NULL)
		return (printf("Error: Wrong file extension\n"), FAILURE);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (printf("Error: Wrong file extension\n"), FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	close(fd);
	return (SUCCESS);
}

static void	ft_fill_map(char **tab, char *file, int nb_lines)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return ;
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tab[i] = line;
		line = get_next_line(fd);
		i++;
	}
	tab[i] = NULL;
	close(fd);
	// return (tab);	
}

static int	ft_get_longest(char **file_info, int i, int nb_lines)
{
	int		j;
	int		longest_line;

	longest_line = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (file_info[i][j] != '\0')
			j++;
		if (j > longest_line)
			longest_line = j;
		i++;
	}
	return (longest_line);
}

static char	*ft_alloc_and_init(char *line, int longest)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (longest + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < longest)
	{
		new_line[i] = '_';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

static	void	ft_create_map(int i, int nb_lines, t_data *data, t_cub3d *c)
{
	char	**map;
	int		longest_line;
	int		j;
	int		k;
	
	printf("COUCOU\n");
	map = malloc(sizeof(char *) * (nb_lines - i + 1));
	if (!map)
		return ;
	longest_line = ft_get_longest(data->file_info, i, nb_lines);
	j = 0;
	while (j < nb_lines - i)
	{
		map[j] = ft_alloc_and_init(data->file_info[i], longest_line);
		if (!map[j])
			return ;
		j++;
	}
	map[j] = NULL;
	k = 0;
	while (k < nb_lines - i)
	{
		j = 0;
		while (data->file_info[k][j] != '\0' && j < longest_line && k < nb_lines)
		{
			if (data->file_info[k][j] != ' ')
				map[k][j] = data->file_info[i + k][j];
			j++;
		}
		printf("map[%d] = %s\n", k, map[k]);
		k++;
	}
}

static int	ft_parse_map(char **file_info, int nb_lines, t_data *data, t_cub3d *c)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		if (file_info[i][j] == '\n')
			i++;
		if (file_info[i][j] == 'N' && file_info[i][j + 1] == 'O')
			data->no = ft_get_texture(file_info[i]);
		else if (file_info[i][j] == 'S' && file_info[i][j + 1] == 'O')
			data->so = ft_get_texture(file_info[i]);
		else if (file_info[i][j] == 'W' && file_info[i][j + 1] == 'E')
			data->we = ft_get_texture(file_info[i]);
		else if (file_info[i][j] == 'E' && file_info[i][j + 1] == 'A')
			data->ea = ft_get_texture(file_info[i]);
		else if (file_info[i][j] == 'F')
			ft_set_color(file_info[i], data->f);
		else if (file_info[i][j] == 'C')
			ft_set_color(file_info[i], data->c);
		else
			return (ft_create_map(i, nb_lines, data, c), SUCCESS);
		i++;
		// else
		// 	return (printf("Error: Invalid description file\n"), FAILURE);
	}
	return (SUCCESS);
}

void	print_file_info(char **file_info)
{
	int i = 0;
	while (file_info[i])
	{
		printf("%s\n", file_info[i]);
		i++;
	}
}

int	ft_parsing(int ac, char **av, t_cub3d *c)
{
	int		nb_lines;
	t_data	data;
	char	*test;

	if (ac != 2)
		return (printf("Error: Wrong number of arguments\n"), FAILURE);
	if (ft_check_file(av[1]) == FAILURE)
		return (FAILURE);
	nb_lines = ft_count_lines(av[1]);
	data.file_info = malloc(sizeof(char *) * (nb_lines + 1));
	if (!data.file_info)
		return (FAILURE);
	ft_fill_map(data.file_info, av[1], nb_lines);
	// print_file_info(data.file_info);
	if (ft_parse_map(data.file_info, nb_lines, &data, c) == FAILURE)
		return (FAILURE);
	free_data(&data);
	return (SUCCESS);
}
