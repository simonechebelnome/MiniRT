/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:05:09 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:05:10 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_imgdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_ray	calc_ray(t_global *core, t_ray r, float j, float i)
{
	float		u;
	float		v;
	t_vector	point;

	u = ((i / (float)core->image_width) - 0.5);
	v = ((j / (float)core->image_height) - 0.5);
	if (core->image_width < core->image_height)
		u *= core->aspect_ratio;
	if (core->image_width > core->image_height)
		v /= core->aspect_ratio;
	point = vec_add(vec_add(vec_add(vec_mul_float(core->cam->right, u),
					vec_mul_float(core->cam->up, v)), core->cam->pos),
			vec_normalize(core->cam->ori));
	r = create_ray(core->cam->pos,
			vec_normalize(vec_sub(point, core->cam->pos)));
	return (r);
}

void	main_print(t_global *core)
{
	t_ray	r;
	int		j;
	int		i;

	j = core->image_height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < core->image_width)
		{
			r = calc_ray(core, r, j, i);
			core->ray_color = ray_color(&r, core);
			core->dec_color = create_color(core->ray_color.x,
					core->ray_color.y, core->ray_color.z);
			my_mlx_pixel_put(&core->cam->img, i, j, core->dec_color);
			i++;
		}
		j--;
	}
}
