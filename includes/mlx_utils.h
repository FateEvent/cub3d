/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/11/02 15:07:55 by faventur         ###   ########.fr       */
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
# define BPP 4
# define NUMSPRITES 3

typedef struct s_vector
{
	uint32_t	x;
	uint32_t	y;
}				t_vector;

typedef struct s_vector2
{
	double	x;
	double	y;
}				t_vector2;

typedef struct s_vector3
{
	int	x;
	int	y;
}				t_vector3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_image
{
	xpm_t		*texture;
	mlx_image_t	*img;
	t_vector2	size;
}				t_image;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texture;
}				t_sprite;

typedef struct s_minimap
{
	t_vector2	pos;
	mlx_image_t	*img;
}			t_minimap;

typedef struct s_map
{
	char		**map;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*ceiling_texture;
	char		*floor_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	int			mode;
	t_vector	spawn_pos;
	char		dir;
	t_minimap	*minimap;
	t_vector2	size;
	char		*map_str;
	int			*size_arr;
}				t_map;

typedef struct s_mouse
{
	double		pcos;
	double		psin;
	double		ncos;
	double		nsin;
	int			focus;
}			t_mouse;

typedef struct s_key_hook
{
	double		pcos;
	double		psin;
	double		ncos;
	double		nsin;
}				t_key;

typedef struct s_sprite_caster
{
	t_vector2	sprite;
	t_vector2	transform;
	double		inv_det;
	int			sprite_screen_x;
	int			sprite_width;
	int			sprite_height;
	t_vector3	draw_start;
	t_vector3	draw_end;
	int			stripe;
	int			d;
	t_vector3	tex;
	t_sprite	*sprites;
	int			*sprite_order;
	double		*sprite_dist;
	double		*z_buffer;
}				t_s_caster;

typedef struct s_floor_casting
{
	t_vector2	ray_dir0;
	t_vector2	ray_dir1;
	int			p;
	double		pos_z;
	double		row_distance;
	t_vector2	floor_step;
	t_vector2	floor;
	t_vector	cell;
	t_vector	t;
	int			floor_tex;
	int			ceiling_tex;
}				t_floor;

typedef struct s_ray_data
{
	t_vector2	resolution;
	double		camera_x;
	t_vector2	plane;
	t_vector2	dir;
	t_vector2	ray_dir;
	t_vector2	pos;
	t_vector	map_pos;
	t_vector2	ray_side;
	t_vector2	ray_delta;
	t_vector	step_coord;
	int			hit;
	int			side;
	double		wall_distance;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_vector	tex;
	int			text_select;
	double		wall_x;
	double		step;
	double		tex_pos;
	t_floor		fl;
	t_key		k;
	t_mouse		m;
	int			half_width;
	t_map		*map;
	t_s_caster	sprite;
	uint32_t	**tex_buf;
}				t_ray;

typedef struct s_speed
{
	double		movement;
	double		rotation;
}				t_speed;

typedef struct s_player
{
	char		player_spawn_dir;
	t_vector	player_spawn_pos;
	int			fov;
	t_speed		speed;
	double		yaw;
	int			start_direction;
}				t_player;

typedef struct s_screen
{
	t_image		display;
}				t_screen;

typedef struct s_data
{
	mlx_t		*mlx;
	t_map		*map;
	t_screen	screen;
	uint32_t	render_delay;
	uint32_t	img_index;
	t_image		*textures;
	int			edge_size;
	int			shading;
	t_player	player;
	t_ray		ray_data;
	int			keycode;
	int			fd;
	int			refresh;
	int			key;
}				t_data;

typedef struct s_var
{
	double		old_dir_x;
	double		old_plane_x;
	double		rotation;
	double		movement;
	uint32_t	width;
	uint32_t	height;
	uint32_t	color;
	int			x;
	int			y;
	uint8_t		*pixels;
	uint32_t	i;
	uint32_t	j;
}				t_var;

typedef struct s_getcolor
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;
	char	**colors;
	t_color	rgba;
}			t_getcolor;

typedef struct s_ctexture
{
	char	str[2];
	int		index;
}			t_ctexture;

typedef struct s_shape
{
	int			x;
	int			y;
	int			width;
	int			height;
	double		dim;
	t_image		*img;
}				t_shape;

