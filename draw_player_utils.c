/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:33:21 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:30 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle_line(t_img *img, t_circle p, int y)
{
	int	x;
	int	dx;
	int	dy;

	x = p.cx - p.r;
	while (x <= p.cx + p.r)
	{
		dx = x - p.cx;
		dy = y - p.cy;
		if (dx * dx + dy * dy <= p.r * p.r)
			my_mlx_pixel_put(img, x, y, p.color);
		x++;
	}
}

void	update_line_pos(t_line *p, t_bresenham *b)
{
	int	e2;

	e2 = 2 * b->err;
	if (e2 > -b->dy)
	{
		b->err -= b->dy;
		p->x1 += b->sx;
	}
	if (e2 < b->dx)
	{
		b->err += b->dx;
		p->y1 += b->sy;
	}
}

void	init_bresenham(t_bresenham *b, t_line p)
{
	b->dx = abs(p.x2 - p.x1);
	b->dy = abs(p.y2 - p.y1);
	b->sx = -1;
	if (p.x1 < p.x2)
		b->sx = 1;
	b->sy = -1;
	if (p.y1 < p.y2)
		b->sy = 1;
	b->err = b->dx - b->dy;
}
