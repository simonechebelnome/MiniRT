/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:03:47 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:03:49 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	create_cam(t_global *core)
{
	t_list	*tmp_list;

	tmp_list = core->cam_list;
	while (tmp_list)
	{
		core->cam = tmp_list->content;
		setup_window(core);
		setup_camera(core);
		main_print(core);
		tmp_list = tmp_list->next;
	}
}

void	select_cam(t_global *core)
{
	t_list		*tmp;
	int			count;

	count = 0;
	tmp = core->cam_list;
	while (tmp)
	{
		if (core->cur_cam == count)
		{
			core->cam = tmp->content;
			core->cur_cam++;
			if (core->cur_cam == core->cam_count)
				core->cur_cam = 0;
			return ;
		}
		count++;
		tmp = tmp->next;
	}
}

void	change_cam(t_global *core)
{
	if (core->cam_count > 1)
	{
		select_cam(core);
		mlx_put_image_to_window(core->mlx, core->mlx_win, core->cam->img.img,
			0, 0);
	}
}
