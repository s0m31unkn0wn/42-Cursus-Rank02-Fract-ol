NAME = fractol

#libft
LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a

#MLX42 pull and build
MLX_NAME = MLX42
MLX_GIT = https://github.com/codam-coding-college/MLX42.git
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
#MLX_ARCHIVE = minilibx_opengl.tgz

SOURCE_DIR_UTILS = ./utils
OBJECTS_DIR = ./obj

SOURCES_UTILS = $(wildcard $(SOURCE_DIR_UTILS)/*.c)
SOURCES_MAIN = main.c

OBJECTS = $(patsubst ./utils/%.c,$(OBJECTS_DIR)/utils/%.o,$(SOURCES_UTILS)) \
          $(OBJECTS_DIR)/main.o


# glfw installation directory might be different, substitute -L"/Users/$(USER)/.brew/opt/glfw/lib/" for yours 


CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I. -I./libft -I$(MLX_DIR)/include
#MLX_FLAGS_TAR = -L$(MLX_DIR) -lmlx -lXext -lX11 -framework OpenGL -framework AppKit
MLX_FLAGS_PULLED = $(MLX_LIB) -Imlx/include -lglfw -L"/Users/$(USER)/.brew/Cellar/glfw/3.4/lib" -framework Cocoa -framework OpenGL -framework IOKit

all: $(LIBFT_A) $(MLX_LIB) $(NAME)

$(LIBFT_A):
	make -C$(LIBFT) && printf "Compiled $(LIBFT_A)\n"

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)
	mkdir -p $(OBJECTS_DIR)/utils

$(MLX_DIR):

#@mkdir -p $(MLX_DIR)
#@tar -xzvf $(MLX_ARCHIVE)
#@ls -la
	git clone $(MLX_GIT) $(MLX_DIR)


$(MLX_LIB): $(MLX_DIR)
#@echo "Building MLX..."
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4 || (echo "MLX42 build failed" && exit 1)

$(OBJECTS_DIR)/utils/%.o: ./utils/%.c | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJECTS_DIR)/%.o: %.c | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

#final linking
$(NAME): $(OBJECTS) $(LIBFT_A) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_A) $(MLX_FLAGS_PULLED)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJECTS_DIR)
	@rm -rf $(MLX_DIR)/build
	make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX_DIR)
	@rm -rf $(MLX_TAR)
	@rm -rf minilibx_opengl_20191021.tgz
	make -C $(LIBFT) fclean

re: fclean all