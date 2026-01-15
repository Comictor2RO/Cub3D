/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:23 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/15 15:47:24 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)NUM_RAYS - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)(game->player.x / TILE);
	ray->map_y = (int)(game->player.y / TILE);
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

static void	calculate_step_and_side_dist(t_ray *ray, t_game *game)
{
	double	player_pos_x;
	double	player_pos_y;

	player_pos_x = game->player.x / TILE;
	player_pos_y = game->player.y / TILE;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player_pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player_pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player_pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player_pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_game *game)
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
		if (ray->map_x < 0 || ray->map_x >= MAP_WIDTH
			|| ray->map_y < 0 || ray->map_y >= MAP_HEIGHT
			|| map[ray->map_y][ray->map_x] == 1)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x / TILE
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y / TILE
				+ (1 - ray->step_y) / 2) / ray->dir_y;
}

static void	draw_ray_on_minimap(t_game *game, t_ray *ray)
{
	double	ray_end_x;
	double	ray_end_y;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;

	ray_end_x = game->player.x + ray->dir_x * ray->perp_wall_dist * TILE;
	ray_end_y = game->player.y + ray->dir_y * ray->perp_wall_dist * TILE;
	start_x = (int)(game->player.x);
	start_y = (int)(game->player.y);
	end_x = (int)(ray_end_x);
	end_y = (int)(ray_end_y);
	if (start_x >= 0 && start_x < MINIMAP_WIDTH
		&& start_y >= 0 && start_y < WINDOW_HEIGHT
		&& end_x >= 0 && end_x < MINIMAP_WIDTH
		&& end_y >= 0 && end_y < WINDOW_HEIGHT)
		draw_line(&game->map_img, start_x, start_y, end_x, end_y, 0xFFFF00);
}

static void	draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;

	line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (ray->side == 1)
		color = 0x808080;
	else
		color = 0xC0C0C0;
	y = 0;
	while (y < draw_start)
		my_mlx_pixel_put(&game->map_img, MINIMAP_WIDTH + x, y++, 0x87CEEB);
	while (y <= draw_end)
		my_mlx_pixel_put(&game->map_img, MINIMAP_WIDTH + x, y++, color);
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(&game->map_img, MINIMAP_WIDTH + x, y++, 0x404040);
}

void	draw_3d_view(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < NUM_RAYS)
	{
		init_ray(&ray, game, x);
		calculate_step_and_side_dist(&ray, game);
		perform_dda(&ray, game);
		draw_wall_stripe(game, &ray, x);
		if (x % 20 == 0)
			draw_ray_on_minimap(game, &ray);
		x++;
	}
}
