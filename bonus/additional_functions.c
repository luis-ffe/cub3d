/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:01:15 by masoares          #+#    #+#             */
/*   Updated: 2024/08/20 01:06:52 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

//minimap fire color renderer

void	render_rect_fire(t_data *img, double pos_x, double pos_y, int scale)
{
	int		i;
	int		j;
	int     color;

	i = pos_x * scale;
	j = pos_y * scale;
	while (i < pos_x * scale + scale)
	{
		j = pos_y * scale;
		while (j < pos_y * scale + scale)
		{
			color = 0xFFAA00;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
int		draw_fire(t_data *cub, double wallDist, int num, int x)
{
	(void) wallDist;
	(void) x;
    double fire_pos;
    double spriteX, spriteY;
	t_castInfo line_prop;

    spriteX = cub->fires[num].pos_x - cub->player->posx;
    spriteY = cub->fires[num].pos_y - cub->player->posy;

    double invDet = 1.0 / (cub->player->cam->planex * cub->player->pov->diry - cub->player->pov->dirx * cub->player->cam->planey);
    double transformX = invDet * (cub->player->pov->diry * spriteX - cub->player->pov->dirx * spriteY);
    double transformY = invDet * (-cub->player->cam->planey * spriteX + cub->player->cam->planex * spriteY); // always > 0

    fire_pos = (int)((cub->img_w / 2) * (1 + transformX / transformY));

    line_prop.line_height = abs((int) (WIN_H / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
    line_prop.ystart  = -line_prop.line_height / 2 + WIN_H / 2;
    if(line_prop.ystart < 0) 
		line_prop.ystart  = 0;
    line_prop.yend  = line_prop.line_height / 2 + WIN_H / 2;
    if(line_prop.yend >= WIN_H) 
		line_prop.yend= WIN_H - 1;
		
	int spriteWidth = abs((int) (WIN_H / (transformY)));
    int drawStartX = -spriteWidth / 2 + fire_pos;
    if(drawStartX < 0)
		drawStartX = 0;
    int drawEndX = spriteWidth / 2 + fire_pos;
    if(drawEndX >= WIN_W) 
	  	drawEndX = WIN_W - 1;
	line_prop.x = x;

	for(int y = line_prop.ystart; y < line_prop.yend ; y++)
    {
			line_prop.wallx = (x - (-spriteWidth / 2 + fire_pos)) * cub->fire1.width / spriteWidth;
			if (line_prop.wallx < 0)
				line_prop.wallx = 0;
			if (line_prop.wallx > cub->fire1.width)
				line_prop.wallx = cub->fire1.width;
			line_maker(cub, line_prop, 20);
	}
	return(1);
}
