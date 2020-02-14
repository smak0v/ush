LIB_NAME = libmx.a

SRC_DIR = src

OBJ_DIR = obj

INC = inc/

SRC = $(addprefix $(SRC_DIR)/, \
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
mx_push_second.c)

OBJ = \
mx_binary_search.o \
mx_bubble_sort.o \
mx_count_substr.o \
mx_count_words.o \
mx_del_strarr.o \
mx_del_intarr.o \
mx_foreach.o \
mx_get_char_index.o \
mx_get_substr_index.o \
mx_hex_to_nbr.o \
mx_isspace.o \
mx_isalpha.o \
mx_islower.o \
mx_isupper.o \
mx_isdigit.o \
mx_toupper.o \
mx_tolower.o \
mx_itoa.o \
mx_lltoa.o \
mx_ulltoa.o \
mx_atoi.o \
mx_ctoi.o \
mx_nbr_to_hex.o \
mx_pow.o \
mx_print_strarr.o \
mx_printchar.o \
mx_printchar_endl.o \
mx_print_unicode.o \
mx_printint.o \
mx_printint_endl.o \
mx_printstr.o \
mx_printstr_endl.o \
mx_print_error.o \
mx_print_error_endl.o \
mx_quicksort.o \
mx_sqrt.o \
mx_str_reverse.o \
mx_strcat.o \
mx_strcmp.o \
mx_strcpy.o \
mx_strdel.o \
mx_intdel.o \
mx_strdup.o \
mx_strndup.o \
mx_strlen.o \
mx_numlen.o \
mx_unumlen.o \
mx_strncmp.o \
mx_strncpy.o \
mx_strnew.o \
mx_strstr.o \
mx_strtrim.o \
mx_swap_char.o \
mx_del_extra_spaces.o \
mx_strsplit.o \
mx_strjoin.o \
mx_get_file_length.o \
mx_file_to_str.o \
mx_read_line.o \
mx_replace_substr.o \
mx_memset.o \
mx_memcpy.o \
mx_memccpy.o \
mx_memcmp.o \
mx_memchr.o \
mx_memrchr.o \
mx_memmem.o \
mx_memmove.o \
mx_realloc.o \
mx_memalloc.o \
mx_create_node.o \
mx_pop_back.o \
mx_pop_front.o \
mx_push_back.o \
mx_push_front.o \
mx_list_size.o \
mx_sort_list.o \
mx_reverse_list.o \
mx_is_equal_lists.o \
mx_get_arr_length.o \
mx_count_unequal.o \
mx_check_set.o \
mx_create_set.o \
mx_strarr_len.o \
mx_pop_string_array.o \
mx_list_merge_sort.o \
mx_list_insertion_sort.o \
mx_push_second.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all : install

install : libmx.a

libmx.a : $(SRC) inc/libmx.h
	@$(CC) $(CFLAGS) -c $(SRC) -I $(INC)
	@ar rcs $(LIB_NAME) $(OBJ)
	@mkdir $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)

uninstall : clean
	@rm -rf $(LIB_NAME)

clean :
	@rm -rf $(OBJ_DIR)

reinstall : uninstall install
