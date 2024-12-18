NAME = pipex

LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a

SOURCE_DIR = ./src
OBJECTS_DIR = ./obj
BONUS_SOURCE_DIR = ./src_bonus
BONUS_OBJECTS_DIR = ./obj_bonus

SOURCES = pipex.c \
		  pipex_utils.c 	

BONUS_SOURCES = pipex_bonus.c \
				pipex_utils_bonus.c

OBJECTS = $(addprefix $(OBJECTS_DIR)/, ${SOURCES:.c=.o})
BONUS_OBJECTS = $(addprefix $(BONUS_OBJECTS_DIR)/, ${BONUS_SOURCES:.c=.o})

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all : $(NAME)

$(LIBFT_A):
	make -C$(LIBFT) && printf "Compiling $(LIBFT_A)\n"

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

$(BONUS_OBJECTS_DIR):
	mkdir -p $(BONUS_OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

$(BONUS_OBJECTS_DIR)/%.o: $(BONUS_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

$(NAME): $(OBJECTS_DIR) $(OBJECTS) $(LIBFT_A)
		$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_A) -o $(NAME) && printf "Compiled $(NAME)\n"

clean:
		rm -rf $(OBJECTS_DIR)
		rm -rf $(BONUS_OBJECTS_DIR)
		make -C $(LIBFT) clean

fclean:	clean
		rm -rf $(NAME)
		make -C $(LIBFT) fclean

re:		fclean all

bonus:	$(BONUS_OBJECTS_DIR) $(BONUS_OBJECTS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(BONUS_OBJECTS) $(LIBFT_A) -o $(NAME) && printf "Compiled $(NAME) with bonus\n"
