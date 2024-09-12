/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:02:34 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 18:51:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_items_textures(t_textures *t){
    int i = 1; 
    while(i <= 255){
        char *name = "assets/items/item";
        char *num = ft_itoa(i);
        char *ext = ".xpm";
        char *path = ft_strjoin(name, num);
        char *path2 = ft_strjoin(path, ext);

        t_texture *item = ft_malloc(sizeof(t_texture));
        item->image = get_texture_file(path2, &item->width, &item->height);
        item->data = mlx_get_data_addr(item->image, &item->bpp, &item->size_line, &item->endian);
        t->items[i] = item;

        ft_free(num);
        ft_free(path);
        ft_free(path2);
        i++;
    }

    // t_texture *netherite_sword = ft_malloc(sizeof(t_texture));
    // netherite_sword->image = get_texture_file("assets/netherite_sword.xpm", &netherite_sword->width, &netherite_sword->height);
    // netherite_sword->data = mlx_get_data_addr(netherite_sword->image, &netherite_sword->bpp, &netherite_sword->size_line, &netherite_sword->endian);
    // t->items[255] = netherite_sword;
}