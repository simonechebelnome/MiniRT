/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:04:00 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:04:02 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	find_intersection(t_global *core, t_object *obj,
		t_vector ori, t_vector dir)
{
	if (obj->id == 1)
		create_sphere(core, obj, ori, dir);
	else if (obj->id == 2)
		create_triangle(core, obj, ori, dir);
	else if (obj->id == 3)
		create_square(core, obj, ori, dir);
	else if (obj->id == 4)
		create_plane(core, obj, ori, dir);
	else if (obj->id == 5)
		create_cylinder(core, obj, ori, dir);
	else if (obj->id == 6)
		circle(core, obj, ori, dir);
}

void	create_sphere(t_global *core, t_object *sph, t_vector ori, t_vector dir)
{
	t_calc	s;

	s.sub = vec_sub(ori, sph->ori);
	s.a = vec_dot(dir, dir);
	s.b = 2 * vec_dot(dir, s.sub);
	s.c = vec_dot(s.sub, s.sub) - pow(sph->diameter / 2, 2);
	s.delta = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.delta < 0)
		return ;
	s.delta = sqrt(s.delta);
	s.a = 2 * s.a;
	s.t1 = (-s.b - s.delta) / s.a;
	s.t2 = (-s.b + s.delta) / s.a;
	if (s.t1 >= 0 && core->t > s.t1)
		core->t = s.t1;
	else if (s.t2 >= 0 && core->t > s.t2)
		core->t = s.t2;
}

void	create_triangle(t_global *core, t_object *tr,
		t_vector ori, t_vector dir)
{
	t_calc		s;
	t_vector	v1;
	t_vector	v2;
	t_vector	vec;
	t_vector	point;

	v1 = vec_sub(tr->point2, tr->point1);
	v2 = vec_sub(tr->point3, tr->point1);
	point = vec_cross(dir, v2);
	s.delta = vec_dot(v1, point);
	if (fabs(s.delta) < 0)
		return ;
	s.c = 1 / s.delta;
	vec = vec_sub(ori, tr->point1);
	s.a = vec_dot(vec, point) * s.c;
	if (s.a < 0 || s.a > 1)
		return ;
	vec = vec_cross(vec, v1);
	s.b = vec_dot(dir, vec) * s.c;
	if (s.b < 0 || s.a + s.b > 1)
		return ;
	core->t = vec_dot(v2, vec) * s.c;
}

void	create_plane(t_global *core, t_object *pl, t_vector ori, t_vector dir)
{
	t_calc	s;

	s.a = vec_dot(vec_sub(ori, pl->ori), pl->dir);
	s.b = vec_dot(dir, pl->dir);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	s.t1 = -s.a / s.b;
	if (s.t1 < 0 || core->t < s.t1)
		return ;
	core->t = s.t1;
}

void	create_square(t_global *core, t_object *sq, t_vector ori, t_vector dir)
{
	t_calc		s;
	t_vector	d;

	s.a = vec_dot(vec_sub(ori, sq->ori), sq->dir);
	s.b = vec_dot(dir, sq->dir);
	if (s.b == 0)
		return ;
	s.t1 = -s.a / s.b;
	d = vec_sub(vec_add(vec_mul_float(dir, s.t1), ori), sq->ori);
	s.t2 = sq->side_size / 2;
	if (fabs(d.x) > s.t2 || fabs(d.y) > s.t2 || fabs(d.z) > s.t2)
		return ;
	if (s.t1 > 0)
		core->t = s.t1;
}
