#################
## COMPILATION ##
#################

$NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
DFLAGS	=	-MMD -MP
FFLAGS	=	-fsanitize=address
IFLAGS	=	-Iinclude
LFLAGS	=
DEBUG	=	-g3
FLAGS	=	$(CFLAGS) $(DFLAGS) $(IFLAGS)
FLAGS	+=	$(DEBUG)

#################
## DIRECTORIES ##
#################

$BLD_DIR	=	build/
$EXA_DIR	=	examples/
$EXT_DIR	=	external/
$XTR_DIR	=	extras/
$INC_DIR	=	include/
$LIB_DIR	=	libs/
$SRC_DIR	=	src/
$TES_DIR	=	tests/

#############
## SOURCES ##
#############

$EXA_FILES	=
$SRC_FILES	=	philo
$TST_FILES	=

########################
## INTERMEDIARY FILES ##
########################

SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
BLD		=	$(addprefix $(BLD_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF	=	.cache_exists

#############
## RECIPES ##
#############

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BLD_DIR)%.o:	$(SRC_DIR)%.c | $(OBJF)
	$(CC) $(CFLAGS) -c <$ -o $@

$(OBJF):
	mkdir -p $(BLD_DIR)
	mkdir -p $(addprefix $(BLD_DIR), $(dir $(SRC_FILES)))
	touch $(OBJF)
