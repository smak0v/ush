APP_NAME = libmx.a

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
CC = clang

DIR_NAME = libmx

SRCD = src
INCD = inc
OBJD = obj

INC = libmx.h
INCS = $(addprefix $(INCD)/, $(INC))

SRC = \
mx_binary_search.c \
mx_bubble_sort.c \
mx_count_substr.c \
mx_count_words.c \
mx_del_strarr.c \
mx_del_intarr.c \
mx_foreach.c \
mx_get_char_index.c \
mx_get_substr_index.c \
mx_hex_to_nbr.c \
mx_isspace.c \
mx_isalpha.c \
mx_islower.c \
mx_isupper.c \
mx_isdigit.c \
mx_toupper.c \
mx_tolower.c \
mx_itoa.c \
mx_lltoa.c \
mx_ulltoa.c \
mx_atoi.c \
mx_ctoi.c \
mx_nbr_to_hex.c \
mx_pow.c \
mx_print_strarr.c \
mx_printchar.c \
mx_printchar_endl.c \
mx_print_unicode.c \
mx_printint.c \
mx_printint_endl.c \
mx_printstr.c \
mx_printstr_endl.c \
mx_print_error.c \
mx_print_error_endl.c \
mx_quicksort.c \
mx_sqrt.c \
mx_str_reverse.c \
mx_strcat.c \
mx_strcmp.c \
mx_strcpy.c \
mx_strdel.c \
mx_intdel.c \
mx_strdup.c \
mx_strndup.c \
mx_strlen.c \
mx_numlen.c \
mx_unumlen.c \
mx_strncmp.c \
mx_strncpy.c \
mx_strnew.c \
mx_strstr.c \
mx_strtrim.c \
mx_swap_char.c \
mx_del_extra_spaces.c \
mx_strsplit.c \
mx_strjoin.c \
mx_get_file_length.c \
mx_read_line.c \
mx_file_to_str.c \
mx_replace_substr.c \
mx_memset.c \
mx_memcpy.c \
mx_memccpy.c \
mx_memcmp.c \
mx_memchr.c \
mx_memrchr.c \
mx_memmem.c \
mx_memmove.c \
mx_realloc.c \
mx_memalloc.c \
mx_create_node.c \
mx_pop_back.c \
mx_pop_front.c \
mx_push_back.c \
mx_push_front.c \
mx_list_size.c \
mx_sort_list.c \
mx_reverse_list.c \
mx_is_equal_lists.c \
mx_get_arr_length.c \
mx_count_unequal.c \
mx_check_set.c \
mx_create_set.c \
mx_strarr_len.c \
mx_pop_string_array.c \
mx_list_merge_sort.c \
mx_list_insertion_sort.c \
mx_push_second.c \

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(APP_NAME)

$(APP_NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r\33[2K$@\t\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCD)
	@printf "\r\33[2K$(APP_NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%)"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)
	@printf "$(DIR_NAME)/$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(APP_NAME)
	@printf "$(APP_NAME)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install
