#include "minishell.h"
#include "get_next_line/get_next_line.h"

char	**removing_spaces_null_arg(char **tab)
{
	char **new;
	int i;
	int j;

	j = ft_strlen_full_str(tab);
	if (!j)
	{
		free_tab(tab, ft_strlen_tab(tab));
		return (NULL);
	}
	i = 0;
	new = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while(tab[i])
	{
		if (check_spaces_arg(tab[i]))
		{
			new[j] = ft_strdup(tab[i]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	new[j] = NULL;
	free(tab);
	return(new);
}

int	ft_clc(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (s[i] == c && check_back(s, i)) //pour garder les doublons if (s[i] != c && s[i - 1] == c && check_back(s, i - 1))
			j++;
		i++;
	}
	return (j);
}
int	*position( char *s, char c,int size)
{
	int i, j;
	int *pos = malloc(sizeof(int) * size);
	if (!pos)
		return(NULL);
	i = 0;
	j = 0;
	if (!s[0])
	{
		free(pos);
		return (NULL);
	}
	while (s[i])
	{
		if (s[i] == c && check_back(s, i)) //pour garder les doublons if (s[i] != c && s[i - 1] == c && check_back(s, i - 1))
		{
			pos[j] = i;
			j++;
		}
		i++;
	}
	return(pos);
}
char **ft_alloc(int *pos, int l, char c,  char *s)
{
	int i;
	int dx;
	char **p;
	int size;

	size = l;
	if (s[0] != c && s[ft_strlen(s) - 1] != c)
		size = l + 1;
	else if (s[0] == c && s[ft_strlen(s) - 1] == c)
		size = l - 1;
	dx = 0;
	i = 0;
	p = malloc(sizeof(char *) * (size + 1));
	if (!p)
		return(NULL);
	if (!l)
	{
		p[0] = ft_substr(s, 0, ft_strlen(s));
		p[1] = NULL;
		return(p);
	}
	if (pos[i] != 0)
	{
		p[dx] = ft_substr(s, 0, pos[0]);
		dx++;
	}
	while(i < l - 1)
	{
		p[dx] = ft_substr(s,pos[i] + 1 , pos[i + 1] - pos[i] - 1);
		if (!p[dx])
			free_tab(p, dx);
		dx++;
		i++;
	}
	if (pos[i] != ft_strlen(s) - 1)
	{
		p[dx] = ft_substr(s, pos[i] + 1, ft_strlen(s) - 1 - pos[i]);
		dx++;
	}
	p[size] = NULL;
	return(p);
}
char	**special_split(char *s, char c)
{
	int i;
	int l;
	int *pos;
	char **tab;

	i = 0;
	l = ft_clc(s, c);
	if (l)
		pos = position(s, c, l);
	else
		pos = NULL;
	if (c == ';')
	{
		if (!check_doublons(pos, l))
		{
			free(pos);
			printf("ERROR : parse error near `;;'\n");
			return (NULL);
		}
	}
	tab = ft_alloc(pos, l, c, s);
	if (!tab)
	{
		free(pos);
		return (NULL);
	}
	if (c == '|')
	{
		if (!check_null_block(tab))
		{
			free_tab(tab, ft_strlen_tab(tab));
			printf("ERROR : parse error near `|'\n");
			free(pos);
			return (NULL);
		}
	}
	free(pos);
	tab = removing_spaces_null_arg(tab);
	return(tab);
}