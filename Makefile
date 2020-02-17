APP_NAME = ush

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
ADDITIONAl_FLAGS =

DIR_NAME = ush

SRCD = src
INCD = inc
OBJD = obj

LIBMXD = libmx
LIBMXA := $(LIBMXD)/libmx.a
LIBMXI := $(LIBMXD)/inc

INC = ush.h
INCS = $(addprefix $(INCD)/, $(INC))

CORE_SRCS = ush_loop.c proccess_commands_list.c traverse_and_execute_tree.c \
			execute.c launch.c

CLEARING_SRCS = clear_tokens.c clear_trees.c

UTILS_SRCS = print_tree.c split_token.c create_trees.c split_cmd.c

BUILTINS_SRCS = builtins.c

CORE = $(addprefix core/, $(CORE_SRCS))
CLEARING = $(addprefix clearing/, $(CLEARING_SRCS))
UTILS = $(addprefix utils/, $(UTILS_SRCS))
BUILTINS = $(addprefix builtins/, $(BUILTINS_SRCS))

SRC = main.c $(CORE) $(CLEARING) $(UTILS) $(BUILTINS)

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = main.o $(CORE_SRCS:%.c=%.o) $(CLEARING_SRCS:%.c=%.o) \
	   $(UTILS_SRCS:%.c=%.o) $(BUILTINS_SRCS:%.c=%.o)

all: install

install: $(LIBMXA) $(APP_NAME)

$(APP_NAME): $(SRCS) $(INCD)/$(INC) $(LIBMXA)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $(SRCS) -I $(INCD) -I $(LIBMXI)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) $(OBJS) $(LIBMXA) -o $(APP_NAME)
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
