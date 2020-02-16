APP_NAME = ush

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
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

CLEARING_SRCS = clear_tokens.c

UTILS_SRCS = print_tree.c split_token.c

CLEARING = $(addprefix clearing/, $(CLEARING_SRCS))
UTILS = $(addprefix utils/, $(UTILS_SRCS))

SOURCES = \
main.c \
ush_loop.c \
execute.c \
launch.c \
builtins.c \
create_trees.c

SRC = $(SOURCES) $(CLEARING) $(UTILS)

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(SOURCES:%.c=%.o) $(CLEARING_SRCS:%.c=%.o) $(UTILS_SRCS:%.c=%.o)

all: install

install: $(LIBMXA) $(APP_NAME)

$(APP_NAME): $(SRCS) $(INCD)/$(INC) $(LIBMXA)
	@$(CC) $(CFLAGS) -c $(SRCS) -I $(INCD) -I $(LIBMXI)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBMXA) -o $(APP_NAME)
	@mkdir $(OBJD)
	@mv $(OBJS) $(OBJD)
	@printf "\r\33[2K$@\t\t   \033[32;1mcreated\033[0m\n"

$(LIBMXA):
	@make -sC $(LIBMXD)

clean:
	@make -sC $(LIBMXD) $@
	@rm -rf $(OBJD)
	@printf "$(DIR_NAME)/$(OBJD)\t\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@make -sC $(LIBMXD) $@
	@rm -rf $(APP_NAME)
	@printf "$(APP_NAME)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install
