/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:55:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/16 01:18:15 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "get_next_line.h"
#include "../libft/libft.h"

#define IS_INVALID 1
#define IS_VALID 0
#define IS_OPPENED 2
#define WIDTH 1024
#define HEIGHT 800
/*
    Player Pos
    N -> 30 -> {0, 1}       
    S -> 35 -> {0, -1}
    W -> 39 -> {1, 0}
    E -> 21 -> {-1, 0}
*/

typedef struct s_screen t_screen;
typedef struct s_game t_game;
typedef struct s_player t_player;
typedef struct s_vec t_vec;
typedef struct s_img t_img;

struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     len;
    int     endian;  
};

struct s_vec
{
    double  x;
    double  y;
};

struct s_player
{
    t_vec   pos;
    t_vec   dir;
    t_vec   plane;
};

struct s_game
{
    int         map_h;
    int         map_w;
    int         floor_color;
    int         ceiling_color;
    int         **mmap;
    int         news;
    int         colors;
    char        **sdl;
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    char        *map;
    t_img       img;
    t_screen    *screen;
    t_player    *player;
};

struct s_screen
{
    void    *mlx;
    void    *win;
};

t_game  *init(void);
void    parser(t_game *game, char *filename);
char    **create_map_buffer(char *filename);
void    failure(void);
void	free_char_pp(char ***pp);
void    set_instances(t_game *game);
void    set_matrix(t_game *game);
void    get_map_sizes(t_game *game, char **split);
char	*set_map(char *s1, int delimiter, char *s2);
int     contains(char *source, char *find);
void    put_textures(t_game *game, int i);
void    put_colors(t_game *game, int i);
int     rgb(char *txt);
char    *path(char *line);
int     *set_matrix_line(char *strline, int map_width);
void    set_int_matrix(t_game *game, char **split);
int     check_board(t_game *game, char **board);
void    run(t_game *game);
void    player(t_game *game);
void    play(t_game *game);
void    draw(t_game *game);