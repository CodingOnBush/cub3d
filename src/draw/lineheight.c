/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineheight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:18:33 by allblue           #+#    #+#             */
/*   Updated: 2024/06/30 19:19:13 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_set_steps(t_env *env)
{
	env->ray.stepX = 1;
	env->ray.stepY = 1;
	if(env->ray.raydir.x < 0)
		env->ray.stepX = -1;
	if(env->ray.raydir.y < 0)
		env->ray.stepY = -1;
}

static int	ft_wall_is_hit(t_env *env)
{
	if (env->ray.mapX < 0 || env->ray.mapY < 0)
		return (YES);
	if (env->ray.mapX >= env->mapw || env->ray.mapY >= env->maph)
		return (YES);
	if(env->map[env->ray.mapX][env->ray.mapY] > '0')
		return (YES);
	return (NO);
}

static double	ft_get_oppside(t_env *env, t_vic sidedist)
{
	ft_set_steps(env);
	while (ft_wall_is_hit(env) == NO)
	{
		if(sidedist.x < sidedist.y)
		{
			sidedist.x += env->ray.deltadist.x;
			env->ray.mapX += env->ray.stepX;
			env->ray.side = 0;
		}
		else
		{
			sidedist.y += env->ray.deltadist.y;
			env->ray.mapY += env->ray.stepY;
			env->ray.side = 1;
		}
	}
	if(env->ray.side == 0)
		return (sidedist.x - env->ray.deltadist.x);
	return (sidedist.y - env->ray.deltadist.y);
}

static void	ft_set_sidedist(t_env *env, t_vic raydir)
{
	t_vic	*sidedist;

	sidedist = &env->ray.sidedist;
	sidedist->x = (env->ray.mapX + 1.0 - env->px) * env->ray.deltadist.x;
	sidedist->y = (env->ray.mapY + 1.0 - env->py) * env->ray.deltadist.y;
	if (raydir.x < 0)
	{
		sidedist->x = (env->px - env->ray.mapX) * env->ray.deltadist.x;
		if (sidedist->x == 0)
			sidedist->x = 0.1;
	}
	if (raydir.y < 0)
	{
		sidedist->y = (env->py - env->ray.mapY) * env->ray.deltadist.y;
		if (sidedist->y == 0)
			sidedist->y = 0.1;
	}
}

void	ft_set_line_height(t_env *env)
{
	env->ray.deltadist.x = 1e30;
	env->ray.deltadist.y = 1e30;
	if (env->ray.raydir.x != 0)
		env->ray.deltadist.x = fabs(1 / env->ray.raydir.x);
	if (env->ray.raydir.y != 0)
		env->ray.deltadist.y = fabs(1 / env->ray.raydir.y);
	// ft_set_sidedist(env, env->ray.raydir);
	env->ray.sidedist.x = (env->ray.mapX + 1.0 - env->px) * env->ray.deltadist.x;
	env->ray.sidedist.y = (env->ray.mapY + 1.0 - env->py) * env->ray.deltadist.y;
	if (env->ray.raydir.x < 0)
	{
		env->ray.sidedist.x = (env->px - env->ray.mapX) * env->ray.deltadist.x;
		if (env->ray.sidedist.x == 0)
			env->ray.sidedist.x = 0.1;
	}
	if (env->ray.raydir.y < 0)
	{
		env->ray.sidedist.y = (env->py - env->ray.mapY) * env->ray.deltadist.y;
		if (env->ray.sidedist.y == 0)
			env->ray.sidedist.y = 0.1;
	}
	env->ray.oppside = ft_get_oppside(env, env->ray.sidedist);
	env->ray.line_height = env->winh / env->ray.oppside;
}
