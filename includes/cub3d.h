/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:55:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/20 05:21:43 by dmartiro         ###   ########.fr       */
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

#define WIDTH 1920
#define HEIGHT 1280

#define PI_HALF (PI / 2)            // 90 
#define PI 3.1415926535             // 180
#define PI_3 (3 * (PI_HALF / 2))    // 270
#define PI_2 (PI * 2)               // 360
#define SPEED 0.08
#define ROT 0.05
#define IS_INVALID 1
#define IS_VALID 0
#define IS_OPPENED 2
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
	t_vec	old_dir;
    t_vec   dir;
    t_vec   plane;
	t_vec	old_plane;
	double	angle;
	double	cdir;
	double	fov;
	double	mouse_x;
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
	int		wallColor;
};

struct s_screen
{
    void    *mlx;
    void    *win;
};

t_game  *init(void);
int     contains(char *source, char *find);
int     update_loop(int kyecode, t_game *game);
int		esc(int keycode, t_game *game);
int		close_win(t_game *game);
int		mouse_(int x, int y, t_game *game);
int     rgb(char *txt);
int		player(t_game *game);
int		check_board(t_game *game);
int		checkall(int **mmap, int y, int x, int w, int h);
int     *set_matrix_line(char *strline, int map_width);
char    **create_map_buffer(char *filename);
char	*set_map(char *s1, int delimiter, char *s2);
void    parser(t_game *game, char *filename);
void    failure(void);
void	free_char_pp(char ***pp);
void    set_instances(t_game *game);
void    set_matrix(t_game *game);
void    get_map_sizes(t_game *game, char **split);
void    put_textures(t_game *game, int i);
void    put_colors(t_game *game, int i);
char    *path(char *line);
void    set_int_matrix(t_game *game, char **split);
void    play(t_game *game);
void    draw(t_game *game);
void	mpp(t_data *data, int x, int y, int color);
double	replace_angle_360(double angle);
double	degree_to_radian(double degree);

void	w(t_game *game);
void	a(t_game *game);
void	s(t_game *game);
void	d(t_game *game);
void	left_right(int k, t_game *game);