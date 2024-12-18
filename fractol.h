/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:24:57 by armirono          #+#    #+#             */
/*   Updated: 2024/12/17 13:13:51 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./mlx/include/MLX42/MLX42.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
//#include "mlx/mlx.h"

// window size

# define WIDTH 800
# define HEIGHT 800

// Colors

# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define MAGENTA_BURST 0xFF00FFFF
# define LIME_SHOCK 0xCCFF00FF
# define NEON_ORANGE 0xFF6600FF
# define PSYCHEDELIC_PURPLE 0x660066FF
# define AQUA_DREAM 0x33CCCCFF
# define HOT_PINK 0xFF66B2FF
# define ELECTRIC_BLUE 0x0066FFFF
# define LAVA_RED 0xFF3300FF

// Complex numbers
typedef struct s_complex
{
	double			real;
	double			imgnr;
}					t_complex;

// Image (MLX42)
typedef struct s_img
{
	mlx_image_t		*img_ptr;
	uint32_t		width;
	uint32_t		height;
}					t_img;

typedef struct s_color_scheme
{
	int				type;
	double			r_mult;
	double			b_mult;
	double			g_mult;
}					t_color_scheme;

// Fractal (updated for MLX42)

typedef struct s_fractal
{
	char			*name;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_color_scheme	color_scheme;
	double			escape_value;
	int				itrtn_def;
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	double			zoom;
	double			shift_x;
	double			shift_y;
	double			julia_real;
	double			julia_imaginary;
}					t_fractal;

// Fractal actions

void				close_handler(void *param);
void				fractal_init(t_fractal *fractal);
void				fractal_render(t_fractal *fractal);
int					logarithmic_color(int iterations, int max_iter);

// string util

double				a2double(char *str);
void				error_msg(char *msg);

// math

double				map(double unscaled_num, double new_min, double new_max,
						double old_max);
t_complex			sum_complex(t_complex z1, t_complex z2);
t_complex			square_complex(t_complex z);
t_complex			calculate_z(t_complex z, t_complex c, t_fractal *fractal);

// Events

void				key_handler(mlx_key_data_t keydata, void *param);
void				scroll_handler(double xdelta, double ydelta, void *param);
void				julia_track(void *param);
double				get_ms_cmplx_crd(t_fractal *f, double mous_coord, int is_x);
int					get_scape_clr(int iterations, int max_iter,
						t_color_scheme color_scheme);
void				handle_color_key(mlx_key_data_t keydata,
						t_fractal *fractal);

#endif
