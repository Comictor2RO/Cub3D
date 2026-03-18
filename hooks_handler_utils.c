/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:25:05 by vturlas           #+#    #+#             */
/*   Updated: 2026/03/18 15:31:35 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player_vectors(t_game *game)
{
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	game->player.plane_x = -sin(game->player.angle) * 0.66;
	game->player.plane_y = cos(game->player.angle) * 0.66;
}

void	rotate_player(t_game *game, double rot_amount)
{
	game->player.angle += rot_amount;
	update_player_vectors(game);
}

void	rotate_with_arrows(t_game *game)
{
	if (game->keys[4])
		rotate_player(game, -ROT_SPEED);
	if (game->keys[5])
		rotate_player(game, ROT_SPEED);
}
