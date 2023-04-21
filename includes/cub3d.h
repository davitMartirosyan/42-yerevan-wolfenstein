/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:55:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/22 01:36:37 by dmkhitar         ###   ########.fr       */
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
#define HEIGHT 640
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
typedef struct s_data t_data;
typedef struct s_tsc t_tsc;
typedef struct s_texture t_texture;

struct s_texture
{
    void    *texture_p;
    int     width;
    int     height;
    int     x;
    int     y;
    int     bpp;
    int     size_line;
    int     endian;
    char*   data;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

};

struct s_data
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
    t_data      img;
    t_screen    *screen;
    t_player    *player;
    t_texture   texture[4];
};

struct s_tsc
{
    double	cameraX;
    double	rayDirX;
    double	rayDirY;
    double	sideDistX;
    double	sideDistY;
    double	deltaDistX;
    double	deltaDistY;
    double  perpWallDist;
    int		mapX;
    int		mapY;
    int		stepX;
    int		stepY;
    int		hit;
    int		side;
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
int     rgb_tohex(int r, int g, int b);
char    *path(char *line);
int     *set_matrix_line(char *strline, int map_width);
void    set_int_matrix(t_game *game, char **split);
int     check_board(t_game *game, char **board);
void    run(t_game *game);
void    player(t_game *game);
void    play(t_game *game);
void    draw(t_game *game);
int     update_loop(int kyecode, t_game *game);
void	mpp(t_data *data, int x, int y, int color);
// my code
void    set_rgb(t_texture *texture, unsigned char *red, unsigned char *green, unsigned char *blue, int x, int y);
int    set_texture_data(t_game *game);
