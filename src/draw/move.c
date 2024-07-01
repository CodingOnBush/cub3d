/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:10:08 by allblue           #+#    #+#             */
/*   Updated: 2024/07/01 11:52:41 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_rotright(t_env *e)
{
	double	olddirx;
	double	oldplanex;

	olddirx = e->ray.dirX;
	e->ray.dirX = e->ray.dirX * cos(-e->ray.rs) - e->ray.dirY
		* sin(-e->ray.rs);
	e->ray.dirY = olddirx * sin(-e->ray.rs) + e->ray.dirY * cos(-e->ray.rs);
	oldplanex = e->ray.planeX;
	e->ray.planeX = e->ray.planeX * cos(-e->ray.rs) - e->ray.planeY
		* sin(-e->ray.rs);
	e->ray.planeY = oldplanex * sin(-e->ray.rs) + e->ray.planeY
		* cos(-e->ray.rs);
}

static void	ft_rotate(t_env *e)
{
	double	olddirx;
	double	oldplanex;

	if (e->rotleft)
	{
		olddirx = e->ray.dirX;
		e->ray.dirX = e->ray.dirX * cos(e->ray.rs) - e->ray.dirY
			* sin(e->ray.rs);
		e->ray.dirY = olddirx * sin(e->ray.rs) + e->ray.dirY * cos(e->ray.rs);
		oldplanex = e->ray.planeX;
		e->ray.planeX = e->ray.planeX * cos(e->ray.rs) - e->ray.planeY
			* sin(e->ray.rs);
		e->ray.planeY = oldplanex * sin(e->ray.rs) + e->ray.planeY
			* cos(e->ray.rs);
	}
	else if (e->rotright)
		ft_rotright(e);
}

static void	ft_move_horizontal(t_env *env)
{
	double	stephorizontalx;
	double	stephorizontaly;

	stephorizontalx = env->ray.planeX * env->ray.ms;
	stephorizontaly = env->ray.planeY * env->ray.ms;
	if (env->left)
	{
		if (env->map[(int)(env->px - stephorizontalx)][(int)(env->py)] == '0')
			env->px -= stephorizontalx;
		if (env->map[(int)(env->px)][(int)(env->py - stephorizontaly)] == '0')
			env->py -= stephorizontaly;
	}
	else if (env->right)
	{
		if (env->map[(int)(env->px + stephorizontalx)][(int)(env->py)] == '0')
			env->px += stephorizontalx;
		if (env->map[(int)(env->px)][(int)(env->py + stephorizontaly)] == '0')
			env->py += stephorizontaly;
	}
}

static void	ft_move_vertical(t_env *env)
{
	double	stepverticalx;
	double	stepverticaly;

	stepverticalx = env->ray.dirX * env->ray.ms;
	stepverticaly = env->ray.dirY * env->ray.ms;
	if (env->down)
	{
		if (env->map[(int)(env->px - stepverticalx)][(int)(env->py)] == '0')
			env->px -= stepverticalx;
		if (env->map[(int)(env->px)][(int)(env->py - stepverticaly)] == '0')
			env->py -= stepverticaly;
	}
	else if (env->up)
	{
		if (env->map[(int)(env->px + stepverticalx)][(int)(env->py)] == '0')
			env->px += stepverticalx;
		if (env->map[(int)(env->px)][(int)(env->py + stepverticaly)] == '0')
			env->py += stepverticaly;
	}
}

void	ft_move(t_env *env)
{
	if (env->up || env->down)
		ft_move_vertical(env);
	if (env->left || env->right)
		ft_move_horizontal(env);
	if (env->rotleft || env->rotright)
		ft_rotate(env);
}
