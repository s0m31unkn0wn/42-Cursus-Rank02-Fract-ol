/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:07:25 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 14:10:04 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_color_key(mlx_key_data_t keydata, t_fractal *fractal)
{
	if (keydata.key == MLX_KEY_1)
		fractal->color_scheme.type = 1;
	else if (keydata.key == MLX_KEY_2)
		fractal->color_scheme.type = 2;
	else if (keydata.key == MLX_KEY_3)
		fractal->color_scheme.type = 3;
	else
		return ;
}

static int	sine_wave_color_mapping(int iterations, int max_iterations)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations == max_iterations)
		return (BLACK);
	t = (double)iterations / max_iterations;
	r = (int)(sin(M_PI * t) * 127 + 128);
	g = (int)(sin(M_PI * t + 2.0) * 127 + 128);
	b = (int)(sin(M_PI * t + 4.0) * 127 + 128);
	return ((r << 16) | (g << 8) | b);
}

static int	linear_color_mapping(int iterations, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations == max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	logarithmic_color(int iterations, int max_iter)
{
	double	log_zn;
	double	nu;
	double	t;
	int		c[3];

	if (iterations == max_iter)
		return (BLACK);
	log_zn = log(iterations);
	nu = log(log_zn / log(2)) / log(2);
	t = iterations + 1 - nu;
	c[0] = (int)(sin(0.016 * t + 0) * 127 + 128);
	c[1] = (int)(sin(0.016 * t + 2) * 127 + 128);
	c[2] = (int)(sin(0.016 * t + 4) * 127 + 128);
	return ((c[0] << 16) | (c[1] << 8) | c[2]);
}

int	get_scape_clr(int iterations, int max_iter, t_color_scheme color_scheme)
{
	if (iterations == max_iter)
		return (BLACK);
	if (color_scheme.type == 1)
		return (linear_color_mapping(iterations, max_iter));
	else if (color_scheme.type == 2)
		return (logarithmic_color(iterations, max_iter));
	else if (color_scheme.type == 3)
		return (sine_wave_color_mapping(iterations, max_iter));
	else
		return (linear_color_mapping(iterations, max_iter));
}
