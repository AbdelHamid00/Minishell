#include "minishell.h"
#include "get_next_line/get_next_line.h"

char	*ft_substr(char  *s, unsigned int start, int len)
{
	char	*p;
	int	i;

	if (!s)
		return (0);
	i = 0;
	if ((ft_strlen(s) - 1) < start)
		start = ft_strlen(s);
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	while (i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (p == 0)
		return (0);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
int	ft_strlen_full_str(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(tab[i])
	{
		if (check_spaces_arg(tab[i]))
			j++;
		i++;
	}
	return (j);
}
int len_no_null_block(char **block)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(block[i])
	{
		if (check_spaces_arg(block[i]))
			j++;
		i++;
	}
	return(j);
}
char ***parsing_by_pipe(char **block)
{
	char ***pipe_block;
	int i;
	int j;
	int len;

	j = 0;
	i = 0;
	if (block[0][0] == '|' || block[ft_strlen_tab(block) - 1][ft_strlen(block[ft_strlen_tab(block) - 1]) - 1] == '|')
	{
		printf("ERROR : parse error near `|'\n");
		return(NULL);
	}
	len = len_no_null_block(block);
	pipe_block = malloc(sizeof(char **) * (len + 1));
	if (!pipe_block)
		return(NULL);
	while(block[i])
	{
		if (check_spaces_arg(block[i]))
		{
			pipe_block[j] = special_split(block[i], '|');
			if (!pipe_block[j])
			{
				free_tab_of_tab(pipe_block, j);
				free(pipe_block);
				return(NULL);
			}
			j++;
		}
		i++;
	}
	pipe_block[j] = NULL;
	return (pipe_block);
}