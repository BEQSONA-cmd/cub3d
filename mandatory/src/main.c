/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 20:25:50 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// format must end .cub

static void	check_format(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len <= 4 || map[len - 1] != 'b' || map[len - 2] != 'u'
		|| map[len - 3] != 'c' || map[len - 4] != '.')
		ft_error("Invalid map format");
}

static void	init_game(char *map)
{
	t_textures	*t;

	check_format(map);
	init_cube(ft_malloc(sizeof(t_cube)));
	init_map(map);
	t = ft_malloc(sizeof(t_textures));
	init_textures(t, cube()->mlx);
	init_player(ft_malloc(sizeof(t_player)));
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_error("Invalid number of arguments");
	check_params(argv);
	ft_alloc_init();
	init_game(argv[1]);
	start_game();
	ft_destructor();
	return (0);
}
