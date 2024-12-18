# 42-Cursus-Rank02-Fract-ol
Fract-ol for 125% as of December 2024.

Requires: cmake, glfw (installed with brew - thus you need brew too. 42 adapted homebrew exists) 

Inspired by https://github.com/suspectedoceano/mlx and his other video on fractol itself (he wrote on linux VM'd on a macbook). 
My minilibx from a .tgz refused to untar properly, so i ended up using MLX42 from Codam. Same essense but completely different function calls \ return types. 

Upside of MLX42 is it's somewhat maintained, downside for someone who might be reading this a year or two later - MLX42 might evolve away from working with my code directly, you might have to update the code accordingly. 
"1-click" making - depends on your glfw exact location, even if MLX42 pull is successful, making might fail if glfw directory in the -L"" in MLX_FLAGS is not correct for your glfw path. We in Quebec had an accidential system reset in spring 2024 after which everyone had to reinstall everything from scratch, and install paths that were harmonized became very individual. Lesson - back up your work (i did).
In color.c i made only 3 coloring schemes (schemes, not colors), you can add more psychedelic ones. i might too if\when i return to this.
