/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:59:43 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 14:21:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vic
{
	double	x;
	double	y;
}			t_vic;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_ray
{
	int		start;
	int		end;

	double	cameraX;
	
	double	rayDirX;
	double	rayDirY;
	t_vic	raydir;
	
	int		mapX;
	int		mapY;
	
	double	sideDistX;
	double	sideDistY;
	t_vic	sidedist;

	double	deltaDistX;
	double	deltaDistY;
	t_vic	deltadist;

	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		texCol;
	
	double	planeX;
	double	planeY;
	t_vic	plane;	// NOP

	double	dirX;
	double	dirY;
	t_vic	dir;	// NOP

	double	ms;
	double	rs;
	int		lineHeight;
	int		pitch;
	int		drawStart;
	int		drawEnd;
	double	wallx;		//where exactly the wall was hit
	double 	step;
	double texPos;
	int texY;
	int wall;
}			t_ray;

typedef struct s_img
{
	char	*path;
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	int		imgw;
	int		imgh;
}			t_img;

typedef struct s_file
{
	char	**content;
	int		width;
	int		rows;
	int		colors[2][3];
	int		count;
}			t_file;

typedef struct s_env
{
	t_file	file;
	char	**map;
	t_img	img[5];
	void	*mlx_ptr;
	void	*win_ptr;
	int		winw;
	int		winh;
	int		mapw;
	int		maph;
	double	px;
	double	py;
	char	pdir;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rotleft;
	int		rotright;
	t_ray	ray;
}			t_env;

#endif