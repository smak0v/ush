APP_NAME = ush

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
CC = clang

DIR_NAME = ush

SRCD = src
INCD = inc
OBJD = obj

LIBMXD = libmx
LIBMXA := $(LIBMXD)/libmx.a
LIBMXI := $(LIBMXD)/inc

INC = ush.h
INCS = $(addprefix $(INCD)/, $(INC))

SRC = \
main.c \
ush_loop.c \
split_line.c \
execute.c \
launch.c \
clear_history.c \
builtins.c \
create_trees.c \
split_token.c \

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(LIBMXA) $(APP_NAME)

$(APP_NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L $(LIBMXD) -lmx -o $@
	@printf "\r\33[2K$@\t\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCD) -I$(LIBMXI)
	@printf "\r\33[2K$(APP_NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%)"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LIBMXA):
	@make -sC $(LIBMXD)

clean:
	@make -sC $(LIBMXD) $@
	@rm -rf $(OBJD)
	@printf "$(DIR_NAME)/$(OBJD)\t\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(APP_NAME)
	@printf "$(APP_NAME)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install
