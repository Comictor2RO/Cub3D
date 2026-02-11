/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:23 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 16:06:03 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ray_on_minimap(t_game *game, t_ray *ray)
{
	double	scale;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;

	scale = (double)MINIMAP_WIDTH / (game->cub->map.width * TILE);
	if ((game->cub->map.height * TILE * scale) > WINDOW_HEIGHT)
		scale = (double)WINDOW_HEIGHT / (game->cub->map.height * TILE);
	start_x = (int)(game->player.x * scale);
	start_y = (int)(game->player.y * scale);
	end_x = (int)((game->player.x + ray->dir_x
				* ray->perp_wall_dist * TILE) * scale);
	end_y = (int)((game->player.y + ray->dir_y
				* ray->perp_wall_dist * TILE) * scale);
	if (start_x >= 0 && start_x < MINIMAP_WIDTH
		&& start_y >= 0 && start_y < WINDOW_HEIGHT
		&& end_x >= 0 && end_x < MINIMAP_WIDTH
		&& end_y >= 0 && end_y < WINDOW_HEIGHT)
	{
		draw_line(&game->map_img, (t_line){start_x,
			start_y, end_x, end_y, 0xFFFF00});
	}
}

static t_wall_draw	init_wall_draw(t_game *game, t_ray *ray)
{
	t_wall_draw	w;
	double		wall_x;

	if (ray->side == 0)
		wall_x = game->player.y / TILE + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x / TILE + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	w.tex = select_texture(game, ray);
	w.tex_x = (int)(wall_x * (double)w.tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		w.tex_x = w.tex->width - w.tex_x - 1;
	w.line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	w.draw_start = -w.line_height / 2 + WINDOW_HEIGHT / 2;
	w.draw_end = w.line_height / 2 + WINDOW_HEIGHT / 2;
	if (w.draw_start < 0)
		w.draw_start = 0;
	if (w.draw_end >= WINDOW_HEIGHT)
		w.draw_end = WINDOW_HEIGHT - 1;
	w.step = 1.0 * w.tex->height / w.line_height;
	w.tex_pos = (w.draw_start - WINDOW_HEIGHT / 2 + w.line_height / 2) * w.step;
	return (w);
}

static void	draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
	t_wall_draw	w;
	int			y;
	int			tex_y;
	int			color;

	w = init_wall_draw(game, ray);
	y = 0;
	while (y < w.draw_start)
		my_mlx_pixel_put(&game->map_img, x, y++, game->cub->ceiling.hex);
	while (y <= w.draw_end)
	{
		tex_y = (int)w.tex_pos & (w.tex->height - 1);
		w.tex_pos += w.step;
		color = get_texture_color(w.tex, w.tex_x, tex_y);
		my_mlx_pixel_put(&game->map_img, x, y++, color);
	}
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(&game->map_img, x, y++, game->cub->floor.hex);
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
		x++;
	}
}

void	draw_rays_on_minimap(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < NUM_RAYS)
	{
		if (x % 20 == 0)
		{
			init_ray(&ray, game, x);
			calculate_step_and_side_dist(&ray, game);
			perform_dda(&ray, game);
			draw_ray_on_minimap(game, &ray);
		}
		x++;
	}
}
