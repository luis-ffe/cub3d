/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:23:36 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 09:59:44 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_mouse_move(int x, int y, t_data *cub);

int	handle_mouse_move(int x, int y, t_data *cub)
{
	(void) y;
	if (x < 5)
	{
		x = WIN_W - 5;
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, y);
	}
	else if (x > WIN_W - 5)
	{
		x = 5;
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, y);
	}
	if (x == cub->player->prev_x)
		return (0);
	else if (x > cub->player->prev_x)
		control_rot(cub, 1);
	else if (x < cub->player->prev_x)
		control_rot(cub, -1);
	cub->player->prev_x = x;
	return (0);
}
