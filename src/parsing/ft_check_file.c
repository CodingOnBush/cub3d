/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:02:37 by momrane           #+#    #+#             */
/*   Updated: 2024/07/06 12:47:18 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_file_extension(char *path, char *ext)
{
	char	*point;

	point = ft_strrchr(path, '.');
	if (!point)
		return (ft_err("No file extension", FAILURE));
	if (ft_strcmp(point, ext) != 0)
		return (ft_err("Invalid file extension", FAILURE));
	return (SUCCESS);
}

int	ft_check_file(char *cubfile_path)
{
	int	fd;

	if (ft_check_file_extension(cubfile_path, ".cub") == FAILURE)
		return (FAILURE);
	fd = open(cubfile_path, O_RDONLY);
	if (fd == -1)
	{
		ft_err_title();
		perror(cubfile_path);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
