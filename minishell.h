#ifndef MINISHELL_H
#define MINISHELL_H

//#include <unistd.h>
//#include <fcntl.h>              
//#include <stdio.h>
//#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct data
{
    int len;
    int index;
    int **tube;
}   t_data;

typedef struct env
{
    char **path;
    char **var;
}   t_env;

int     ft_cmp(char *s1, char *s2);
void	free_tab_of_tab(char ***pipe_block, int index);
void	free_tab(char **tab, int index);
int ft_strlen_tab(char **tab);
int	ft_strlen_tab_tab(char ***tab);
int	ft_strlen_full_str(char **tab);

int check_spaces_arg(char *tab);
int	check_back(char *s, int index);
int	check_null_block(char **tab);
int check_doublons(int *pos, int size);
int counter(char *tab, char c);
int	quotes_check(char **block);
char	**special_split(char *s, char c);
char	**removing_spaces_null_arg(char **tab);

char ***parsing_by_pipe(char **block);
int	ft_strlen_full_str(char **tab);
int len_no_null_block(char **block);

char	*ft_strdup(char *s1);
char	*ft_substr(char  *s, unsigned int start, int len);

char **last_step_parsing(char *block, char *env[]);
void    print_free_blocks(char **block);
char	**ft_split(char const *s, char c);

#endif