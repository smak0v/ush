APP_NAME = ush

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
ADDITIONAl_FLAGS = -g -ltermcap

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
			execute.c launch.c get_input.c init_ush.c history.c input_mode.c \
			execute_piped.c signals.c

CLEARING_SRCS = clear_tokens.c clear_trees.c

UTILS_SRCS = print_tree.c split_token.c create_trees.c split_cmd.c \
			 mx_printnbr.c create_env_list.c errors.c set_defaults.c \
			 process_home.c

BUILTINS_SRCS = builtins.c builtins2.c parse_flags.c parse_args.c \
				validation.c cd.c mixed_errors.c

ENV_SRCS = env.c env_errors.c parse_env.c

CORE = $(addprefix core/, $(CORE_SRCS))
CLEARING = $(addprefix clearing/, $(CLEARING_SRCS))
UTILS = $(addprefix utils/, $(UTILS_SRCS))
BUILTINS = $(addprefix builtins/, $(BUILTINS_SRCS))
ENV = $(addprefix builtins/env/, $(ENV_SRCS))

SRC = main.c $(CORE) $(CLEARING) $(UTILS) $(BUILTINS) $(ENV)

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = main.o $(CORE_SRCS:%.c=%.o) $(CLEARING_SRCS:%.c=%.o) \
	   $(UTILS_SRCS:%.c=%.o) $(BUILTINS_SRCS:%.c=%.o) $(ENV_SRCS:%.c=%.o)

all: install

install: $(LIBMXA) $(APP_NAME)

$(APP_NAME): $(SRCS) $(INCD)/$(INC) $(LIBMXA)
	@$(CC) $(CFLAGS) -c $(SRCS) -I $(INCD) -I $(LIBMXI)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) $(OBJS) $(LIBMXA) -o $(APP_NAME)
	@mkdir -p $(OBJD)
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
