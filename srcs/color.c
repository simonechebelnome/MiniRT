/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:03:54 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:03:55 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	create_color(float r, float g, float b)
{
	int	ir;
	int	ig;
	int	ib;
	int	colore;

	ir = (int)(255.999 * r);
	ig = (int)(255.999 * g);
	ib = (int)(255.999 * b);
	colore = create_trgb(0, ir, ig, ib);
	return (colore);
}

t_vector	apply_intensity(float intensity, t_vector color)
{
	if (intensity > 1)
		return (color);
	color.x = color.x * intensity;
	color.y = color.y * intensity;
	color.z = color.z * intensity;
	return (color);
}

t_vector	color_average(t_vector color1, t_vector color2)
{
	t_vector	average;

	average.x = color1.x * color2.x;
	average.y = color1.y * color2.y;
	average.z = color1.z * color2.z;
	return (average);
}

t_vector	add_color(t_vector color1, t_vector color2)
{
	t_vector	result;

	result.x = color1.x + color2.x;
	if (result.x > 1)
		result.x = 1;
	result.y = color1.y + color2.y;
	if (result.x > 1)
		result.x = 1;
	result.z = color1.z + color2.z;
	if (result.z > 1)
		result.z = 1;
	return (result);
}
