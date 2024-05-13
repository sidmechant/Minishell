SRCS		=	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c\
				builtins/export.c builtins/pwd.c builtins/unset.c\
				execution/exec_1.c execution/exec_2.c execution/exec_3.c execution/exec_4.c\
				execution/exec_5.c execution/exec_6.c\
				parsing/lexer_1.c parsing/lexer_2.c parsing/lexer_3.c parsing/parser_1.c\
				parsing/parser_2.c parsing/token_1.c parsing/token_2.c parsing/token_3.c\
				sources/main.c sources/signals.c sources/norme.c sources/normal.c sources/coucou.c\
				utils/compare_utils_1.c utils/compare_utils_2.c utils/compare_utils_3.c utils/free_utils.c utils/list_utils.c\
				utils/malloc_utils_1.c utils/malloc_utils_2.c utils/malloc_utils_3.c utils/malloc_utils_4.c\
				utils/print_utils.c
				
OBJS 		=	$(SRCS:.c=.o)
OBJS_DIR	=	Objs_and_Deps
DEPS		=	$(OBJS:.o=.d)
CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror
LIB			=	-L/usr/include -lreadline
NAME		=	minishell

%.o: %.c
				$(CC) -MMD $(CFLAGS) -c $< -o $@

all:			$(OBJS_DIR) $(NAME)

$(NAME):		$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
				mv $(OBJS) $(DEPS) $(OBJS_DIR)

$(OBJS_DIR):
				mkdir $(OBJS_DIR)

clean:
				$(RM) $(OBJS_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

-include $(DEPS)

.PHONY:			all clean fclean re