/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:52:27 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 13:22:20 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled, double new_min, double new_max, double old_max)
{
	return ((((new_max - new_min) * unscaled) / old_max) + new_min);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.imgnr * z.imgnr);
	result.imgnr = 2 * z.real * z.imgnr;
	return (result);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real + z2.real;
	result.imgnr = z1.imgnr + z2.imgnr;
	return (result);
}
