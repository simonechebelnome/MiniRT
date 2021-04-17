/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:05:32 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:05:33 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	free_all(t_global *core)
{
	ft_lstclear(&core->obj_list, free);
	ft_lstclear(&core->cam_list, free);
	ft_lstclear(&core->light_list, free);
	if (!core->screenshot)
	{
		mlx_clear_window(core->mlx, core->mlx_win);
		mlx_destroy_window(core->mlx, core->mlx_win);
	}
	exit(1);
}

void	exit_program(char *str, t_global *core)
{
	ft_putstr("Errore\n");
	ft_putstr(str);
	if (core->split_save)
		free_split(core->split_save);
	if (core->line)
		free(core->line);
	ft_lstclear(&core->obj_list, free);
	ft_lstclear(&core->cam_list, free);
	ft_lstclear(&core->light_list, free);
	exit(-1);
}

int	str_is_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}
