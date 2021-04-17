/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:05:14 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:05:15 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = direction;
	return (ray);
}

void	treat_obj(t_global *core, t_ray *r)
{
	core->point = vec_add(r->origin,
			vec_mul_float(r->dir, core->closest_t));
	core->color_atm = core->obj->color;
	core->color_atm = create_lights(core);
}

void	sky_box(t_global *core, t_ray *r)
{
	t_vector	norm_dir;

	core->color1 = create_vec(1.0, 1.0, 1.0);
	core->color2 = create_vec(0.5, 0.7, 1.0);
	norm_dir = vec_normalize(r->dir);
	core->k = 0.5 * (norm_dir.y + 1.0);
	core->color_atm = (vec_add(vec_mul_float(core->color1,
					(1.0 - core->k)), vec_mul_float(core->color2, core->k)));
}

t_vector	ray_color(t_ray *r, t_global *core)
{
	t_list		*elements;

	core->obj = NULL;
	core->t = INT_MAX;
	core->closest_t = INT_MAX;
	ft_bzero(&core->color_atm, sizeof(t_vector));
	elements = core->obj_list;
	while (elements)
	{
		find_intersection(core, elements->content, r->origin, r->dir);
		if (core->t > 0 && core->t < core->closest_t)
		{
			core->closest_t = core->t;
			core->obj = elements->content;
		}
		elements = elements->next;
	}
	if (core->obj)
		treat_obj(core, r);
	else
		sky_box(core, r);
	return (core->color_atm);
}
