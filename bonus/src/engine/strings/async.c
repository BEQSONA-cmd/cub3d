/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:28:59 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 22:25:53 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool string_blink(t_string *str)
{
	static int		frame = 0;

	if(str->blink && str->blink > -1)
	{
		frame++;
		if(frame >= 2 * str->blink)
		{
			frame = 0;
		}
		
		return frame > str->blink;
	}

	return false;
}

static bool string_animation(t_string *str, t_string *new)
{
	static int		frame = 0;

	if(str->animation && str->animation > -1 && ft_strlen(str->str) > str->char_index)
	{
		new->str = ft_strdup(str->str);
		new->str[str->char_index] = '\0';
		frame++;
		if(frame > str->animation)
		{
			str->char_index++;
			frame = 0;
		}
	}
	
	if(frame == 0)
	{
		if(string_blink(str))
			return true;
	}
	return false;
}

void	enqueue_string(t_async *async)
{
	t_string		*q;
	t_render *const	r = render();
	t_string *const	str = (t_string *)async->arg;
	t_string *const	new = malloc(sizeof(t_string));

	ft_memcpy(new, str, sizeof(t_string));
	if(string_animation(str, new))
		return ;
	new->next = NULL;
	pthread_mutex_lock(&r->string_queue_mutex);
	if (!r->string_queue)
		r->string_queue = new;
	else
	{
		q = r->string_queue;
		while (q->next)
			q = q->next;
		q->next = new;
	}
	pthread_mutex_unlock(&r->string_queue_mutex);
}

void	end_string(t_async *async)
{
	t_string *const	str = (t_string *)async->arg;

	if (str)
	{
		if (str->str)
			str->str = NULL;
		ft_free(str);
	}
}

void	render_string_async(t_string *str)
{
	t_async *const	async = new_async();
	t_string *const	str_copy = ft_malloc(sizeof(t_string));

	str_copy->str = ft_strdup(str->str);
	str_copy->x = str->x;
	str_copy->y = str->y;
	str_copy->color = str->color;
	str_copy->size = str->size;
	str_copy->time = str->time;
	str_copy->background = str->background;
	str_copy->padding = str->padding;
	str_copy->animation = str->animation;
	str_copy->char_index = 0;
	str_copy->animation = -1;
	if(str->animation)
		str_copy->animation = str->animation;
	str_copy->blink = -1;
	if(str->blink)
		str_copy->blink = str->blink;
	str_copy->next = NULL;
	ft_free(str->str);
	async->process = &enqueue_string;
	async->end = end_string;
	async->arg = str_copy;
	async->process_time = 5;
	async->time = str->time;
	start_async(async);
}
