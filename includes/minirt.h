#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "elements.h"
# include "../LIBFT/libft.h"

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2	
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_TAB 48
# define KEY_ESC 53

# define INT_MAX   __INT_MAX__

typedef struct s_global
{
	void		*mlx;
	void		*mlx_win;
	int			image_width;
	int			image_height;
	float		aspect_ratio;
	char		**split_save;
	char		*line;
	int			cur_cam;
	int			cam_count;
	t_camera	*cam;
	t_ray		ray;
	int			dec_color;
	t_vector	point;
	t_vector	color1;
	t_vector	color2;
	t_vector	ray_color;
	t_vector	color_atm;
	float		t;
	float		k;
	float		closest_t;
	int			scroll;
	int			res_parse;
	int			ambient_parse;
	t_ambient	ambient;
	t_object	*obj;
	t_list		*obj_list;
	t_list		*cam_list;
	t_list		*light_list;
	int			ref_count;
	int			screenshot;
}				t_global;

t_vector	create_vec(float x, float y, float z);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_sub_float(t_vector v1, float t);
t_vector	vec_add_float(t_vector v1, float d);
t_vector	vec_mul_vec(t_vector v1, t_vector v2);
t_vector	vec_mul_float(t_vector v1, float t);
t_vector	vec_div(t_vector v1, t_vector v2);
t_vector	vec_div_float(t_vector v1, float t);
t_vector	vec_normalize(t_vector v);
t_vector	vec_cross(t_vector v1, t_vector v2);
float		vec_length_squared(t_vector v);
float		vec_dot(t_vector v1, t_vector v2);
float		vec_length(t_vector v);
int			create_color(float r, float g, float b);
int			create_trgb(int t, int r, int g, int b);
void		add_gradient(t_global *core, t_ray *r, t_object *sph);
t_vector	apply_intensity(float intensity, t_vector color);
t_vector	color_average(t_vector color1, t_vector color2);
t_vector	add_color(t_vector color1, t_vector color2);
t_vector	color_average2(t_vector color1, t_vector color2, float intensity);
t_ray		create_ray(t_vector origin, t_vector direction);
t_vector	find_point(t_global *core, t_ray *r);
t_vector	ray_color(t_ray *r, t_global *core);
t_ray		calc_ray(t_global *core, t_ray r, float j, float i);
void		create_sphere(t_global *core, t_object *sph,
				t_vector ori, t_vector dir);
void		create_triangle(t_global *core, t_object *tr,
				t_vector ori, t_vector dir);
void		create_plane(t_global *core, t_object *pl,
				t_vector ori, t_vector dir);
void		create_square(t_global *core, t_object *sq,
				t_vector ori, t_vector dir);
void		create_cylinder(t_global *core, t_object *cy,
				t_vector ori, t_vector dir);
void		find_intersection(t_global *core, t_object *obj,
				t_vector ori, t_vector dir);
void		create_circle(t_global *core, t_object *cy, float t, int create);
void		setup_window(t_global *core);
void		setup_camera(t_global *core);
void		window_setup(t_global *core);
void		remake_window(t_global *core);
void		init_setup(t_global *core);
void		main_print(t_global *core);
void		my_mlx_pixel_put(t_imgdata *data, int x, int y, int color);
void		treat_obj(t_global *core, t_ray *r);
void		sky_box(t_global *core, t_ray *r);
void		ft_putstr(char *s);
int			str_is_equal(char *s1, char *s2);
int			char_count(char *str, char c);
void		exit_program(char *str, t_global *core);
t_vector	get_normal(t_global *core, t_vector point);
t_object	*new_object(t_object *obj, t_global *core);
void		free_all(t_global *core);
t_vector	cy_normal(t_object *cy, t_vector p);
int			scroll_press(int button, int x, int y, t_global *core);
int			scroll_release(int button, int x, int y, t_global *core);
int			count_split(char **split);
void		check_id(t_global *core);
char		**free_split(char **split);
t_vector	split_color(char *str, t_global *core);
t_vector	split_vec(char *str, t_global *core, int norm);
void		parse_light(t_global *core);
void		parse_camera(t_global *core);
void		parse_sphere(t_global *core);
void		parse_triangle(t_global *core);
void		parse_square(t_global *core);
void		parse_plane(t_global *core);
void		parse_cylinder(t_global *core);
void		parse_res(t_global *core);
void		parse_ambient(t_global *core);
void		parse_file(char *file_name, t_global *core);
int			split_check(char **split, int max);
t_vector	get_ray(t_object *light, t_vector p);
t_vector	change_color(t_global *core, t_vector point,
				t_vector normal, t_vector color);
t_vector	create_lights(t_global *core);
int			create_shadow(t_global *core, t_vector origin,
				t_vector dir, t_object *light);
void		reflection(t_global *core, t_ray *r);
void		create_cam(t_global *core);
void		select_cam(t_global *core);
void		change_cam(t_global *core);
int			check_camera_dir(t_vector *dir);
int			change_camera_dir(int x, int y, t_global *core);
void		create_screeshot(t_global *core, char *file);
void		create_file_info(t_global *core, int fd);
void		create_file_header(t_global *core, int padding_round, int fd);
int			camera_hook(int key, t_global *core);
int			get_key(int key, t_global *core);
void		circle(t_global *core, t_object *circle, t_vector ori, t_vector dir);

#endif