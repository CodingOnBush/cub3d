/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallheight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:45:04 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 15:28:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_set_step(t_env *env, t_point *step)
{
	step->x = 1;
	if (env->ray.raydir.x < 0)
		step->x = -1;
	step->y = 1;
	if (env->ray.raydir.y < 0)
		step->y = -1;
}

static void	ft_set_sidedist(t_env *env, t_vic *sidedist, t_vic deltadist)
{
	if (env->ray.raydir.x < 0)
		sidedist->x = (env->px - env->ray.mapx) * deltadist.x;
	else
		sidedist->x = (env->ray.mapx + 1.0 - env->px) * deltadist.x;
	if (env->ray.raydir.y < 0)
		sidedist->y = (env->py - env->ray.mapy) * deltadist.y;
	else
		sidedist->y = (env->ray.mapy + 1.0 - env->py) * deltadist.y;
	if (sidedist->x == 0)
		sidedist->x = 0.1;
	if (sidedist->y == 0)
		sidedist->y = 0.1;
}

static void	ft_hit_wall(t_env *env, t_vic *side, t_vic *delta, t_point step)
{
	while (1)
	{
		if (side->x < side->y)
		{
			side->x += delta->x;
			env->ray.mapx += step.x;
			env->ray.side = 0;
		}
		else
		{
			side->y += delta->y;
			env->ray.mapy += step.y;
			env->ray.side = 1;
		}
		if (env->ray.mapx < 0 || env->ray.mapy < 0 || env->ray.mapx >= env->mapw
			|| env->ray.mapy >= env->maph)
			break ;
		if (env->map[env->ray.mapx][env->ray.mapy] > '0')
			break ;
	}
}

int	ft_get_line_height(t_env *env, int col)
{
	double const	camerax = 2 * (col) / (double)env->winw - 1;
	t_vic			sidedist;
	t_vic			deltadist;
	t_point			step;

	env->ray.mapx = (int)env->px;
	env->ray.mapy = (int)env->py;
	env->ray.raydir.x = env->ray.dirx + (env->ray.planex) * (camerax);
	env->ray.raydir.y = env->ray.diry + (env->ray.planey) * (camerax);
	deltadist.x = 1e30;
	if (env->ray.raydir.x != 0)
		deltadist.x = fabs(1 / env->ray.raydir.x);
	deltadist.y = 1e30;
	if (env->ray.raydir.y != 0)
		deltadist.y = fabs(1 / env->ray.raydir.y);
	ft_set_step(env, &step);
	ft_set_sidedist(env, &sidedist, deltadist);
	ft_hit_wall(env, &sidedist, &deltadist, step);
	env->ray.adjacent = (sidedist.y - deltadist.y);
	if (env->ray.side == 0)
		env->ray.adjacent = (sidedist.x - deltadist.x);
	return ((int)(env->winh / env->ray.adjacent));
}
