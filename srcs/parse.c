/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:04:29 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:04:31 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_file(char *file_name, t_global *core)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_program("Errore nell'apertura del file", core);
	while (get_next_line(fd, &core->line) > 0)
	{
		core->split_save = ft_setsplit(core->line, " \t\v\n\r\f");
		if (core->split_save[0])
			check_id(core);
		core->split_save = free_split(core->split_save);
		free(core->line);
	}
	close(fd);
	core->cam_count = ft_lstsize(core->cam_list);
	if (!core->cam_count)
		exit_program("Camera non inserita", core);
	if (!core->res_parse)
		exit_program("Nessuna risoluzione inserita", core);
}

void	check_id(t_global *core)
{
	if (str_is_equal(core->split_save[0], "R") && !core->res_parse)
		parse_res(core);
	else if (str_is_equal(core->split_save[0], "A") && !core->ambient_parse)
		parse_ambient(core);
	else if (str_is_equal(core->split_save[0], "c"))
		parse_camera(core);
	else if (str_is_equal(core->split_save[0], "l"))
		parse_light(core);
	else if (str_is_equal(core->split_save[0], "sp"))
		parse_sphere(core);
	else if (str_is_equal(core->split_save[0], "pl"))
		parse_plane(core);
	else if (str_is_equal(core->split_save[0], "sq"))
		parse_square(core);
	else if (str_is_equal(core->split_save[0], "cy"))
		parse_cylinder(core);
	else if (str_is_equal(core->split_save[0], "tr"))
		parse_triangle(core);
	else if (core->split_save[0][0] == '#' || str_is_equal(core->split_save[0]
			, "#"))
		;
	else
		exit_program("Errore Parsing", core);
}

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

t_vector	split_vec(char *str, t_global *core, int norm)
{
	t_vector	v;
	char		**split;

	split = ft_split(str, ',');
	if (count_split(split) != 3 || char_count(str, ',') != 2)
	{
		free_split(split);
		exit_program("Errore", core);
	}
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_split(split);
	if (norm && ((v.x > 1 || v.y > 1 || v.z > 1 || v.x < -1 || v.y
				< -1 || v.z < -1) || (!v.x && !v.y && !v.z)))
		exit_program("Valori vettore non validi", core);
	return (v);
}

t_vector	split_color(char *str, t_global *core)
{
	t_vector	c;
	char		**split;

	split = ft_split(str, ',');
	if (count_split(split) != 3 || char_count(str, ',') != 2)
	{
		free_split(split);
		exit_program("Errore", core);
	}
	c.x = ft_atof(split[0]) / 255;
	c.y = ft_atof(split[1]) / 255;
	c.z = ft_atof(split[2]) / 255;
	free_split(split);
	if (c.x > 1 || c.x < 0 || c.y > 1 || c.y < 0 || c.z > 1 || c.z < 0)
		exit_program("Errore Parsing colore", core);
	return (c);
}
