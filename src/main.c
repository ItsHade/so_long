/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:27:42 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/18 15:27:42 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_exit(t_parameters *par)
{
	mlx_destroy_image(par->mlx, par->txt.floor);
	mlx_destroy_image(par->mlx, par->txt.player);
	mlx_destroy_image(par->mlx, par->txt.player1);
	mlx_destroy_image(par->mlx, par->txt.wall);
	mlx_destroy_image(par->mlx, par->txt.exit);
	mlx_destroy_image(par->mlx, par->txt.end);
	mlx_destroy_image(par->mlx, par->txt.col1);
	mlx_destroy_image(par->mlx, par->txt.col2);
	mlx_destroy_image(par->mlx, par->txt.monster);
	mlx_destroy_image(par->mlx, par->txt.img);
	mlx_destroy_window(par->mlx, par->win);
	mlx_destroy_display(par->mlx);
	free(par->mlx);
	ft_freemap(par->data);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_parameters	par;

	if (ft_check_args(argc, argv, &par.data) == -1)
		return (0);
	ft_initialize(&par, argv[1]);
	par.mlx = mlx_init();
	par.win = mlx_new_window(par.mlx, par.width, par.height + TILE, "so_long");
	par.playerposx = par.data.cellp_y;
	par.playerposy = par.data.cellp_x;
	ft_initialize_textures(&par);
	ft_render_map(&par);
	ft_display_text(&par);
	mlx_put_image_to_window(par.mlx, par.win, par.txt.player,
		par.playerposx * TILE, par.playerposy * TILE);
	mlx_loop_hook(par.mlx, NULL, NULL);
	mlx_hook(par.win, 17, 0, ft_exit, &par);
	mlx_hook(par.win, 2, 1L << 0, ft_keyboard_hook, &par);
	mlx_loop(par.mlx);
	ft_exit (&par);
}
