/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:05:26 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:05:27 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h" 

t_vector	get_ray(t_object *light, t_vector p)
{
	t_vector	light_ray;

	light_ray.x = 0;
	light_ray.y = 0;
	light_ray.z = 0;
	light_ray = vec_normalize(vec_sub(light->ori, p));
	light->dir = light_ray;
	return (light_ray);
}

int	create_shadow(t_global *core, t_vector origin,
		t_vector dir, t_object *light)
{
	t_list		*list;
	t_object	*obj;

	list = core->obj_list;
	core->t = INT_MAX;
	create_plane(core, light, origin, dir);
	core->k = core->t - 0.1;
	while (list)
	{
		obj = list->content;
		if (core->obj == obj)
		{
			if (core->obj->id == 6)
				list = list->next->next;
			list = list->next;
			continue ;
		}
		find_intersection(core, list->content, origin, dir);
		if (core->t > 0 && core->t < core->k)
			return (1);
		list = list->next;
	}
	return (0);
}

static	int	plane_side(t_global *core, t_object *light,
		t_vector origin, t_vector dir)
{
	t_object	cam_plane;
	t_global	rtt;
	t_object	light2;

	if (core->obj->id != 2 && core->obj->id != 3 && core->obj->id != 4)
		return (1);
	rtt.t = INT_MAX;
	light2.dir = dir;
	light2.ori = light->ori;
	create_plane(&rtt, &light2, origin, dir);
	rtt.k = rtt.t;
	cam_plane.ori = core->ray.origin;
	cam_plane.dir = dir;
	rtt.t = INT_MAX;
	create_plane(&rtt, &cam_plane, origin, dir);
	if (rtt.t == INT_MAX && rtt.k == INT_MAX)
		return (-1);
	if (rtt.t != INT_MAX && rtt.k != INT_MAX)
		return (1);
	return (0);
}

t_vector	change_color(t_global *core, t_vector point,
			t_vector normal, t_vector color)
{
	t_object	*light;
	t_vector	light_ray;
	t_list		*light_list;
	float		scal;

	light_list = core->light_list;
	while (light_list)
	{
		light = new_object(light_list->content, core);
		light_ray = get_ray(light, point);
		scal = vec_dot(normal, light_ray);
		scal *= plane_side(core, light, core->obj->ori, normal);
		if (scal <= 0 || create_shadow(core, point, light_ray, light))
		{
			light_list = light_list->next;
			free(light);
			continue ;
		}
		color = add_color(color, color_average(core->color_atm,
					apply_intensity(light->brightness * scal, light->color)));
		free(light);
		light_list = light_list->next;
	}
	return (color);
}

t_vector	create_lights(t_global *core)
{
	t_vector	normal;
	t_vector	color;

	color = color_average(core->color_atm,
			apply_intensity(core->ambient.brightness, core->ambient.color));
	normal = get_normal(core, core->point);
	color = change_color(core, core->point, normal, color);
	return (color);
}
