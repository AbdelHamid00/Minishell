#include "minishell.h"
#include "get_next_line/get_next_line.h"

int check_spaces_arg(char *tab)
{
	int i;

	i = 0;
	if (!tab[0])
		return (0);
	while(tab[i])
	{
		if (tab[i] != ' ' && tab[i] != '\t')
			return (1);
		i++;
	}
	return(0);
}

int	check_back(char *s, int index)
{
	int count39;
	int count34;

	count34 = 0;
	count39 = 0;
	while(index >= 0)
	{
		if (s[index] == 39)
			count39++;
		else if (s[index] == 34)
			count34++;
		index--;
	}
	if ((count34 % 2) || (count39 % 2))
		return(0);
	else
		return(1);
}

int	check_null_block(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		if (!check_spaces_arg(tab[i]))
			return(0);
		i++;
	}
	return(1);
}

int check_doublons(int *pos, int size)
{
	int i;

	i = 0;
	if (size == 0 || size == 1)
		return(1);
	while(i < size - 1)
	{
		if (pos[i] == pos[i + 1] - 1)
			return (0);
		i++;
	}
	return (1);
}

int counter(char *tab, char c)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while(tab[i])
    {
        if (tab[i] == c)
            j++;
        i++;
    }
    return(j);
}