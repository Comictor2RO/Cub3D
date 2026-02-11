/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:33 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 16:10:00 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)NUM_RAYS - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)(game->player.x / TILE);
	ray->map_y = (int)(game->player.y / TILE);
	if (fabs(ray->dir_x) < 1e-10)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (fabs(ray->dir_y) < 1e-10)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_ray *ray, t_game *game)
{
	double	pos_p_x;
	double	pos_p_y;

	pos_p_x = game->player.x / TILE;
	pos_p_y = game->player.y / TILE;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pos_p_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pos_p_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->cub->map.width
			|| ray->map_y < 0 || ray->map_y >= game->cub->map.height
			|| game->cub->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x / TILE
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y / TILE
				+ (1 - ray->step_y) / 2) / ray->dir_y;
}

t_texture	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&game->cub->tex_east);
		else
			return (&game->cub->tex_west);
	}
	else
	{
		if (ray->step_y > 0)
			return (&game->cub->tex_south);
		else
			return (&game->cub->tex_north);
	}
}

int	get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*dst;
	int		color;

	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height)
		return (0xFF00FF);
	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
