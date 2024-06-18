/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:37:40 by momrane           #+#    #+#             */
/*   Updated: 2024/06/18 15:39:01 by vvaudain         ###   ########.fr       */
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

	printf("nb_lines = %d\n", nb_lines);
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

static int	ft_parse_map(char **file_info, int nb_lines, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (ft_isspace(file_info[i][j]) == 1)
			j++;
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
		// else if (file_info[i][0] == '1')
		// 	printf("Map\n");
		// else
		// 	return (printf("Error\nInvalid map\n"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_parsing(int ac, char **av)
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
	if (ft_parse_map(data.file_info, nb_lines, &data) == FAILURE)
		return (FAILURE);
	free_data(&data);
	return (SUCCESS);
}
