#ifndef FT_ASYNC_H
#define FT_ASYNC_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "cub3d.h"

typedef struct s_async_manager t_async_manager;

typedef struct s_cube t_cube;
typedef struct s_player t_player;
typedef struct s_render t_render;

typedef struct s_async
{
    int id;
    pthread_t thread_id;
    pthread_mutex_t async_mutex;
    t_async_manager *manager;

    void (*start)(struct s_async *);
    void (*process)(struct s_async *);
    void (*end)(struct s_async *);
    void *arg;

    void (*end_mt)(void *);

    int time;
    int time_elapsed;
    int process_time;
    bool stopped;

    t_cube *cube;
    t_player *player;
    t_render *render;

} t_async;

typedef struct s_async_list
{
    t_async *current;
    struct s_async_list *next;
} t_async_list;

typedef struct s_async_manager
{
    pthread_mutex_t manager_mutex;
    pthread_mutex_t list_mutex;
    t_async_list *thread_list; // List of threads
    int thread_count;          // Number of threads
    bool stop_all;             // Flag to stop all tasks
} t_async_manager;

t_async_manager *get_manager();
void destroy_manager();

t_async *new_async();
void start_async(t_async *async);
void stop_all_async_tasks(void);
void add_to_list(t_async *async);
void remove_from_list(t_async *async);

void start_async_process(t_async *async);

#endif