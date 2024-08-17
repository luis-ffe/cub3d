/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/16 14:24:55 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	cub;

	field_filler(&cub);
	check_user_input(argc, argv[1], &cub);
	read_mapfile(&cub, argv[1]);
	read_lines(&cub);
	parser_first(&cub);
	init_fields(&cub);
	run_window(&cub);
	general_free(&cub);
	return (0);
}
