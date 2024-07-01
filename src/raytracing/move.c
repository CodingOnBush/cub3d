/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:33:00 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 15:25:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_move_horizontal(t_env *env)
{
	t_vic	step;

	step.x = env->ray.planex * env->ray.ms;
	step.y = env->ray.planey * env->ray.ms;
	if (env->left)
	{
		if (env->map[(int)(env->px - step.x)][(int)(env->py)] == '0')
			env->px -= step.x;
		if (env->map[(int)(env->px)][(int)(env->py - step.y)] == '0')
			env->py -= step.y;
	}
	if (env->right)
	{
		if (env->map[(int)(env->px + step.x)][(int)(env->py)] == '0')
			env->px += step.x;
		if (env->map[(int)(env->px)][(int)(env->py + step.y)] == '0')
			env->py += step.y;
	}
}

static void	ft_move_vertical(t_env *env)
{
	t_vic	step;

	step.x = env->ray.dirx * env->ray.ms;
	step.y = env->ray.diry * env->ray.ms;
	if (env->down)
	{
		if (env->map[(int)(env->px - step.x)][(int)(env->py)] == '0')
			env->px -= step.x;
		if (env->map[(int)(env->px)][(int)(env->py - step.y)] == '0')
			env->py -= step.y;
	}
	if (env->up)
	{
		if (env->map[(int)(env->px + step.x)][(int)(env->py)] == '0')
			env->px += step.x;
		if (env->map[(int)(env->px)][(int)(env->py + step.y)] == '0')
			env->py += step.y;
	}
}

static void	ft_rotate(t_env *env)
{
	double const	rs = env->ray.rs;
	double			olddirx;
	double			oldplanex;

	if (env->rotleft)
	{
		olddirx = env->ray.dirx;
		env->ray.dirx = env->ray.dirx * cos(rs) - env->ray.diry * sin(rs);
		env->ray.diry = olddirx * sin(rs) + env->ray.diry * cos(rs);
		oldplanex = env->ray.planex;
		env->ray.planex = env->ray.planex * cos(rs) - env->ray.planey * sin(rs);
		env->ray.planey = oldplanex * sin(rs) + env->ray.planey * cos(rs);
	}
	if (env->rotright)
	{
		olddirx = env->ray.dirx;
		env->ray.dirx = env->ray.dirx * cos(-rs) - env->ray.diry * sin(-rs);
		env->ray.diry = olddirx * sin(-rs) + env->ray.diry * cos(-rs);
		oldplanex = env->ray.planex;
		env->ray.planex = env->ray.planex * cos(-rs) - env->ray.planey
			* sin(-rs);
		env->ray.planey = oldplanex * sin(-rs) + env->ray.planey * cos(-rs);
	}
}

void	ft_move(t_env *env)
{
	if (env->down || env->up)
		ft_move_vertical(env);
	if (env->left || env->right)
		ft_move_horizontal(env);
	if (env->rotleft || env->rotright)
		ft_rotate(env);
}
