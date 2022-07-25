#include "minishell.h"
#include "get_next_line/get_next_line.h"

int ft_strlen_tab(char **tab)
{
	int i = 0;
	while(tab[i])
		i++;
	return (i);
}
int	ft_strlen_tab_tab(char ***tab)
{
	int i = 0;
	while(tab[i])
		i++;
	return(i);
}
void	free_tab(char **tab, int index)
{
	if (!index)
		return ;
	while(index > 0)
	{
		index--;
		free(tab[index]);
	}
	free(tab);
}

void	free_tab_of_tab(char ***pipe_block, int index)
{
	if (!index)
		return ;
	while(index > 0)
	{
		index--;
		free_tab(pipe_block[index], ft_strlen_tab(pipe_block[index]));
	}
}