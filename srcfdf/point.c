/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:17:47 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:42:01 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_move_map_points(t_env *env, int r, int c)
{
	int	x;
	int	y;

	x = env->map[r][c].x;
	y = env->map[r][c].y;
	if (c < env->c)
		x += (env->c - c) * fabs(env->zoom);
	else if (c > env->c)
		x -= (c - env->c) * fabs(env->zoom);
	if (r < env->r)
		y += (env->r - r) * fabs(env->zoom);
	else if (r > env->r)
		y -= (r - env->r) * fabs(env->zoom);
	env->map[r][c].x = x;
	env->map[r][c].y = y;
}

void	ft_convert_points(t_env *env, int r, int c)
{
	t_pt	out;
	int		x;
	int		y;
	int		z;

	x = env->map[r][c].x - env->map[env->rows / 2][env->cols / 2].x;
	y = env->map[r][c].y - env->map[env->rows / 2][env->cols / 2].y;
	z = env->map[r][c].z;
	if (c < env->c)
		x += (env->c - c) * env->zoom;
	else if (c > env->c)
		x -= (c - env->c) * env->zoom;
	if (r < env->r)
		y += (env->r - r) * env->zoom;
	else if (r > env->r)
		y -= (r - env->r) * env->zoom;
	out.x = x * cosf(env->angle) - y * sinf(env->angle);
	out.y = (x * sinf(env->angle) + y * cosf(env->angle)) / 2 - z
		* env->altitude;
	out.x += env->origin.x;
	out.y += env->origin.y;
	out.z = z * env->altitude * env->zoom;
	out.color = env->map[r][c].color * (z + 42);
	env->mat[r][c] = out;
}
