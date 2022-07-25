SRCS = minishell.c cmd_block.c strlen_free.c check_counter.c point_virgule.c pipe_block.c \
	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ft_split.c

 
SRCS_BONUS = 

NAME = minishell

NAME_BONUS = 

CC = gcc

FLAGS = -Wall -Wextra -Werror

${NAME} :
		${CC}  -lreadline ${SRCS} -o ${NAME}

${NAME_BONUS} :
		${CC} ${FLAGS} ${SRCS_BONUS} -o ${NAME_BONUS}

all : mandatory bonus

mandatory : ${NAME}

bonus : ${NAME_BONUS}

clean :
		rm -f ${NAME}

bclean :
		rm -f ${NAME_BONUS}

fclean :	clean bclean

re : clean mandatory

bre : bclean bonus

re_all : fclean all 