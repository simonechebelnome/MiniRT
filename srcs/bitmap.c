/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:03:40 by smenna            #+#    #+#             */
/*   Updated: 2021/04/10 10:03:42 by smenna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	create_file_header(t_global *core, int padding_round, int fd)
{
	unsigned char	*header;
	int				size;

	header = ft_calloc(14, sizeof(unsigned char));
	if (!header)
		exit_program("Errore nel malloc", core);
	size = 54 + (core->cam->img.bits_per_pixel / 8 * core->image_width
			+ padding_round) * core->image_height;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
	free((char **)header);
}

void	create_file_info(t_global *core, int fd)
{
	unsigned char	*info;

	info = ft_calloc(40, sizeof(unsigned char));
	if (!info)
		exit_program("Errore nel malloc", core);
	info[0] = (unsigned char)(40);
	info[4] = (unsigned char)(core->image_width);
	info[5] = (unsigned char)(core->image_width >> 8);
	info[6] = (unsigned char)(core->image_width >> 16);
	info[7] = (unsigned char)(core->image_width >> 24);
	info[8] = (unsigned char)(core->image_height);
	info[9] = (unsigned char)(core->image_height >> 8);
	info[10] = (unsigned char)(core->image_height >> 16);
	info[11] = (unsigned char)(core->image_height >> 24);
	info[12] = (unsigned char)(1);
	info[14] = (unsigned char)(core->cam->img.bits_per_pixel);
	write(fd, info, 40);
	free((char **)info);
}

void	create_screeshot(t_global *core, char *file)
{
	int					hold_y;
	int					padding_round;
	int					fd;
	unsigned char		padding[3];

	hold_y = core->image_height;
	ft_bzero(padding, 3);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!fd)
		exit_program("Errore nella creazione del file bmp", core);
	padding_round = (core->image_width * 3) % 4;
	create_file_header(core, padding_round, fd);
	create_file_info(core, fd);
	while (hold_y >= 0)
	{
		write(fd, core->cam->img.addr + (hold_y * core->image_width
			* core->cam->img.bits_per_pixel / 8), core->cam->img.line_length);
		write(fd, padding, padding_round);
		hold_y--;
	}
	close(fd);
}
