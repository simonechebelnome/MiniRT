#include "../includes/minirt.h"

t_vector	vec_sub_float(t_vector v1, float t)
{
	t_vector	v;

	v.x = v1.x - t;
	v.y = v1.y - t;
	v.z = v1.z - t;
	return (v);
}

float	vec_length(t_vector v)
{
	return (sqrt(vec_length_squared(v)));
}

float	vec_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vec_normalize(t_vector v)
{
	t_vector	normalized_vect;
	float		len;

	len = vec_length(v);
	normalized_vect.x = v.x / len;
	normalized_vect.y = v.y / len;
	normalized_vect.z = v.z / len;
	return (normalized_vect);
}

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
