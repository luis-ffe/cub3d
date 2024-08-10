/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/09 23:49:36 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_detect(int key, t_data *cub)
{
	printf("key %x \n", key);
	if (key == XK_Escape)
		close_win_free(cub);
	else if (key == XK_Up)
		control_trans(cub, 1);
	else if (key == XK_Down)
		control_trans(cub, -1);
	else if (key == XK_Left)
		control_rot(cub,-1);
	else if (key == XK_Right)
		control_rot(cub, 1);
	render(cub);
	return (0);
}

void control_rot(t_data *cub, int dir)
{
	if (dir > 0)
		cub->player->p_ang += DG_RAD*5;
	else
		(cub->player->p_ang) -= DG_RAD*5;
}

void control_trans(t_data *cub, int dir)
{
	int finalX;
	int finalY;

	if (dir > 0 )
	{
		finalX = (int)(cub->player->posX + cos(cub->player->p_ang)/10);
		finalY = (int)(cub->player->posY + sin(cub->player->p_ang)/10);
		if (cub->map[finalX][finalY] == 0)
		{
			cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/10;	
			cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/10;
		}
	}	
	else
	{
		finalX = (int)(cub->player->posX - cos(cub->player->p_ang)/10);
		finalY = (int)(cub->player->posY - sin(cub->player->p_ang)/10);
		if (cub->map[finalX][finalY] == 0)
		{
			cub->player->posX -= (cos(cub->player->p_ang)/10);
			cub->player->posY -= (sin(cub->player->p_ang)/10);
		}
	}
}