GREEN = \033[0;32m
RESET = \033[0m

NAME = myapp

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=address

SRCS = main.c
#routine.c monitor.c utils.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
		@echo "Compilating..."
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "Successfully compiled 🚀"

%.o: %.c philo.h
		@echo "Generating the objects..."
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "Objects successfully generated 👌"

clean:

		@rm -f $(OBJS)
		@echo "Deleted objects...🚮"

fclean: clean
		@rm -f $(NAME)
		@echo "Deleted objects and executable...🗑️​"

re: fclean all
		@printf "$(GREEN)Making the world green again.$(RESET) ♻️​​"

.PHONY: all clean fclean re