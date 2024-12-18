/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:29:23 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 13:33:31 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_handler(fractal);
	if (keydata.key == MLX_KEY_LEFT)
		fractal->shift_x -= (0.5 / fractal->zoom);
	else if (keydata.key == MLX_KEY_RIGHT)
		fractal->shift_x += (0.5 / fractal->zoom);
	else if (keydata.key == MLX_KEY_UP)
		fractal->shift_y += (0.5 / fractal->zoom);
	else if (keydata.key == MLX_KEY_DOWN)
		fractal->shift_y -= (0.5 / fractal->zoom);
	else if (keydata.key == MLX_KEY_EQUAL)
		fractal->itrtn_def += 10;
	else if (keydata.key == MLX_KEY_MINUS)
		fractal->itrtn_def -= 10;
	else if (keydata.key == MLX_KEY_1 || keydata.key == MLX_KEY_2
		|| keydata.key == MLX_KEY_3)
		handle_color_key(keydata, fractal);
	fractal_render(fractal);
}

void	apply_zoom(t_fractal *fractal, double mouse_x, double mouse_y,
		double zoom_fact)
{
	double	mouse_x_cmpl;
	double	mouse_y_cmpl;
	double	range_x;
	double	range_y;

	mouse_x_cmpl = get_ms_cmplx_crd(fractal, mouse_x, 1);
	mouse_y_cmpl = get_ms_cmplx_crd(fractal, mouse_y, 0);
	range_x = fractal->x_max - fractal->x_min;
	range_y = fractal->y_max - fractal->y_min;
	fractal->x_min = mouse_x_cmpl - (mouse_x_cmpl - fractal->x_min) * zoom_fact;
	fractal->x_max = mouse_x_cmpl + (fractal->x_max - mouse_x_cmpl) * zoom_fact;
	fractal->y_min = mouse_y_cmpl - (mouse_y_cmpl - fractal->y_min) * zoom_fact;
	fractal->y_max = mouse_y_cmpl + (fractal->y_max - mouse_y_cmpl) * zoom_fact;
	fractal_render(fractal);
}

void	scroll_handler(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;
	int32_t		mouse_x;
	int32_t		mouse_y;
	double		zoom_fact;

	fractal = param;
	mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
	if (ydelta > 0)
		zoom_fact = 0.95;
	else if (ydelta < 0)
		zoom_fact = 1.05;
	else
		return ;
	xdelta += 0;
	apply_zoom(fractal, mouse_x, mouse_y, zoom_fact);
}

void	julia_track(void *param)
{
	t_fractal	*fractal;
	double		new_julia_x;
	double		new_julia_y;
	int32_t		x;
	int32_t		y;

	fractal = param;
	mlx_get_mouse_pos(fractal->mlx, &x, &y);
	new_julia_x = get_ms_cmplx_crd(fractal, x, 1);
	new_julia_y = get_ms_cmplx_crd(fractal, y, 0);
	if (!ft_strcmp(fractal->name, "julia"))
	{
		fractal->julia_real = (map(x, -2, +2, WIDTH) * fractal->zoom)
			+ fractal->shift_x;
		fractal->julia_imaginary = (map(y, +2, -2, HEIGHT) * fractal->zoom)
			+ fractal->shift_y;
		fractal_render(fractal);
	}
}
