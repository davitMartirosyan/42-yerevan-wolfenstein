/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:55:14 by tumolabs          #+#    #+#             */
/*   Updated: 2023/04/26 00:30:03 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include "../libft/libft.h"
# define W 1024
# define H 800
# define PI_HALF 1.57079632675
# define PI 3.1415926535
# define PI_3 4.71238898025
# define PI_2 6.28318530718
# define SPEED 0.08
# define ROT 0.05
# define R 0.09
# define IS_INVALID 1
# define IS_VALID 0
# define IS_OPPENED 2

typedef struct s_screen		t_screen;
typedef struct s_tsc		t_tsc;
typedef struct s_game		t_game;
typedef struct s_player		t_player;
typedef struct s_vec		t_vec;
typedef struct s_data		t_data;
typedef struct s_texture	t_texture;
typedef struct s_texel		t_texel;
typedef struct s_getmath	t_getmath;

struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		w;
	int		h;
};

struct	s_texture
{
	void	*file;
	char	*img;
	int		w;
	int		h;
	int		bpp;
	int		size;
	int		endian;
	int		x;
	int		y;
};

struct	s_vec
{
	double	x;
	double	y;
};

struct	s_player
{
	t_vec	pos;
	t_vec	old_dir;
	t_vec	dir;
	t_vec	plane;
	t_vec	old_plane;
	double	angle;
	double	cdir;
	double	fov;
	double	mouse_x;
};

struct	s_texel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				wall_height;
	double			divide;
	double			wall_x;
	int				px;
	int				py;
};

struct s_getmath
{
	int			clr;
	double		angle;
	double		wall_x;
};

struct s_tsc
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		wall_color;
	int		wall;
};

struct s_game
{
	int			map_h;
	int			map_w;
	int			floor_color;
	int			ceiling_color;
	int			**mmap;
	int			news;
	int			colors;
	int			bpp[2];
	int			endian[2];
	int			line_len[2];
	char		**sdl;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	void		*dir[4];
	char		*addr[4];
	char		*map;
	t_tsc		tsc;
	t_data		img;
	t_texture	texture[4];
	t_screen	*screen;
	t_player	*player;
};

struct s_screen
{
	void	*mlx;
	void	*win;
};

t_game	*init(void);

int		contains(char *source, char *find);
int		update_loop(int kyecode, t_game *game);
int		esc(int keycode, t_game *game);
int		close_win(t_game *game);
int		mouse_(int x, int y, t_game *game);
int		rgb(char *txt);
int		player(t_game *game);
int		check_board(t_game *game);
int		checkall(int **mmap, int y, int x, int h);
int		*set_matrix_line(char *strline, int map_w);
int		rgb_tohex(int r, int g, int b);

char	**create_map_buffer(char *filename);
char	*set_map(char *s1, int delimiter, char *s2);
char	*path(char *line);

double	replace_angle_360(double angle);
double	degree_to_radian(double degree);

void	w(t_game *game);
void	a(t_game *game);
void	s(t_game *game);
void	d(t_game *game);
void	left_right(int k, t_game *game);
void	parser(t_game *game, char *filename);
void	failure(void);
void	free_char_pp(char ***pp);
void	set_instances(t_game *game);
void	set_matrix(t_game *game);
void	get_map_sizes(t_game *game, char **split);
void	put_textures(t_game *game, int i);
void	put_colors(t_game *game, int i);
void	set_int_matrix(t_game *game, char **split);
void	play(t_game *game);
void	draw(t_game *game);
void	start_end(int x, t_game *game);
void	mpp(t_data *data, int x, int y, int color);
void	draw_textured_walls(int x, t_game *game);
void	draw_sky(int x, t_game *game);
void	draw_floor(int x, t_game *game);
void	init_game_tsc(int x, t_game *game);
void	check_rays(t_game *game);
void	dda_algorithm_loop(t_game *game);
void	check_dependancies(t_game *game);
void	set_rgb(t_texture *texture, t_texel *texel, int x, int y);
void	checkangle(t_game *game, t_texel *texel, t_texture *data);

#endif
