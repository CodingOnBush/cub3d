/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:49:37 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:41:39 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_exit_error(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(0);
}

void	*ft_free_matrix(t_pt **matrix, int rows)
{
	int	i;

	i = 0;
	if (!matrix)
		return (NULL);
	while (i < rows)
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

void	ft_free_env(t_env *env)
{
	if (env->map != NULL)
		ft_free_matrix(env->map, env->rows);
	if (env->mat != NULL)
		ft_free_matrix(env->mat, env->rows);
	if (env->mlx_ptr)
	{
		if (env->win_ptr)
		{
			if (env->img.img_ptr != NULL)
				mlx_destroy_image(env->mlx_ptr, env->img.img_ptr);
			mlx_clear_window(env->mlx_ptr, env->win_ptr);
			mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		}
		mlx_destroy_display(env->mlx_ptr);
		free(env->mlx_ptr);
	}
	ft_init_env_values(env, NULL);
}

int	ft_free_env_err(t_env *env, char *msg)
{
	ft_free_env(env);
	ft_printf("%s\n", msg);
	return (-1);
}
