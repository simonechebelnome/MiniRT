#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_imgdata;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
}				t_ray;

typedef struct s_viewport
{
	t_vector	lower_left_corner;
	t_vector	hor_axis;
	t_vector	ver_axis;
	t_vector	camera_origin;
	t_vector	fov;
	float		vp_height;
	float		vp_width;
}				t_viewport;

typedef struct s_ambient
{
	float		brightness;
	t_vector	color;
}				t_ambient;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	ori;
	int			fov;
	t_imgdata	img;
	t_vector	up;
	t_vector	right;
}				t_camera;

typedef struct s_calc
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		t1;
	float		t2;
	t_vector	cross1;
	t_vector	cross2;
	t_vector	sub;
}				t_calc;

typedef struct s_object
{
	int			id;
	t_vector	ori;
	t_vector	dir;
	t_vector	point1;
	t_vector	point2;
	t_vector	point3;
	float		diameter;
	float		height;
	float		side_size;
	float		brightness;
	int			flag;
	t_vector	color;
}				t_object;

#endif