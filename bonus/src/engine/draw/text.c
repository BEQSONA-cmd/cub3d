/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/24 18:19:09 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_string_queue(t_string **q)
{
    if (*q)
    {
        if ((*q)->str){
            // free((*q)->str);
            (*q)->str = NULL;
        }
        free(*q);
        *q = NULL;
    }
}


void clear_string_queue(t_render *r)
{
    printf("Clearing string queue\n");
    pthread_mutex_lock(&r->string_queue_mutex);

    t_string *current = r->string_queue;
    t_string *next = NULL;

    while (current != NULL)
    {
        next = current->next;    // Save the next pointer
        remove_string_queue(&current);  // Free the current image
        current = next;          // Move to the next image
    }

    r->string_queue = NULL;  // Set the queue to NULL

    pthread_mutex_unlock(&r->string_queue_mutex);
}

void put_string_queue(t_render *r)
{
    pthread_mutex_lock(&r->string_queue_mutex);

    t_string *q = r->string_queue;
    while (q != NULL)
    {
        render_string(q);

        t_string *tmp = q->next;
        remove_string_queue(&q);  // Properly free the dequeued image
        q = tmp;
    }

    r->string_queue = NULL;

    pthread_mutex_unlock(&r->string_queue_mutex);
}

void enqueue_string(t_async *async)
{
    t_string *str = (t_string *)async->arg;
    t_render *r = render();
    t_string *new = calloc(sizeof(t_string),1);
    ft_memcpy(new, str, sizeof(t_string));
    
    new->next = NULL;

    pthread_mutex_lock(&r->string_queue_mutex);

    if (!r->string_queue)
        r->string_queue = new;
    else
    {
        t_string *q = r->string_queue;
        while (q->next)
            q = q->next;
        q->next = new;
    }

    pthread_mutex_unlock(&r->string_queue_mutex);
}

void end_string(t_async *async)
{
    t_string *str = (t_string *)async->arg;
    if (str)
    {
        if (str->str){
            // ft_free(str);
            str->str = NULL;
        }
        ft_free(str);
    }
}

void render_string_async(t_string *str)
{
    t_async *async = new_async();
    t_string *str_copy = ft_malloc(sizeof(t_string));

    // Deep copy the image data
    str_copy->str = ft_strdup(str->str);
    str_copy->x = str->x;
    str_copy->y = str->y;
    str_copy->color = str->color;
    str_copy->size = str->size;
    str_copy->time = str->time;
    str_copy->background = str->background;
    str_copy->padding = str->padding;
    str_copy->next = NULL;

    ft_free(str->str);

    async->process = &enqueue_string;
    async->end = end_string;
    async->arg = str_copy;
    async->process_time = 10;
    async->time = str->time;
    start_async(async);
}

void put_string(char *str, int x, int y, int color, float size)
{
    t_string string = {0};
    string.str = str;
    string.x = x;
    string.y = y;
    string.color = color;
    string.size = size;
    string.padding = 0;
    render_string(&string);
}

// https://stmn.itch.io/font2bitmap
void render_string(t_string *string)
{
    t_texture *font = textures()->font;
    t_render *r = render();

    const int char_width = 32;
    const int char_height = 32; 
    const int chars_per_row = 16; 

    int char_pixel_data[95][32 * 32];

    for (int index = 0; index < 95; ++index)
    {
        int row = index / chars_per_row;
        int col = index % chars_per_row;
        int src_x = col * char_width;
        int src_y = row * char_height;
        
        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                int pixel_color = get_pixel_from_image(font, src_x + i, src_y + j);
                char_pixel_data[index][i + j * char_width] = pixel_color;
            }
        }
    }

    char *str = string->str;
    int x = string->x;
    int y = string->y;
    int color = string->color;
    float size = string->size;
    int padding = string->padding;

    int len = ft_strlen(str);

    if (string->background != NULL)
    {
        for (int i = -padding; i < char_width * len * size; ++i)
        {
            for (int j = -padding; j < char_height * size; ++j)
            {
                put_pixel(x + i , y + j , string->background, r);
            }
        }
    }

    while (*str)
    {
        char ch = *str++;
        if (ch && ch < ' ' || ch > '~') continue; 

        int char_index = ch - ' ';
        int *pixels = char_pixel_data[char_index];

        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                // if(string->background != NULL)
                //     put_pixel(x + i , y + j , string->background, r);
                int pixel_color = pixels[i + j * char_width];
                if (pixel_color > 0) 
                {
                    for (int dx = 0; dx < size; ++dx)
                    {
                        for (int dy = 0; dy < size; ++dy)
                        {
                            put_pixel(x + i * size + dx, y + j * size + dy, color, r);
                        }
                    }
                }
            }
        }

        x += char_width * size;
    }
}


void timer_process(t_async *async){
    char *time = ft_itoa((async->time - async->time_elapsed) / 1000);

    t_string str = {0};
    str.str = time;
    str.x = ((t_location *)async->arg)->x;
    str.y = ((t_location *)async->arg)->y;
    str.color = 0xc2410c;
    str.size = 3;
    str.time = 1000;
    render_string_async(&str);
}

void string_timer(int time, t_location *location)
{
    t_async *async = new_async();
    async->process = &timer_process;
    async->process_time = 1000;
    async->arg = (void *)(location);
    async->time = time;
    start_async(async);
}

void interaction_notify(char *str)
{
    t_string notify = {0};
    notify.str = str;
    notify.color = 0xeab308;
    notify.size = 0.7;
    notify.x = CENTER_WIDTH - 330;
    notify.y = HEIGHT -100;

    t_texture *t = textures()->ui->button_long;
    const int length  = ft_strlen(str);
    for(int i = 0; i < length / 5; i++)
        put_image(t, CENTER_WIDTH - 400 + (i * t->width*0.7 - ((i-1) * 4)), HEIGHT -115, 0.7);
    render_string(&notify);
}