// init
void		init_minimap(t_data *data);
void		init_struct(t_data *data);
void		init_direction(t_data *data);
t_vector	ft_get_coordinates(char **map, char prop);
t_vector	ft_get_x_and_y(char **map, char prop);
t_image		*ft_load_textures(t_data *data);

// window functions
void		mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
				uint32_t color);
void		fill_window(t_data *data, uint32_t color);

// hooks
void		ft_key_input(t_data *data);
void		ft_key_hook(mlx_key_data_t keydata, void *param);
void		ft_key_input_arrows(t_data *data, t_ray *ray, t_var *var);
void		ft_mouse_input(double x, double y, void *param);
void		ft_update(void *param);

// parsing functions
char		**ft_map_reader(char *filename);
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
int			check_texture(t_map *m, char *map, int *count, t_ctexture c);
int			check_texture_batch(t_map *m, char **map, size_t i, int *count);
int			get_spawn_position(t_map *m);
void		init_direction(t_data *data);

// ray casting tools
void		floor_casting(t_data *data, t_ray *ray);
void		ray_casting(t_data *data);
void		ray_data_init(t_ray *ray, int x);
void		ray_delta_calculator(t_ray *ray);
void		rayside_calculator(t_ray *ray);
void		ray_launcher(t_ray *ray);
void		wall_distance_calculator(t_ray *ray);
void		wall_line_calculator(t_ray *ray);
void		texture_x_pos_calculator(t_data *data, t_ray *ray);
void		texture_y_pos_calculator(t_data *data, t_ray *ray);
void		choose_wall_texture(t_ray *ray);
void		sprite_caster(t_data *data, t_ray *ray, t_var *v);
void		doing_some_math(t_ray *ray, int i);
void		points_lines_designer(t_ray *ray);
void		line_drawer(t_data *data, t_ray *ray, t_var *v, int i);
uint32_t	get_shading(uint32_t color, t_ray ray);

// drawing tools
void		draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
				uint32_t color);
void		draw_vertical_line(mlx_image_t *img, t_vector draw_start,
				uint32_t draw_end, uint32_t color);
void		draw_walls(t_data *data, int x);
void		draw_ceiling(t_data *data, int x);
void		draw_floor(t_data *data, int x);
void		draw_minimap(t_data	*data);
void		draw_rect(mlx_image_t *img, t_shape rect, int color);

// sprites
void		load_sprites(t_data *data, t_image *texture);

// minimap
void		get_map_size(t_data *data);
void		get_map_str(t_data *data);
void		get_size_arr(t_data *data, int y);

// vector utils
t_vector	ft_inttovec(int x, int y);
t_vector2	ft_doubletovec2(double x, double y);
double		ft_vect2_distance_calc(t_vector2 start, t_vector2 finish);
void		ft_vec_swap(t_vector *start, t_vector *finish);
void		ft_vec2_swap(t_vector2 *start, t_vector2 *finish);

// color tools
t_color		new_color(int r, int g, int b, int a);
t_color		hex_to_rgb(uint32_t hex_value);
t_color		lerp(t_color a, t_color b, double t);
double		lerp_double(double a, double b, double t);
double		inv_lerp(double a, double b, double value);
int			get_rgba(int r, int g, int b, int a);
int			rgb_to_hex(t_color rgb);
int			add_shade(double distance, int color);
int			get_opposite(int color);
void		turn_pixel_to_color(char *pixel, t_color color);
void		turn_img_to_color(t_image *image, t_color color);

// utils
void		ft_uchar_arr_display(unsigned char *arr, size_t size);
uint32_t	*uchar_to_arr(unsigned char *arr, size_t width,
				size_t height);
uint32_t	**hex_buf_creator(uint32_t *arr, size_t width, size_t height);
uint32_t	**ft_from_uchar_to_hex_buf(unsigned char *arr, size_t width,
				size_t height);
t_color		**rgb_buf_creator(uint32_t **buf, size_t width, size_t height);
t_color		**ft_from_uchar_to_rgb_buf(unsigned char *arr, size_t width,
				size_t height);
void		ft_print_map(char **map);
void		sort_sprites(int *order, double *dist, int amount);
double		get_time(void);
void		tex_to_img(t_data *data, t_image *texture, size_t i);

#endif