/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:04:45 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:04:47 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	camera_hook(int key, t_global *core)
{
	if (key == KEY_W)
		core->cam->pos.z += 0.4;
	else if (key == KEY_S)
		core->cam->pos.z -= 0.4;
	else if (key == KEY_D)
		core->cam->pos.x += 0.4;
	else if (key == KEY_A)
		core->cam->pos.x -= 0.4;
	else
		return (0);
	remake_window(core);
	return (1);
}

int	get_key(int key, t_global *core)
{
	if (key == KEY_TAB)
		change_cam(core);
	if (key == KEY_ESC)
		free_all(core);
	camera_hook(key, core);
	return (1);
}

void	remake_window(t_global *core)
{
	setup_camera(core);
	main_print(core);
	mlx_put_image_to_window(core->mlx, core->mlx_win, core->cam->img.img, 0, 0);
}

int	check_camera_dir(t_vector *dir)
{
	if (dir->x > 1)
		dir->x = 1;
	else if (dir->y > 1)
		dir->y = 1;
	else if (dir->z > 1)
		dir->z = 1;
	else if (dir->x < -1)
		dir->x = -1;
	else if (dir->y < 1)
		dir->y = -1;
	else if (dir->z < -1)
		dir->z = -1;
	else
		return (1);
	return (0);
}

int	change_camera_dir(int x, int y, t_global *core)
{
	if (x > 0 && x <= core->image_width && y > 0 && y
		< core->image_height && core->scroll)
	{
		if (x < core->image_width / 3)
			core->cam->ori.x -= 0.1;
		else if (x > core->image_width - core->image_width / 3)
			core->cam->ori.x += 0.1;
		else if (y < core->image_height / 3)
			core->cam->ori.y += 0.1;
		else if (y > core->image_height - core->image_height / 3)
			core->cam->ori.y -= 0.1;
		check_camera_dir(&core->cam->ori);
		remake_window(core);
	}
	return (1);
}
