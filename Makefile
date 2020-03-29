#================================COMMON=======================================#
APP_NAME				= ush

CC						= clang
CFLAGS					= -std=c11 -Wall -Wextra -Wpedantic
ADDITIONAl_FLAGS		= -g
LINKER_FLAGS			= -ltermcap

DIR_NAME				= ush

SRCD					= src
INCD					= inc

LIBMXD					= libmx
LIBMXA					:= $(LIBMXD)/libmx.a
LIBMXI					:= $(LIBMXD)/inc

INC						= ush.h
INCS					= $(addprefix $(INCD)/, $(INC))

#===================================OBJ=======================================#
OBJD					= obj

CORE_OBJD				= $(OBJD)/core
INPUT_OBJD				= $(OBJD)/input
UTILS_OBJD				= $(OBJD)/utils
CLEARING_OBJD			= $(OBJD)/clearing
BUILTINS_OBJD			= $(OBJD)/builtins
PARSING_OBJD			= $(OBJD)/parsing
JOB_CTRL_SYSTEM_OBJD	= $(OBJD)/job_control_system
CMD_SUBSTS_OBJD			= $(OBJD)/cmd_substitutions

ENV_OBJD				= $(BUILTINS_OBJD)/env
EXPORT_OBJD				= $(BUILTINS_OBJD)/export
WHICH_OBJD				= $(BUILTINS_OBJD)/which
CD_OBJD					= $(BUILTINS_OBJD)/cd
FG_OBJD					= $(BUILTINS_OBJD)/fg
JOBS_OBJD				= $(BUILTINS_OBJD)/jobs

OBJ_DIRS				= $(OBJD) $(CORE_OBJD) $(INPUT_OBJD) $(UTILS_OBJD) \
						  $(CLEARING_OBJD) $(BUILTINS_OBJD) $(ENV_OBJD) \
						  $(EXPORT_OBJD) $(WHICH_OBJD) $(CD_OBJD) $(FG_OBJD) \
						  $(JOBS_OBJD) $(PARSING_OBJD) $(CMD_SUBSTS_OBJD) \
						  $(JOB_CTRL_SYSTEM_OBJD)

OBJS					= $(addprefix $(OBJD)/, main.o $(CORE:%.c=%.o) \
						  $(UTILS:%.c=%.o) $(BUILTINS:%.c=%.o) $(ENV:%.c=%.o) \
						  $(EXPORT:%.c=%.o) $(WHICH:%.c=%.o) $(CD:%.c=%.o) \
						  $(PARSING:%.c=%.o) $(JOB_CTRL_SYSTEM:%.c=%.o) \
						  $(INPUT:%.c=%.o) $(FG:%.c=%.o) $(JOBS:%.c=%.o) \
						  $(CMD_SUBSTS:%.c=%.o) $(CLEARING:%.c=%.o))

#===================================SRC=======================================#
CORE_SRCS				= ush_loop.c process_commands_list.c \
						  traverse_and_execute_tree.c init_ush.c input_mode.c \
						  signals.c

INPUT_SRCS				= get_input.c history.c expansions.c tilde_exp.c \
						  dollar_exp.c input_keys.c input_utils.c

UTILS_SRCS				= build_pwd_string.c getenv.c set_defaults.c \
						  check_identifier_validity.c mx_printnbr.c \
						  setup_underscore_env_var.c create_tmp_env.c \
						  overwrite_strarr_value.c split_key_value.c \
						  create_trees.c print_tree.c ush_errors.c errors.c \
						  process_home.c check_flag.c is_builtin.c \
						  init_builtins.c

CLEARING_SRCS			= clear_tokens.c clear_trees.c clear_processes_data.c

BUILTINS_SRCS			= builtins.c builtins2.c parse_flags.c parse_args.c \
						  validation.c mixed_errors.c unset.c exit.c

ENV_SRCS				= env.c env_errors.c parse_env.c janitor.c

EXPORT_SRCS				= export.c process_duplicates.c

WHICH_SRCS				= which.c which_utils.c

CD_SRCS					= cd.c path.c cd_errors.c build_logical_path.c

FG_SRCS					= fg.c fg_errors.c fg_utils.c

JOBS_SRCS				= jobs.c jobs_errors.c

PARSING_SRCS			= proccess_escapings.c split_cmd.c split_token.c

JOB_CTRL_SYSTEM_SRCS	= jcs_utils.c job_utils.c process_utils.c \
						  launch_job.c launch_process.c

CMD_SUBSTS_SRCS			= cmd_substs.c cmd_substs_utils.c

CORE					= $(addprefix core/, $(CORE_SRCS))
INPUT					= $(addprefix input/, $(INPUT_SRCS))
PARSING					= $(addprefix parsing/, $(PARSING_SRCS))
CLEARING				= $(addprefix clearing/, $(CLEARING_SRCS))
UTILS					= $(addprefix utils/, $(UTILS_SRCS))
JOB_CTRL_SYSTEM			= $(addprefix job_control_system/, \
						  $(JOB_CTRL_SYSTEM_SRCS))
CMD_SUBSTS				= $(addprefix cmd_substitutions/, $(CMD_SUBSTS_SRCS))
BUILTINS				= $(addprefix builtins/, $(BUILTINS_SRCS))

ENV						= $(addprefix builtins/env/, $(ENV_SRCS))
EXPORT					= $(addprefix builtins/export/, $(EXPORT_SRCS))
WHICH					= $(addprefix builtins/which/, $(WHICH_SRCS))
CD						= $(addprefix builtins/cd/, $(CD_SRCS))
FG						= $(addprefix builtins/fg/, $(FG_SRCS))
JOBS					= $(addprefix builtins/jobs/, $(JOBS_SRCS))

#=================================RULES=======================================#
all: install

install: $(LIBMXA) $(APP_NAME)

$(OBJ_DIRS):
	@mkdir -p $@

$(LIBMXA):
	@make -sC $(LIBMXD)

clean:
	@rm -rf $(OBJD)
	@printf "$(DIR_NAME)/$(OBJD)\t\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@make -sC $(LIBMXD) $@
	@rm -rf $(APP_NAME)
	@printf "$(APP_NAME)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

#==============================DEPENDENCIES===================================#
$(APP_NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) $(LINKER_FLAGS) $(OBJS) -L $(LIBMXD) -lmx -o $@
	@printf "\r\33[2K$@\t\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/core/%.o: $(SRCD)/core/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/input/%.o: $(SRCD)/input/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/utils/%.o: $(SRCD)/utils/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/clearing/%.o: $(SRCD)/clearing/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/%.o: $(SRCD)/builtins/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/env/%.o: $(SRCD)/builtins/env/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/export/%.o: $(SRCD)/builtins/export/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/which/%.o: $(SRCD)/builtins/which/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/cd/%.o: $(SRCD)/builtins/cd/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/fg/%.o: $(SRCD)/builtins/fg/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/builtins/jobs/%.o: $(SRCD)/builtins/jobs/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/parsing/%.o: $(SRCD)/parsing/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/job_control_system/%.o: $(SRCD)/job_control_system/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJD)/cmd_substitutions/%.o: $(SRCD)/cmd_substitutions/%.c $(INCS)
	@$(CC) $(CFLAGS) $(ADDITIONAl_FLAGS) -c $< -o $@ -I $(INCD) -I $(LIBMXI)
	@printf "\r\33[2K$(DIR_NAME)\t   \033[33;1mcompile\t\033[0m$(<:$(SRCD)%.c=%)"

$(OBJS): | $(OBJ_DIRS)
