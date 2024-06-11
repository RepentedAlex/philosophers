########################
## COMPILER AND FLAGS ##
########################

CC			=	gcc
FFLAGS		=	-fsanitize=address
IFLAGS		=	-Iinclude
LFLAGS		=
WFLAGS		=	-Wall -Wextra -Werror
CFLAGS		= $(WFLAGS) $(IFLAGS) $(FFLAGS)

#################
## DIRECTORIES ##
#################

SRC_DIR	=	src/
BLD_DIR	=	build/

###########
## FILES ##
###########

NAME		=	philo
SRC_FILES	=	philosophers
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))

############
## COLORS ##
############

RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA		=	\033[1;35m
CYAN		=	\033[1;36m
RESET		=	\033[0m

#############
## RECIPES ##
#############

all: $(NAME)

$(NAME):
	@echo -e "$(BLUE)Linking $@$(RESET)"

clean:

fclean:

re: fclean all

.PHONY: all bonus clean fclean re