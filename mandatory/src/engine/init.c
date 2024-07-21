/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 12:16:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* CUBE */

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;
	
	if (c == NULL)
		return (cube);

	c->mlx = mlx_init();
	c->keycode = D;
	
	t_render *r = ft_malloc(sizeof(t_render));
	r->mlx = c->mlx;
	r->side = 1;
	init_render(r);

	t_textures *t = ft_malloc(sizeof(t_textures));
	init_textures(t, c->mlx);

	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}

t_render *init_render(t_render *r)
{
	static t_render	*render;

	if (r == NULL)
		return (render);

	render = r;
	return (render);
}

t_render *render(void)
{
	return (init_render(NULL));
}

t_textures *init_textures(t_textures *t, void *mlx)
{
	static t_textures	*texture;
	if (t == NULL)
		return (texture);

	t_texture *wall_north = ft_malloc(sizeof(t_texture));
	t_texture *wall_south = ft_malloc(sizeof(t_texture));
	t_texture *wall_east = ft_malloc(sizeof(t_texture));
	t_texture *wall_west = ft_malloc(sizeof(t_texture));

	wall_north->image = mlx_xpm_file_to_image(mlx, "assets/north.xpm", &wall_north->width, &wall_north->height);
	wall_north->data = mlx_get_data_addr(wall_north->image, &wall_north->bpp, &wall_north->size_line, &wall_north->endian);
	t->wall_north = wall_north;
	
	wall_south->image = mlx_xpm_file_to_image(mlx, "assets/south.xpm", &wall_south->width, &wall_south->height);
	wall_south->data = mlx_get_data_addr(wall_south->image, &wall_south->bpp, &wall_south->size_line, &wall_south->endian);
	t->wall_south = wall_south;

	wall_east->image = mlx_xpm_file_to_image(mlx, "assets/east.xpm", &wall_east->width, &wall_east->height);
	wall_east->data = mlx_get_data_addr(wall_east->image, &wall_east->bpp, &wall_east->size_line, &wall_east->endian);
	t->wall_east = wall_east;

	wall_west->image = mlx_xpm_file_to_image(mlx, "assets/west.xpm", &wall_west->width, &wall_west->height);
	wall_west->data = mlx_get_data_addr(wall_west->image, &wall_west->bpp, &wall_west->size_line, &wall_west->endian);
	t->wall_west = wall_west;
	
	texture = t;
	return (texture);
}

t_textures *textures(void)
{
	return (init_textures(NULL, NULL));
}