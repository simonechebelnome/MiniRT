/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:05:20 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:05:21 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	setup_window(t_global *core)
{
	core->cam->img.img = mlx_new_image(core->mlx, core->image_width,
			core->image_height);
	if (!core->cam->img.img)
		exit_program("Errore creazione immagine", core);
	core->cam->img.addr = mlx_get_data_addr(core->cam->img.img,
			&core->cam->img.bits_per_pixel,
			&core->cam->img.line_length, &core->cam->img.endian);
	if (!core->cam->img.addr)
		exit_program("Errore creazione data address", core);
}

void	setup_camera(t_global *core)
{
	core->cam->up = create_vec(0.0, -1, 0.0);
	core->aspect_ratio = (float)core->image_width / (float)core->image_height;
	core->cam->right = vec_cross(vec_normalize(core->cam->ori), core->cam->up);
	core->cam->up = vec_cross(core->cam->right, vec_normalize(core->cam->ori));
	core->closest_t = 0;
	core->t = 0;
}
