/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:05:03 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:05:04 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_sphere(t_global *core)
{
	t_object	*sp;
	int			count;

	count = count_split(core->split_save);
	sp = ft_calloc(1, sizeof(t_object));
	if (!sp)
		exit_program("Errore nel malloc sfera", core);
	if (count < 4 || count > 6 || !split_check(core->split_save, 5))
	{
		free(sp);
		exit_program("Errore parsing sfera", core);
	}
	sp->ori = split_vec(core->split_save[1], core, 0);
	sp->diameter = ft_atof(core->split_save[2]);
	if (sp->diameter < 0)
		exit_program("Diametro sfera negativo", core);
	sp->color = split_color(core->split_save[3], core);
	sp->id = 1;
	ft_lstadd_back(&core->obj_list, ft_lstnew(sp));
}

void	parse_triangle(t_global *core)
{
	t_object	*tr;
	int			count;

	count = count_split(core->split_save);
	tr = ft_calloc(1, sizeof(t_object));
	if (!tr)
		exit_program("Errore nel malloc triangolo", core);
	if (count < 4 || count > 6 || !split_check(core->split_save, 5))
	{
		free(tr);
		exit_program("Errore parsing triangolo", core);
	}
	tr->point1 = split_vec(core->split_save[1], core, 0);
	tr->point2 = split_vec(core->split_save[2], core, 0);
	tr->point3 = split_vec(core->split_save[3], core, 0);
	tr->color = split_color(core->split_save[4], core);
	tr->id = 2;
	ft_lstadd_back(&core->obj_list, ft_lstnew(tr));
}

void	parse_square(t_global *core)
{
	t_object	*sq;
	int			count;

	count = count_split(core->split_save);
	sq = ft_calloc(1, sizeof(t_object));
	if (!sq)
		exit_program("Errore nel malloc quadrato", core);
	if (count < 5 || count > 7 || !split_check(core->split_save, 6))
	{
		free(sq);
		exit_program("Errore nel parsing quadrato", core);
	}
	sq->ori = split_vec(core->split_save[1], core, 0);
	sq->dir = split_vec(core->split_save[2], core, 1);
	sq->side_size = ft_atof(core->split_save[3]);
	if (sq->side_size < 0)
		exit_program("Dimensione lato quadrato negativa", core);
	sq->color = split_color(core->split_save[4], core);
	sq->id = 3;
	ft_lstadd_back(&core->obj_list, ft_lstnew(sq));
}

void	parse_plane(t_global *core)
{
	t_object	*pl;
	int			count;

	count = count_split(core->split_save);
	pl = ft_calloc(1, sizeof(t_object));
	if (!pl)
		exit_program("Errore nel malloc piano", core);
	if (count < 4 || count > 6 || !split_check(core->split_save, 5))
	{
		free(pl);
		exit_program("Errore nel parsing piano", core);
	}
	pl->ori = split_vec(core->split_save[1], core, 0);
	pl->dir = split_vec(core->split_save[2], core, 1);
	pl->color = split_color(core->split_save[3], core);
	pl->id = 4;
	ft_lstadd_back(&core->obj_list, ft_lstnew(pl));
}

void	parse_cylinder(t_global *core)
{
	t_object	*cy;
	int			count;

	count = count_split(core->split_save);
	cy = ft_calloc(1, sizeof(t_object));
	if (!cy)
		exit_program("Errore nel malloc cilindro", core);
	if (count < 6 || count > 8 || !split_check(core->split_save, 7))
	{
		free(cy);
		exit_program("Errore nel parsing del cilindro", core);
	}
	cy->ori = split_vec(core->split_save[1], core, 0);
	cy->dir = split_vec(core->split_save[2], core, 1);
	cy->diameter = ft_atof(core->split_save[3]);
	cy->height = ft_atof(core->split_save[4]);
	if (cy->diameter < 0 || cy->height < 0)
		exit_program("Il cilindro ha parametri negativi", core);
	cy->color = split_color(core->split_save[5], core);
	cy->id = 5;
	ft_lstadd_back(&core->obj_list, ft_lstnew(cy));
	create_circle(core, cy, cy->height / 2 - 0.1, 1);
}
