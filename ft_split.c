/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:11:28 by aabouzid          #+#    #+#             */
/*   Updated: 2021/11/22 17:41:20 by aabouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "get_next_line/get_next_line.h"
char	*ft_allocate(char **p, char const *str, int k, int m)
{
	int	i;

	i = 0;
	p[m] = (char *)malloc(sizeof(char) * (k + 1));
	if (p[m] == NULL)
	{
		if (m > 1)
		{
			m--;
			while (m >= 0)
			{
				free(p[m]);
				m--;
			}
		}
		return (0);
	}
	while (i < k)
	{
		p[m][i] = str[i];
		i++;
	}
	p[m][i] = '\0';
	return (p[m]);
}

int	ft_calcul(char const *s, char c)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c)
		j++;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			j++;
		i++;
	}
	return (j);
}

void	*ft_allocation(char **p, int l, char c, const char *s)
{
	int	m;
	int	k;

	k = 0;
	m = 0;
	while (m < l && *s != '\0')
	{
		while (*s != c && *s != '\0')
		{
			s++;
			k++;
		}
		if (k != 0)
		{
			p[m] = ft_allocate(p, s - k, k, m);
			if (!p[m])
				return (0);
			m++;
			s--;
			k = 0;
		}
		s++;
	}
	p[m] = NULL;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		l;

	if (!s)
		return (0);
	l = ft_calcul(s, c);
	p = (char **)malloc(sizeof(char *) * (l + 1));
	if (p == 0)
		return (0);
	p = ft_allocation(p, l, c, s);
	if (p == 0)
	{
		free(p);
		return (0);
	}
	return (p);
}
