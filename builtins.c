#include "minishell.h"
#include "get_next_line/get_next_line.h"

int     ft_cmp(char *s1, char *s2)
{
        int     i;

        i = 0;
        while (s2[i])
        {
                if (s1[i] != s2[i])
                        return (0);
                i++;
        }
        if (!s1[i])
                return (1);
        return (0);
}
void    ft_echo(char **tab) //quotation probleme
{
    int i;
    int indice;

    indice = 0;
    i = 0;
    if (!*tab)
    {
        write(1, "\n", 1);
        return ;
    }
    if (ft_cmp(tab[0], "-n"))
    {
        indice = 1;
        i++;
    }
    while(tab[i])
    {
        write(1, tab[i], ft_strlen(tab[i]));
        write(1, " ", 1);
        i++;
    }
    if (!indice)
        write(1, "\n", 1);
}