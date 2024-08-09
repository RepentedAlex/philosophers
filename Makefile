########################
## COMPILER AND FLAGS ##
########################

CC			=	gcc
FFLAGS		=	-fsanitize=address
IFLAGS		=	-Iinclude
LFLAGS		=
WFLAGS		=	-Wall -Wextra -Werror -g3
CFLAGS		=	$(WFLAGS) $(IFLAGS)
#CFLAGS		+=	$(FFLAGS)
CFLAGS		+=	-MMD -MP

#################
## DIRECTORIES ##
#################

SRC_DIR	=	src/
BLD_DIR	=	build/

###########
## FILES ##
###########

NAME		=	philo
SRC_FILES	=	philosophers \
				initialisation \
				utils \
				utils_2
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(BLD_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

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

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$@ linked successfully! :D$(RESET)"

$(BLD_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(BLUE)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

$(OBJF):
	@mkdir -p $(BLD_DIR)
	@mkdir -p $(addprefix $(BLD_DIR), $(dir $(SRC_FILES)))
	@touch $(OBJF)
	@echo "$(YELLOW)Object directory created!$(RESET)"

clean:
	@rm -rf $(BLD_DIR) $(OBJF)
	@echo "$(MAGENTA)Build files cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(MAGENTA)$(NAME) cleaned!$(RESET)"

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: all bonus clean fclean re