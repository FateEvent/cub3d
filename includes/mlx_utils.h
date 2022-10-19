/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 12:11:12 by faventur         ###   ########.fr       */
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
#define WIDTH 640
#define HEIGHT 480
#define texWidth 64
#define texHeight 64
#define BPP 4

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

typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_image {
	xpm_t		*texture;
	mlx_image_t	*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	uint32_t	color_arr;
}				t_image;

typedef struct sprite
{
	double	x;
	double	y;
	int		texture;
}	t_sprite;

typedef struct s_texture {
	int				width;
	int				height;
	char			**bitmap;
	struct s_color	*colors;
}				t_texture;

typedef struct s_ray_data
{
	double		resolution_x;
	double		resolution_y;
	double		camera_x;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
	double		raydir_x;
	double		raydir_y;
	double		pos_x;
	double		pos_y;
	int			map_x;
	int			map_y;
	double		ray_side_x;
	double		ray_side_y;
	double		ray_delta_x;
	double		ray_delta_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		walldistance;
	int			lineheight;	
	int			drawstart;	
	int			drawend;	
	int			color;
	double		rotate_left;
	double		rotate_right;
	int			texx;
	int			texy;
	int			text_select;
	double		wall_x;
	double		step;
	double		texpos;
}	t_ray;

typedef struct s_key
{
	int	move_forward;
	int	move_back;
	int	move_left;
	int	move_right;
	int	rotate_left;
	int	rotate_right;
}	t_key;

typedef struct s_map {
	char	**map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor_color;
	t_color	ceiling_color;
}				t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	t_image		img;
	t_map		*map;
	uint32_t	frame;
	uint32_t	render_delay;
	uint32_t	img_index;
	t_image		*textures;
	int			floor;
	int			ceiling;
	void		*display;
	char		*display_add;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		player_spawn_dir;
	int			player_spawn_pos[2];
	int			edge_size;
	int			fov;
	int			shading;
	int			resolution_x;
	int			resolution_y;
	double		move_speed;
	double		rotate_speed;
	t_ray		ray_data;
	t_key		key;
	int			keycode;
	int			textures_nb;
	int			fd;
	int			is_map_started;
	int			refresh;
}				t_data;

typedef struct s_var
{
	double	old_dir_x;
	double	old_plane_x;
}				t_var;

typedef struct s_map_data
{
	char	**map;
	int		x_start;
	int		y_start;
	int		pos_x;
	int		pos_y;
	int		width;
	int		height;
	char	dir;
	int		nb_pass;
	int		no_move_possible;
	int		is_againt_wall;
	int		nb_move;
}	t_map_data;

typedef struct s_getcolor {
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;
	char	**colors;
	t_color	rgba;
}			t_getcolor;

typedef struct s_ctexture {
	char	str[2];
	int		index;
}			t_ctexture;

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
t_image		*ft_load_textures(t_data *data);
//void		ft_display_map(t_program *data, t_image *pixie);

// window functions
void		fill_window(t_data *data, uint32_t color);

int			ft_map_parser(char **map);
char		**ft_map_reader(char *filename);

void		ft_key_input(mlx_key_data_t keydata, void *param);
void		ft_update(void *param);

// parsing
t_map		*check(int argc, char **argv);
void		check_args(char argc);
void		check_map_extension(char *argv[]);
t_map		*check_map_integrity(char *path);
int			check_map_components(char **map);
char		**get_map_description(char **map);
int			get_color(char *str, t_map *mapStruct, int mode);
int			get_color_check(char **colors, ssize_t j);
int			get_texture(char *str, t_map *mapStruct, int mode);
int			invalid_check(char **map);
int			wall_check(char **map);
int			gap_check(char **map);
int			gap_check_reverse(char **map, ssize_t i, ssize_t j);
int			space_check(char **map, ssize_t i, ssize_t j);
int			hole_check(char **map);

// drawing tools
void		mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
				uint32_t color);
void		draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
				uint32_t color);
void		draw_vertical_line(mlx_image_t *img, t_vector draw_start,
				uint32_t draw_end, uint32_t color);
void		ft_print_texture(t_data *data, int x);
void		draw_ceiling(t_data *data, int x);
void		draw_floor(t_data *data, int x);

void		ray_casting(t_data *data);
float		degrees_to_radians(float degrees);

// vector utils
t_vector	ft_inttovec(int x, int y);
t_vector2	ft_floattovec2(float x, float y);
float		ft_vect2_distance_calc(t_vector2 start, t_vector2 finish);
void		ft_vec_swap(t_vector *start, t_vector *finish);
void		ft_vec2_swap(t_vector2 *start, t_vector2 *finish);

// colour tools
t_color		new_color(int r, int g, int b, int a);
t_color		hex_to_rgb(uint32_t hex_value);
t_color		lerp(t_color a, t_color b, float t);
int 		get_rgba(int r, int g, int b, int a);
int			rgb_to_hex(t_color rgb);
int			add_shade(double distance, int color);
int			get_opposite(int color);
void		turn_pixel_to_color(char *pixel, t_color color);
void		turn_img_to_color(t_image *image, t_color color);

void		ft_uchar_arr_display(unsigned char *arr, size_t size);
uint32_t	*ft_from_uchar_to_hex_arr(unsigned char *arr, size_t width, size_t height);
uint32_t	**hex_buf_creator(uint32_t *arr, size_t width, size_t height);
uint32_t	**ft_from_uchar_to_hex_buf(unsigned char *arr, size_t width, size_t height);
t_color		**rgb_buf_creator(uint32_t **buf, size_t width, size_t height);
t_color		**ft_from_uchar_to_rgb_buf(unsigned char *arr, size_t width, size_t height);

#endif