/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:39:38 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 13:13:04 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	if ((argc == 2 && (ft_strcmp(argv[1], "mandelbrot") == 0
				|| ft_strcmp(argv[1], "burning_ship") == 0)) || (argc == 4
			&& ft_strcmp(argv[1], "julia") == 0))
	{
		fractal.name = argv[1];
		if (ft_strncmp(fractal.name, "julia", 5) == 0)
		{
			fractal.julia_real = a2double(argv[2]);
			fractal.julia_imaginary = a2double(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx);
	}
	else
		error_msg("Usage: mandelbrot | julia j.real j.imagin | burning_ship\n");
	return (0);
}
