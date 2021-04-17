/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:04:54 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:04:56 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_res(t_global *core)
{
	int	count;

	count = count_split(core->split_save);
	if (count != 3)
		exit_program("Parametri risoluzione non validi", core);
	core->image_width = ft_atoi(core->split_save[1]);
	core->image_height = ft_atoi(core->split_save[2]);
	if (core->image_width < 1 || core->image_height < 1)
		exit_program("Risoluzione schermo non valida", core);
	if (core->image_width > 2560)
		core->image_width = 2560;
	if (core->image_height > 1440)
		core->image_height = 1440;
	core->res_parse = 1;
}

void	parse_ambient(t_global *core)
{
	int	count;

	count = count_split(core->split_save);
	if (count != 3 || !split_check(core->split_save, 0))
		exit_program("Parametri luce ambientale non validi", core);
	core->ambient.brightness = ft_atof(core->split_save[1]);
	if (core->ambient.brightness < 0 || core->ambient.brightness > 1)
		exit_program("Valori luminosità ambientale fuori dal range", core);
	core->ambient.color = split_color(core->split_save[2], core);
	core->ambient_parse = 1;
}

void	parse_camera(t_global *core)
{
	int	count;

	core->cam = ft_calloc(1, sizeof(t_object));
	if (!core->cam)
		exit_program("Errore nel malloc", core);
	count = count_split(core->split_save);
	if (count != 4)
	{
		free(core->cam);
		exit_program("Errore nel parsing camera", core);
	}
	core->cam->pos = split_vec(core->split_save[1], core, 0);
	core->cam->ori = split_vec(core->split_save[2], core, 1);
	core->cam->fov = ft_atoi(core->split_save[3]);
	if (core->cam->fov < 0 || core->cam->fov > 180)
		exit_program("Valore FOV errato", core);
	ft_lstadd_back(&core->cam_list, ft_lstnew(core->cam));
}

void	parse_light(t_global *core)
{
	t_object	*light;
	int			count;

	light = ft_calloc(1, sizeof(t_object));
	if (!light)
		exit_program("Errore nel malloc", core);
	count = count_split(core->split_save);
	if (count != 4)
	{
		free(light);
		exit_program("Errore nel parsing luce", core);
	}
	light->ori = split_vec(core->split_save[1], core, 0);
	light->brightness = ft_atof(core->split_save[2]);
	if (light->brightness < 0 || light->brightness > 1)
		exit_program("Valori luminosità fuori dal range", core);
	light->color = split_color(core->split_save[3], core);
	ft_lstadd_back(&core->light_list, ft_lstnew(light));
}
