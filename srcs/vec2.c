#include "../includes/minirt.h"

t_vector	vec_mul_vec(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vector	vec_mul_float(t_vector v1, float t)
{
	t_vector	v;

	v.x = v1.x * t;
	v.y = v1.y * t;
	v.z = v1.z * t;
	return (v);
}

t_vector	vec_div(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}

t_vector	vec_div_float(t_vector v1, float t)
{
	t_vector	v;

	v.x = v1.x / t;
	v.y = v1.y / t;
	v.z = v1.z / t;
	return (v);
}

float	vec_length_squared(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
