/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/09/27 11:29:15 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <fcntl.h>
# include <sys/types.h>
# include <math.h>
# include <MLX42.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# define WIDTH 1024
# define HEIGHT 512

// ----------------------------------
// STRUCTS

/* vector with an x and y */
typedef struct s_vector
{
	uint32_t	x;
	uint32_t	y;
}				t_vector;

/* The 4 values that define a color */
typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

/* all info needed for an image */
typedef struct s_image {
	xpm_t		*texture;
	mlx_image_t	*img;
}				t_image;

typedef struct s_program {
	mlx_t					*mlx;
	t_image					img;
	t_image					*pixies;
	char					**map;
	int						frame;
	struct s_screen			*screen;
	struct s_render			*render;
	struct s_ray_casting	*rc;
	struct s_player			*player;
}				t_program;

typedef struct s_screen {
	uint32_t	width;
	uint32_t	height;
	uint32_t	half_width;
	uint32_t	half_height;
}				t_screen;

typedef struct s_render {
	uint32_t	delay;
}				t_render;

typedef struct s_ray_casting {
	uint32_t	increment_angle;
	uint32_t	precision;
}				t_ray_casting;

typedef struct s_player {
	uint32_t	fov;
	uint32_t	half_fov;
	uint32_t	x;
	uint32_t	y;
	uint32_t	angle;
}				t_player;



// to take out
typedef struct s_prop {
	int	item;
	int	exit;
	int	start_pos;
}				t_prop;

typedef struct s_nme
{
	t_vector	pos;
	t_vector	prev;
}				t_nme;

typedef struct s_update
{
	t_vector	basic_pos;
	t_vector	villain_pos;
	int			b_var;
	int			v_var;
}				t_update;

// ---------------------------------
// FUNCTIONS

t_vector	calculate_window_size(char **map);

t_vector	ft_get_coordinates(char **map, char prop);
t_vector	ft_get_x_and_y(char **map, char prop);
t_vector	ft_get_char_pos(char **map);
char		who_is_it(char **map);
void		ft_put_background(t_program *data, char *path);
t_image		*ft_put_sprite(t_program *data);
void		ft_invoke_pixie(char c, uint32_t *i, t_program *data,
				t_image *pixie);
void		ft_invoke_char(t_program *data, t_image *pixie, t_vector pos,
				int var);
void		ft_invoke_enemy(t_program *data, t_image *pixie, t_vector pos,
				int var);
void		ft_display_map(t_program *data, t_image *pixie);

void		ft_display_moves(t_program *d, int key, t_vector pos, int *counter);
void		move_ur_ass(t_program *data);
void		track_ur_move_left(t_program *data, t_nme death);
void		track_ur_move_up(t_program *data, t_nme death);
void		track_ur_move_right(t_program *data, t_nme death);
void		track_ur_move_down(t_program *data, t_nme death);
int			ft_swing(t_program *data);

int			ft_map_parser(char **map);
char		**ft_map_reader(char *filename);

void		ft_input(int key, void *param);
void		ft_update(void *param);

void		ft_prop_init(t_prop *obj);
int			verify_conditions(char **map);

void		check_args(char argc);
void		check_map_extension(char *argv[]);

void		ft_break_the_game(t_program *data, char *end_msg);
int			ft_close(void);

// my useless tools !!!
void		ft_put_background(t_program *data, char *path);
void		mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
				uint32_t color);
void		mlx_draw_line(mlx_image_t *img, int x0, int y0,
				int x1, int y1, uint32_t color);

void		ray_casting(t_program *data);
uint32_t	degrees_to_radians(uint32_t degrees);

#endif