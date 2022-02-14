NAME = containers
NAME_STD = std

SRCS_DIR = ./
SRCS =	main.cpp \
		vectorTest.cpp

FLAGS = -std=c++98 -Wall -Wextra -Werror

OBJS_DIR 	= 	obj/
OBJ 		= 	$(SRCS:.cpp=.o)
OBJS 		= 	$(addprefix $(OBJS_DIR), $(OBJ))

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@clang++ $(FLAGS) -c $< -o $@

OBJS_DIR_STD 	= 	obj_std/
OBJ_STD 		= 	$(SRCS:.cpp=.o)
OBJS_STD 		= 	$(addprefix $(OBJS_DIR_STD), $(OBJ_STD))

$(OBJS_DIR_STD)%.o :	$(SRCS_DIR_STD)%.cpp
	@mkdir -p $(OBJS_DIR_STD)
	@echo "Compiling: $<"
	@clang++ $(FLAGS) -c $< -o $@ -D USE_STD

$(NAME): $(OBJS)
	@echo "Creating $(NAME)"
	@clang++ $(FLAGS) -o $(NAME) $(OBJS)

$(NAME_STD): $(OBJS_STD)
	@echo "Creating $(NAME_STD)"
	@clang++ $(FLAGS) -o $(NAME_STD) $(OBJS_STD)

all: $(NAME) $(NAME_STD)

clean:
	@echo "Deleting $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)
	@echo "Deleting $(OBJS_DIR_STD)"
	@rm -rf $(OBJS_DIR_STD)

fclean: clean
	@echo "Deleting $(NAME)"
	@rm -f $(NAME)
	@echo "Deleting $(NAME_STD)"
	@rm -f $(NAME_STD)

re: fclean all