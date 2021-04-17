/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:04:06 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:04:08 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	window_setup(t_global *core)
{
	core->mlx_win = mlx_new_window(core->mlx, core->image_width,
			core->image_height, "MiniRT");
	if (!core->mlx_win)
		exit_program("Errore creazione finestra", core);
	mlx_hook(core->mlx_win, 2, 0, get_key, core);
	mlx_hook(core->mlx_win, 4, 0, scroll_press, core);
	mlx_hook(core->mlx_win, 5, 0, scroll_release, core);
	mlx_hook(core->mlx_win, 6, 0, change_camera_dir, core);
	mlx_put_image_to_window(core->mlx, core->mlx_win, core->cam->img.img, 0, 0);
	mlx_loop(core->mlx);
}

void	init_setup(t_global *core)
{
	create_cam(core);
	select_cam(core);
	if (core->screenshot)
	{
		create_screeshot(core, "screenshot.bmp");
		free_all(core);
	}
	window_setup(core);
}

int	main(int argc, char **argv)
{
	t_global	core;

	ft_bzero(&core, sizeof(t_global));
	core.mlx = mlx_init();
	if (!core.mlx)
		exit_program("Errore Inizializzazione MiniLibX", &core);
	if (argc > 3 || argc == 1 || (argc == 3 && !str_is_equal(argv[2],
				"--save")))
		exit_program("Argomenti sbagliati", &core);
	if (argc == 3 && str_is_equal(argv[2], "--save"))
		core.screenshot = 1;
	parse_file(argv[1], &core);
	init_setup(&core);
}
