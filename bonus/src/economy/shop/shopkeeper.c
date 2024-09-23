/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shopkeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:27 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 17:43:05 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void shopkeeper()
{
    t_player *p = player();

    float dist = distance(p->x_px / BLOCK_SIZE, p->y_px / BLOCK_SIZE, p->store->x, p->store->y);
    open_store();
    math_gui();

    if(dist < 1.5){
        p->GUI_temp = STORE;
        interaction_notify("Press G to open a shop");
    }else if(p->GUI_temp == STORE){
        p->GUI_temp = NONE;
        p->GUI = NONE;
        printf("You left the shop\n");
    }
}