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
			init_ush.c input_mode.c signals.c

INPUT_SRCS = get_input.c history.c expansions.c tilde_exp.c dollar_exp.c

UTILS_SRCS = build_pwd_string.c getenv.c set_defaults.c \
			 check_identifier_validity.c mx_printnbr.c \
			 setup_underscore_env_var.c create_tmp_env.c \
			 overwrite_strarr_value.c split_key_value.c \
			 create_trees.c print_tree.c ush_errors.c \
			 errors.c process_home.c

CLEARING_SRCS = clear_tokens.c clear_trees.c clear_processes_data.c

BUILTINS_SRCS = builtins.c builtins2.c parse_flags.c parse_args.c \
				validation.c mixed_errors.c unset.c exit.c

ENV_SRCS = env.c env_errors.c parse_env.c janitor.c

EXPORT_SRCS = export.c process_duplicates.c

WHICH_SRCS = which.c

CD_SRCS = cd.c

PARSING_SRCS = proccess_escapings.c split_cmd.c split_token.c

JOB_CTRL_SYSTEM_SRCS = jobs.c processes.c launch_job.c launch_proccess.c

CORE = $(addprefix core/, $(CORE_SRCS))
INPUT = $(addprefix input/, $(INPUT_SRCS))
PARSING = $(addprefix parsing/, $(PARSING_SRCS))
CLEARING = $(addprefix clearing/, $(CLEARING_SRCS))
UTILS = $(addprefix utils/, $(UTILS_SRCS))
BUILTINS = $(addprefix builtins/, $(BUILTINS_SRCS))
ENV = $(addprefix builtins/env/, $(ENV_SRCS))
EXPORT = $(addprefix builtins/export/, $(EXPORT_SRCS))
WHICH = $(addprefix builtins/which/, $(WHICH_SRCS))
CD = $(addprefix builtins/cd/, $(CD_SRCS))

JOB_CTRL_SYSTEM = $(addprefix job_control_system/, $(JOB_CTRL_SYSTEM_SRCS))

SRC = main.c $(CORE) $(CLEARING) $(UTILS) $(BUILTINS) $(ENV) $(EXPORT) \
	  $(WHICH) $(CD) $(JOB_CTRL_SYSTEM) $(PARSING) $(INPUT)

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = main.o $(CORE_SRCS:%.c=%.o) $(CLEARING_SRCS:%.c=%.o) \
	   $(UTILS_SRCS:%.c=%.o) $(BUILTINS_SRCS:%.c=%.o) $(ENV_SRCS:%.c=%.o) \
	   $(EXPORT_SRCS:%.c=%.o) $(WHICH_SRCS:%.c=%.o) $(CD_SRCS:%.c=%.o) \
	   $(PARSING_SRCS:%.c=%.o) $(JOB_CTRL_SYSTEM_SRCS:%.c=%.o) \
	   $(INPUT_SRCS:%.c=%.o)

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

debug:
	clang -std=c11 -Wall -Wextra -Wpedantic -ltermcap -g \
	src/*.c src/builtins/*.c src/clearing/*.c src/utils/*.c src/core/*.c \
	src/builtins/cd/*.c src/builtins/export/*.c src/builtins/env/*.c \
	src/builtins/which/*.c src/parsing/*.c src/input/*.c \
	src/job_control_system/*.c libmx/libmx.a -I libmx/inc/ -I inc/ -o ush
