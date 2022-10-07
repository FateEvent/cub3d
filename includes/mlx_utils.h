/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/07 10:27:56 by albaur           ###   ########.fr       */
=======
/*   Updated: 2022/10/07 14:26:45 by faventur         ###   ########.fr       */
>>>>>>> cf6b520019f2554992bb97b9934745cf244b129a
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>
# include <MLX42.h>
# include "libft.h"
# define WIDTH 640
# define HEIGHT 480

// ----------------------------------
// STRUCTS

/* vector with an x and y */
typedef struct s_vector
{
	uint32_t	x;
	uint32_t	y;
}				t_vector;

typedef struct s_vector2
{
	float	x;
	float	y;
}				t_vector2;

/* The 4 values that define a color */
typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

struct s_texture {
	uint32_t		width;
	uint32_t		height;
	char			**bitmap;
	struct s_color	*colors;
}		t_texture;

typedef struct s_speed {
	float	movement;
	float	rotation;
}				t_speed;

typedef struct s_player {
	float			fov;
	float			half_fov;
	float			x;
	float			y;
	float			angle;
	struct s_speed	speed;
}				t_player;

typedef struct s_ray_casting {
	float	increment_angle;
	float	precision;
}				t_ray_casting;

typedef struct s_render {
	uint32_t	delay;
}				t_render;

typedef struct s_projection {
	float	width;
	float	height;
	float	half_width;
	float	half_height;
}				t_projection;

typedef struct s_screen {
	uint32_t	width;
	uint32_t	height;
	uint32_t	half_width;
	uint32_t	half_height;
	uint32_t	scale;
}				t_screen;

typedef struct s_map {
	char		**map;
	int			width;
	int			height;
}				t_map;

/* all info needed for an image */
typedef struct s_image {
	xpm_t		*texture;
	mlx_image_t	*img;
}				t_image;

typedef struct s_program {
	mlx_t					*mlx;
	t_image					img;
	t_image					*pixies;
	struct s_map			map;
	uint32_t				frame;
	struct s_screen			screen;
	struct s_projection		proj;
	struct s_render			render;
	struct s_ray_casting	rc;
	struct s_player			player;
	struct s_texture		texture;
}				t_program;

typedef struct s_key_input {
	float		player_cos;
	float		player_sin;
	float		new_x;
	float		new_y;
}				t_key_input;

// to take out
typedef struct s_prop {
	int	start_pos;
}				t_prop;

enum e_key {
	UP = 87,
	DOWN = 83,
	LEFT = 65,
	RIGHT = 68,
	ESCAPE = 256
};

// ---------------------------------
// FUNCTIONS

t_vector	ft_get_coordinates(char **map, char prop);
t_vector	ft_get_x_and_y(char **map, char prop);
t_image		*ft_put_sprite(t_program *data);
void		ft_invoke_pixie(char c, uint32_t *i, t_program *data,
				t_image *pixie);
void		ft_display_map(t_program *data, t_image *pixie);

// window functions
void		fill_window(t_program *data, uint32_t color);

int			ft_map_parser(char **map);
char		**ft_map_reader(char *filename);

void		ft_key_input(mlx_key_data_t keydata, void *param);
void		ft_update(void *param);

void		ft_prop_init(t_prop *obj);

void		check(int argc, char **argv);
void		check_args(char argc);
void		check_map_extension(char *argv[]);
void		check_map_integrity(char *path);
int			check_map_components(char **map);

// drawing tools
void		mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
				uint32_t color);
void		draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
				uint32_t color);
void		draw_vertical_line(mlx_image_t *img, t_vector draw_start,
				uint32_t draw_end, uint32_t color);

void		ray_casting(t_program *data);
float		degrees_to_radians(float degrees);

// vector utils
t_vector2	ft_floattovec2(float x, float y);
float		ft_vect2_distance_calc(t_vector2 start, t_vector2 finish);
void		ft_vec2_swap(t_vector2 *start, t_vector2 *finish);

#endif