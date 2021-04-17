#include "../includes/minirt.h"

static	void	inter(t_global *rt, t_object *cylinder, t_calc s,
					t_ray tmp_ray)
{
	t_object	plan;
	t_global	rtt;
	t_vector	inter;
	float		t;

	t = INT_MAX;
	if (s.t1 >= 0 && rt->t > s.t1)
		t = s.t1;
	else if (s.t2 >= 0 && rt->t > s.t2)
		t = s.t2;
	if (t == INT_MAX)
		return ;
	inter = vec_add(tmp_ray.origin, vec_mul_float(tmp_ray.dir, t));
	plan.dir = cylinder->dir;
	plan.ori = cylinder->ori;
	rtt.t = INT_MAX;
	create_plane(&rtt, &plan, inter, cylinder->dir);
	if (rtt.t <= cylinder->height / 2)
		rt->t = t;
	create_plane(&rtt, &plan, inter, vec_mul_float(cylinder->dir, -1));
	if (rtt.t <= cylinder->height / 2)
		rt->t = t;
}

void	create_cylinder(t_global *rt, t_object *cylinder, t_vector ori,
					t_vector dir)
{
	t_calc		s;
	t_ray		tmp_ray;
	t_vector	cross2;

	tmp_ray.origin = ori;
	tmp_ray.dir = dir;
	s.cross1 = vec_cross(tmp_ray.dir, cylinder->dir);
	s.sub = vec_sub(tmp_ray.origin, cylinder->ori);
	cross2 = vec_cross(s.sub, cylinder->dir);
	s.a = vec_dot(s.cross1, s.cross1);
	s.b = 2 * vec_dot(s.cross1, cross2);
	s.c = vec_dot(cross2, cross2) - (pow(cylinder->diameter / 2, 2)
			* vec_dot(cylinder->dir, cylinder->dir));
	s.delta = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.delta < 0)
		return ;
	s.a = 2 * s.a;
	s.delta = sqrt(s.delta);
	s.t1 = (-s.b - s.delta) / s.a;
	s.t2 = (-s.b + s.delta) / s.a;
	inter(rt, cylinder, s, tmp_ray);
}

void	create_circle(t_global *core, t_object *cy, float t, int create)
{
	t_object		*circle;

	circle = ft_calloc(1, sizeof(t_object));
	if (!circle)
		exit_program("Errone nel Malloc", core);
	circle->id = 6;
	circle->flag = 1;
	circle->ori = vec_add(cy->ori,
			vec_mul_float(vec_normalize(cy->dir), t));
	circle->dir = cy->dir;
	circle->diameter = cy->diameter;
	circle->color = cy->color;
	ft_lstadd_back(&core->obj_list, ft_lstnew(circle));
	if (create)
		create_circle(core, cy, (cy->height / -2) + 0.1, 0);
}

void	circle(t_global *core, t_object *circle, t_vector ori, t_vector dir)
{
	t_calc		s;
	t_vector	inter;

	s.a = vec_dot(vec_sub(ori, circle->ori), circle->dir);
	s.b = vec_dot(dir, circle->ori);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	s.t1 = -s.a / s.b;
	if (s.t1 < 0 || core->t < s.t1)
		return ;
	inter = vec_add(ori, vec_mul_float(dir, s.t1));
	inter = vec_sub(inter, circle->ori);
	s.delta = sqrt(vec_dot(inter, inter));
	if (s.delta <= circle->diameter / 2)
		core->t = s.t1;
}
