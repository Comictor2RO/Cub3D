/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:00:00 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/22 17:15:00 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_game(t_game *game)
{
	if (game->cub)
	{
		if (game->cub->tex_north.img)
			mlx_destroy_image(game->mlx, game->cub->tex_north.img);
		if (game->cub->tex_south.img)
			mlx_destroy_image(game->mlx, game->cub->tex_south.img);
		if (game->cub->tex_east.img)
			mlx_destroy_image(game->mlx, game->cub->tex_east.img);
		if (game->cub->tex_west.img)
			mlx_destroy_image(game->mlx, game->cub->tex_west.img);
		free_cub(game->cub);
	}
	if (game->map_img.img)
		mlx_destroy_image(game->mlx, game->map_img.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
