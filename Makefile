######################### -*- Mode: Makefile-Gmake -*- ########################
## 
## Filename: Makefile
## Description: 
## Author: Lunacie
## Created: Thu Jan 16 02:42:39 2014 (+0100)
## Last-Updated: 
##           By: 
##     Update #: 0
## 
######################################################################
## 
### Change Log:
## 
## 
## 
######################################################################

NAME		=		world

BIN_PATH	=		bin/

NAME_PATH	=		$(BIN_PATH)$(NAME)

SRCS		=		main.c						\
				debugHandling.c					\
				time.c						\
				getFile.c					\
										\
				engines.c					\
				gameEngine.c					\
				event_handling.c				\
										\
				graphicEngine.c					\
				initScreen.c					\
				camera.c					\
				frustrum.c					\
				vector.c					\
				getObj.c					\
				draw/draw.c					\
				draw/draw_primitives.c				\
				draw/draw_obj.c					\
				draw/transform.c				\
				draw/draw_model.c				\
				draw/draw_background.c				\
				draw/draw_camera.c				\
				draw/primitives/drawCube_primitive.c		\
				draw/map/map.c					\
				draw/map/chunk.c				\
				draw/map/cube.c					\
				draw/map/voxel.c				\
										\
				material/getMaterial.c				\
				material/textureMap.c				\
				material/tga.c					\
										\
				map/map.c					\
										\
				mapBuilderEngine.c				\
				mapBuilder/selectElementFromMap.c		\


OBJS		=		$(SRCS:%.c=objs/%.o)

SRCS_DIR	=		srcs/

CFLAGS		=		-W -Wall -Wextra -pedantic -ansi

INCLUDES	=		$(addprefix -I./, $(shell find includes/ -type d)) -I/usr/include  -I./libs/includes

LDFLAGS		=		-lSDL -lGL -lGLU  -L./libs/  -llncstring -llnclist -llncerror -lm

CC		=		gcc

SRC_DIR		=		$(shell find srcs/ -type d)
OBJ_DIR		=		$(subst srcs/, objs/, $(SRC_DIR))

ERROR_FILE	=		.temp.errors
WARN_FILE	=		.warn.tmp
LOG_FILE	=		.temp.log

all		:		$(NAME_PATH)

objs/%.o	:		$(SRCS_DIR)%.c
				@$(foreach dir, $(OBJ_DIR), if test -e $(dir); then true; else mkdir $(dir); fi;)
				@$(CC) -c  $< -o $@ $(CXXFLAGS) $(INCLUDES) 2>> $(LOG_FILE) || touch $(ERROR_FILE)
				@if test -e $(ERROR_FILE); then  echo -n "$(ERROR)" ;elif test -s $(LOG_FILE);then echo -n  "$(WARN)" && touch $(WARN_FILE) ;else echo -n "$(OK)"; fi;
				@echo "\033[5G" Compiling $<  "\033[70G" "->  " $@
				@if test -e $(ERROR_FILE); then cat $(LOG_FILE);elif test -s $(LOG_FILE);then cat $(LOG_FILE); fi;
				@rm -rf $(ERROR_FILE) $(LOG_FILE)


$(NAME_PATH)	:		$(OBJS)
				@make --no-print-directory ./libs/strings
				@make --no-print-directory ./libs/list
				@make --no-print-directory ./libs/handle_error
				@if test -e ./bin ;then test  -e; else mkdir bin;fi;
				@$(CC)  -o $(NAME_PATH) $(OBJS) $(LDFLAGS) 2> $(LOG_FILE) || touch $(ERROR_FILE)
				@if test -e $(ERROR_FILE); then  echo  "\n$(FAILED) " ;elif test -e $(WARN_FILE); then echo "$(WARNINGS)";else echo -n; fi;
				@if test -e $(ERROR_FILE); then cat $(LOG_FILE); else\
				echo "\n$(OK)  $(YELLOW)" "Linking : \033[20G Objects\033[35G ->   $(OBJS)";\
				echo "\033[20G Libraries \033[35G ->   $(LDFLAGS)";\
				echo "\n$(OK)  \033[5GCompilation complete using \033[35G  :   $(CC)";\
				echo "\t -> Executable location \033[35G  :  " "$(BIN_PATH)$(OK_COLOR)$(NAME)$(NO_COLOR)"; fi;
				@rm -rf $(ERROR_FILE) $(LOG_FILE) $(WARN_FILE)


clean		:
				@rm -rf $(OBJS)
				@echo "$(OK) $(YELLOW)" Deleting objects

fclean		:		clean
				@echo "$(OK) $(YELLOW)" "Deleting executable -> $(NAME_PATH)\n"
				@rm -rf $(NAME_PATH)

re		:		fclean all





## ==

YELLOW		=		\033[5G
NO_COLOR	=		\033[0m
OK_COLOR	=		\033[32;01m
ERROR_COLOR	=		\033[31;01m
WARN_COLOR	=		\033[33;01m

OK		=		$(OK_COLOR)[x]$(NO_COLOR)
ERROR		=		$(ERROR_COLOR)[ ]$(NO_COLOR)
WARN		=		$(WARN_COLOR)[W]$(NO_COLOR)
FAILED		=		$(ERROR_COLOR)[Compilation Failed]$(NO_COLOR)
WARNINGS	=		$(WARN_COLOR)\n[There are warnings left]\n$(NO_COLOR)
