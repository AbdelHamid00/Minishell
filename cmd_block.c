#include "minishell.h"
#include "get_next_line/get_next_line.h"

int number_of_cmds(char *tab)
{
	int i;
	int count;

	i = 0;
	count = 0;

	if (tab[i] != ' ' && tab[i] != '\t')
		count++;
	i = 1;
	while(tab[i])
	{
		if ((tab[i - 1] == ' ' || tab[i - 1] == '\t') && (tab[i] != '\t' && tab[i] != ' ') && check_back(tab, i - 1))
			count++;
		else if ((tab[i - 1] != '<' && tab[i - 1] != '>') && (tab[i] == '<' || tab[i] == '>') && check_back(tab, i))
			count++;
		else if ((tab[i - 1] == '<' || tab[i - 1] == '>') && (tab[i] != '<' && tab[i] != '>') && check_back(tab, i - 1))
			count++;
		i++; 
	}
	return(count);
}
int *position_of_pars(char *tab, int size)
{
	int *pos;
	int i;
	int count;

	i = 0;
	count = 0;
	pos = malloc(sizeof(int) * size);
	if (tab[i] != ' ' && tab[i] != '\t')
	{
		pos[count] = i;
		count++;
	}
	i = 1;
	while(tab[i])
	{
		if ((tab[i - 1] == ' ' || tab[i - 1] == '\t') && (tab[i] != '\t' && tab[i] != ' ') && check_back(tab, i - 1))
		{
			pos[count] = i;
			count++;
		}
		else if ((tab[i - 1] != '<' && tab[i - 1] != '>') && (tab[i] == '<' || tab[i] == '>') && check_back(tab, i))
		{
			pos[count] = i;
			count++;
		}
		else if ((tab[i - 1] == '<' || tab[i - 1] == '>') && (tab[i] != '<' && tab[i] != '>') && check_back(tab, i - 1))
		{
			pos[count] = i;
			count++;
		}
		i++;
	}
	return(pos);

}
int ft_strlen_no_spaces(char *tab)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while(tab[i])
	{
		if ((tab[i] != ' ' && tab[i] != '\t') || ((tab[i] == ' ' || tab[i] == '\t') && !check_back(tab, i)))
			len++;
		i++;
	}
	return(len);
}

char *new_tab(char *tab)
{
	char *new;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = ft_strlen_no_spaces(tab);
	new = malloc(sizeof(char) * len + 1);
	while(tab[i])
	{
		if ((tab[i] != ' ' && tab[i] != '\t') || ((tab[i] == ' ' || tab[i] == '\t') && !check_back(tab, i)))
		{
			new[j] = tab[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(tab);
	return(new);
}

void    removing_spaces(char **tab)
{
	int i;
	int j;

	i = 0;
	while(tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			if ((tab[i][j] == ' ' || tab[i][j] == '\t') && check_back(tab[i], j))
			{
				tab[i] = new_tab(tab[i]);
				break ;
			}
			j++;
		}
		i++;
	}
}
/*
int ft_strlen_no_quotes(char *tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(tab[i])
	{
		if (tab[i] != 34 && tab[i] != 39)
			j++;
		i++;
	}
	return (j);
}


int paire_or_impaire(char *tab)
{
	int i;
	int j_34;
	int j_39;

	i = 0;
	j_34 = 0;
	j_39 = 0;
	while(tab[i])
	{
		if ((tab[i] != 34 && tab[i] != 39 && tab[i] != ' ' && tab[i] != '\t') || (j_34 && tab[i] == 39) || (j_39 && tab[i] == 34))
			break;
		else if (tab[i] == 34)
			j_34++;
		else if (tab[i] == 39)
			j_39++;
		i++;
	}
	if (j_34)
		return(j_34 % 2);// 0 o r 1
	else
		return(j_39 % 2);// 0 or 1
}

int the_start(char *tab, int mode)
{
	int i;

	i = 0;
	while(tab[i])
	{
		if ((tab[i] != mode  && tab[i] != ' ' && tab[i] != '\t'))
			return (i);
		i++;
	}
	return(1337);
}
int the_end(char *tab, int mode)
{
	int i;

	i = ft_strlen(tab) - 1;
	while(i >= 0)
	{
		if ((tab[i] != mode  && tab[i] != ' ' && tab[i] != '\t'))
			return (i);
		i--;
	}
	return(1337);
}

char *tab_no_quotes(char *tab, int len)
{
	int i;
	int j;
	char *new;
	
	new = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while(tab[i])
	{
		if (tab[i] != 34 && tab[i] != 39)
		{
			new[j] = tab[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return(new);
}

char *new_tab_two(char *tab, int mode, int p_imp, char *env[])
{
	char *new;
	int start;
	int end;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!p_imp)
	{
		new = tab_no_quotes(tab, ft_strlen_no_quotes(tab));
	}
	else
	{
		//remove mode (" or ')
		start = the_start(tab, mode);
		end = the_end(tab, mode);
		new = malloc(sizeof(char) *  (end - start + 1));
		new = ft_substr(tab, start, end - start + 1);
	}
	free(tab);
	return(new);
}
void    removing_quotes_and_dollars(char **tab, char *env[])
{
	int i;
	int j;

	i = 0;
	while(tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			if (tab[i][j] == 39)
			{
				tab[i] = new_tab_two(tab[i], 39, paire_or_impaire(tab[i]), env);
				break ;
			}
			else if (tab[i][j] == 34)
			{
				tab[i] = new_tab_two(tab[i], 34, paire_or_impaire(tab[i]), env);
				break ;
			}
			j++;
		}
		i++;
	}
}*/

char **last_pars(char *block, int *pos, int size)
{
	char **tab;
	int i;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	while(i < size - 1)
	{
		tab[i] = ft_substr(block, pos[i] , pos[i + 1] - pos[i]);
		i++;
	}
	tab[i] = ft_substr(block, pos[i] , ft_strlen(block) - pos[i]);
	i += 1;
	tab[i] = NULL;
	return(tab);
}

char **last_step_parsing(char *block, char *env[])
{
	char **cmds;
	int *pos;
	int len;
	int i;

	i = 0;
	len = number_of_cmds(block);
	pos = position_of_pars(block, len);
	cmds = last_pars(block, pos, len);
	cmds = removing_spaces_null_arg(cmds);
	removing_spaces(cmds);
	free(pos);
	return (cmds);
}