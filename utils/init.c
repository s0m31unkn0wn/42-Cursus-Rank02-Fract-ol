/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:19:18 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 14:15:41 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	close_handler(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	mlx_delete_image(fractal->mlx, fractal->img);
	mlx_terminate(fractal->mlx);
	ft_putstr_fd("Gracefully exiting fractol\n", 1);
	exit(EXIT_SUCCESS);
}

static void	data_init(t_fractal *fractal)
{
	fractal->x_min = -2.0;
	fractal->x_max = 2.0;
	fractal->y_min = -2.0;
	fractal->y_max = 2.0;
	fractal->escape_value = 4.0;
	fractal->itrtn_def = 142;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->color_scheme.type = 1;
	fractal->color_scheme.r_mult = 1.0;
	fractal->color_scheme.g_mult = 1.0;
	fractal->color_scheme.b_mult = 1.0;
}

void	julia_track_wrapper(double x, double y, void *param)
{
	t_fractal	*fractal;
	int32_t		mouse_x;
	int32_t		mouse_y;

	fractal = param;
	mouse_x = (int32_t)round(x);
	mouse_y = (int32_t)round(y);
	julia_track(param);
}

static void	events_init(t_fractal *fractal)
{
	mlx_key_hook(fractal->mlx, key_handler, fractal);
	mlx_scroll_hook(fractal->mlx, scroll_handler, fractal);
	mlx_cursor_hook(fractal->mlx, julia_track_wrapper, fractal);
	mlx_close_hook(fractal->mlx, close_handler, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx = mlx_init(WIDTH, HEIGHT, fractal->name, false);
	if (!fractal->mlx)
		error_msg("Error: mlx_init failed");
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		mlx_terminate(fractal->mlx);
		error_msg("Error: mlx_new_image failed");
	}
	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
	events_init(fractal);
	data_init(fractal);
}
