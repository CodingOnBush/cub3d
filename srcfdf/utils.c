/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:23:27 by momrane           #+#    #+#             */
/*   Updated: 2024/02/29 17:10:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	ft_count_cols(char *line)
{
	int	col;

	col = 0;
	while (*line)
	{
		if (ft_isdigit(*line) || ft_strchr("+-", *line))
		{
			col++;
			if (ft_strchr("+-", *line))
				line++;
			while (ft_isdigit(*line) || ft_strchr(",xabcdefABCDEF", *line))
				line++;
		}
		else
			line++;
	}
	return (col);
}

int	ft_get_color(char *str)
{
	char	*substr;
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	substr = ft_strchr(str, ',');
	if (substr == NULL)
		return (0);
	substr++;
	while (substr[i])
	{
		if (substr[i] >= 'A' && substr[i] <= 'F')
			nb = nb * 16 + (substr[i] - 'A' + 10);
		else if (substr[i] >= 'a' && substr[i] <= 'f')
			nb = nb * 16 + (substr[i] - 'a' + 10);
		else
			nb = nb * 16 + (substr[i] - '0');
		i++;
	}
	return (nb);
}

void	ft_set_zoom(t_env *env)
{
	if (env->rows > 499 || env->cols > 499)
		env->zoom = 3;
	else if (env->rows > 199 || env->cols > 199)
		env->zoom = 10;
	else if (env->rows > 99 || env->cols > 99)
		env->zoom = 12;
	else
		env->zoom = 30;
}
