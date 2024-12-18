/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:43:52 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 13:14:44 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

t_complex	calculate_z(t_complex z, t_complex c, t_fractal *fractal)
{
	if (ft_strcmp(fractal->name, "burning_ship") == 0)
	{
		z.real = fabs(z.real);
		z.imgnr = -fabs(z.imgnr);
	}
	return (sum_complex(square_complex(z), c));
}

static t_complex	get_complex_point(int x, int y, t_fractal *frctl)
{
	t_complex	point;

	point.real = (map(x, frctl->x_min, frctl->x_max, WIDTH) * frctl->zoom)
		+ frctl->shift_x;
	point.imgnr = (map(y, frctl->y_max, frctl->y_min, HEIGHT) * frctl->zoom)
		+ frctl->shift_y;
	return (point);
}

static void	handle_pixel(int x, int y, t_fractal *frctl)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	z = get_complex_point(x, y, frctl);
	if (ft_strcmp(frctl->name, "julia") == 0)
	{
		c.real = frctl->julia_real;
		c.imgnr = frctl->julia_imaginary;
	}
	else
		c = z;
	while (i < frctl->itrtn_def)
	{
		z = calculate_z(z, c, frctl);
		if ((z.real * z.real) + (z.imgnr * z.imgnr) > frctl->escape_value)
		{
			mlx_put_pixel(frctl->img, x, y, get_scape_clr(i, frctl->itrtn_def,
					frctl->color_scheme));
			return ;
		}
		++i;
	}
	mlx_put_pixel(frctl->img, x, y, WHITE);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)fractal->img->height)
	{
		x = 0;
		while (x < (int)fractal->img->width)
		{
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
}
