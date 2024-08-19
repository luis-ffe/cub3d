/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 11:42:48 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	init_fields_bonus(t_data *cub)
{
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		ft_error(MLX, cub);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_W, WIN_H, "CUB3D");
	if (cub->win_ptr == NULL)
		ft_error(WINDOW, cub);
	cub->img_w = WIN_W;
	cub->img_h = WIN_H;
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	if (!cub->img)
		ft_error(CUBIMG, cub);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
	cub->player = init_player(cub);
	init_position_bonus(cub);
	init_keys(cub);
	textures_definer_bonus(cub);
	return (0);
}

t_player *init_player(t_data *cub)
{
	t_player *player;
	
	player = (t_player *) malloc(sizeof(t_player) * 1);
	if (player == NULL)
		ft_error(PLAYER, cub);
	player->pov = (t_pov *) malloc(sizeof(t_pov) * 1);
	init_orientation(player, cub->player_init_ori);
	init_camera(player, cub);
	return (player);
}

void init_orientation(t_player *player, char player_init_ori)
{
	player->fov = FOV;
	if (player_init_ori == 'N')
		player->p_ang = -90 * DG_RAD;
	else if (player_init_ori == 'W')
		player->p_ang = 0 * DG_RAD;
	else if (player_init_ori == 'E')
		player->p_ang = 180 * DG_RAD;
	else
		player->p_ang = 90 * DG_RAD;
	player->pov->dirX = cos(player->p_ang);
	player->pov->dirY = sin(player->p_ang);
}

void init_position_bonus(t_data *cub)
{
	int i;
	int j;
	int count;

	count = 0;
	cub->player->posX = (double) cub->init_x + 0.5;
	cub->player->posY = (double) cub->init_y + 0.5;
    i = -1;
	while (++i < cub->map_h)
	{
		j = -1;
		while (++j < cub->map_w)
		{
			if (cub->map[i][j] == 'D'
				&& ((cub->map[i + 1][j] == '1' && cub->map[i - 1][j] == '1') 
				||(cub->map[i][j + 1] == '1' && cub->map[i][j - 1] == '1')))
				count++;
			else if (cub->map[i][j] == 'D')
				cub->map[i][j] = '0';
		}
	}
	if (count > 0)
		init_doors_bonus(cub, count);
	return ;
}

void	init_doors_bonus(t_data *cub, int count)
{
	int i;
	int j;
	int door_num;

	door_num = 0;
	cub->doors = (t_door *)malloc((count + 1) * sizeof(t_door));
	if (cub->doors == NULL)
		ft_error(125, cub);
	i = -1;
	while (++i < cub->map_h)
	{
		j = -1;
		while (++j < cub->map_w)
		{
			if (cub->map[i][j] == 'D')
			{
				fill_door_info_bonus(cub, door_num, i, j);
				door_num++;
			}
		}
	}
	cub->doors[count].orientation = -1;
}

void	fill_door_info_bonus(t_data *cub, int door_num, int i, int j)
{
	cub->doors[door_num].pos_x = (double) j + 0.5;
	cub->doors[door_num].pos_y = (double) i + 0.5;
	if(cub->map[i + 1][j] == '1' && cub->map[i - 1][j] == '1')
		cub->doors[door_num].orientation = 1;
	else if (cub->map[i][j - 1] == '1' && cub->map[i][j + 1] == '1')
		cub->doors[door_num].orientation = 0;
	cub->doors[door_num].open = false;
	cub->doors[door_num].status = 0;
	cub->doors[door_num].speed = 0.002;
	cub->doors[door_num].last_time = get_time();
	cub->doors[door_num].position = 0.0;

}

void init_camera(t_player *player, t_data *cub)
{
	player->cam = (t_camera *) malloc(sizeof(t_camera) * 1);
	if (player->cam == NULL)
		ft_error(CAMERA, cub);
	player->cam->planeX = -player->pov->dirY * tan(player->fov / 2);
	player->cam->planeY = player->pov->dirX * tan(player->fov / 2);
}

void textures_definer_bonus(t_data *cub)
{
	cub->texnorth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->north, &cub->texnorth.width,
			&cub->texnorth.height);
	cub->texnorth.data = mlx_get_data_addr(cub->texnorth.img,
			&cub->texnorth.bits_per_pixel, &cub->texnorth.line_length, 
			&cub->texnorth.endian);
	cub->texsouth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->south, &cub->texsouth.width,
			&cub->texsouth.height);
	cub->texsouth.data = mlx_get_data_addr(cub->texsouth.img, 
			&cub->texsouth.bits_per_pixel, &cub->texsouth.line_length, 
			&cub->texsouth.endian);
	cub->texeast.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->east, &cub->texeast.width,
			&cub->texeast.height);
	cub->texeast.data = mlx_get_data_addr(cub->texeast.img, 
			&cub->texeast.bits_per_pixel, &cub->texeast.line_length, 
			&cub->texeast.endian);
	cub->texwest.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->west, &cub->texwest.width,
			&cub->texwest.height);
	cub->texwest.data = mlx_get_data_addr(cub->texwest.img, 
			&cub->texwest.bits_per_pixel, &cub->texwest.line_length, 
			&cub->texwest.endian);
	texture_door_bonus(cub);
	texture_fire_bonus(cub);
}

void texture_door_bonus(t_data *cub)
{
	int fd;

	fd = open("./textures/Door.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	cub->door.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/Door.xpm", &cub->door.width,
			&cub->door.height);
	if (cub->door.img == NULL)
		ft_error(1000, cub);
	cub->door.data = mlx_get_data_addr(cub->door.img, 
			&cub->door.bits_per_pixel, &cub->door.line_length, 
			&cub->door.endian);
}

void texture_fire_bonus(t_data *cub)
{
	int fd;

	fd = open("./textures/fire1.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	fd = open("./textures/fire2.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	fd = open("./textures/fire3.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	cub->fire1.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/fire1.xpm", &cub->door.width,
			&cub->door.height);
	if (cub->door.img == NULL)
			ft_error(1000, cub);
	cub->fire1.data = mlx_get_data_addr(cub->door.img, 
			&cub->door.bits_per_pixel, &cub->door.line_length, 
			&cub->door.endian);
	cub->fire2.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/fire2.xpm", &cub->door.width,
			&cub->door.height);
	if (cub->fire2.img == NULL)
		ft_error(1000, cub);
	cub->fire2.data = mlx_get_data_addr(cub->door.img, 
			&cub->door.bits_per_pixel, &cub->door.line_length, 
			&cub->door.endian);
	cub->fire3.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/fire3.xpm", &cub->door.width,
			&cub->door.height);
	if (cub->fire3.img == NULL)
		ft_error(1000, cub);
	cub->fire3.data = mlx_get_data_addr(cub->door.img, 
			&cub->door.bits_per_pixel, &cub->door.line_length, 
			&cub->door.endian);
	cub->fire_num = 0;
}

void	init_keys(t_data *cub)
{
	cub->keys.back_front = 0;
	cub->keys.left_right = 0;
	cub->keys.rotate = 0;
}