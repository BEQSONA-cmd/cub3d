/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/08/28 20:50:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int calculate_direction(float x, float y, float cosangle, float sinangle, t_cube *c, int *tex_x)
{
    int sx = cosangle > 0 ? 1 : -1; 
    int sy = sinangle > 0 ? 1 : -1;

    if (is_touching(x - sx, y, c) || is_touching(x - sx, y - sy, c)) {
        *tex_x = (int)x % BLOCK_SIZE;
        return (sy == 1) ? 1 : 3;
    } else if (is_touching(x, y - sy, c) || is_touching(x, y, c)) {
        *tex_x = (int)y % BLOCK_SIZE;
        return (sx == 1) ? 2 : 4;
    } else if (touch_block(c->map->doors, x - sx, y)) {
        *tex_x = (int)x % BLOCK_SIZE;
        return 5;
    } else if (touch_block(c->map->doors, x, y - sy)) {
        *tex_x = (int)y % BLOCK_SIZE;
        return 5;
    } else if (touch_block(c->map->blocks, x - sx, y)) {
        *tex_x = (int)x % BLOCK_SIZE;
        return 6;
    } else if (touch_block(c->map->blocks, x, y)) {
        *tex_x = (int)y % BLOCK_SIZE;
        return 6;
    } else if (touch_line(c->map->lines, x - sx, y) == 1){
        *tex_x = (int)x % BLOCK_SIZE;
        return 3;
    } else if (touch_line(c->map->lines, x, y) == 1) {
        *tex_x = (int)y % BLOCK_SIZE;
        return 3;
    } else if(touch_line(c->map->lines, x - sx, y) == 2)
    {
        *tex_x = (int)x % BLOCK_SIZE;
        return 1;
    } else if(touch_line(c->map->lines, x, y) == 2)
    {
        *tex_x = (int)y % BLOCK_SIZE;
        return 1;
    } else if(touch_chest(c->map->chests, x - sx, y))
    {
        *tex_x = (int)x % BLOCK_SIZE;
        return 7;
    } else if(touch_chest(c->map->chests, x, y))
    {
        *tex_x = (int)y % BLOCK_SIZE;
        return 7;
    }
    return 0;
}


static bool find_hitbox(float x, float y, t_cube *c)
{
    if (is_touching(x, y, c))
        return true;
    if (touch_block(c->map->blocks, x, y))
        return true;
    if (touch_block(c->map->doors, x, y))
        return true;
    if(touch_line(c->map->lines, x, y))
        return true;
    return false;
}

void draw_line(float angle, int start_x, ThreadParams *params)
{
    t_cube *c = params->cube;
    const t_player *p = params->player;

    float cosangle = cos(angle);
    float sinangle = sin(angle);

    float x = p->x_px;
    float y = p->y_px;
    float save_x = 0;
    float save_y = 0;
    bool save = false;
    int dist;

    int local_tex_x;  // Thread-local variable for tex_x
    int local_side;   // Thread-local variable for side

    while (!find_hitbox(x, y, c))
    {
        if(!save && touch_chest(c->map->chests, x, y))
        {
            save = true;
            save_x = x;
            save_y = y;
        }
        x += cosangle;
        y += sinangle;
    }

    // wall
    dist = view_lane_distance(x, y, angle);
    local_side = calculate_direction(x, y, cosangle, sinangle, c, &local_tex_x);
    int line_height = (BLOCK_SIZE * HEIGHT) / dist;
    draw_floor(line_height, start_x, params, angle);
    // chest

    // Draw the floor

    // Draw the wall using the thread-local variables
    // pthread_mutex_lock(params->mutex);
    draw_wall(line_height, start_x, params, dist, local_side, local_tex_x);
    {
        int chest_dist = view_lane_distance(save_x, save_y, angle);
        int chest_height = (BLOCK_SIZE * HEIGHT) / chest_dist;
        int chest_local_side = calculate_direction(save_x, save_y, cosangle, sinangle, c, &local_tex_x);
        draw_chest(chest_height, start_x, params, dist, chest_local_side, local_tex_x);
    }
    // pthread_mutex_unlock(params->mutex);
}
