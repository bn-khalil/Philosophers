/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:09 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 13:23:01 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

long	long_ft_atoi(const char *str)
{
	int		i;
	long	store;
	int		si;

	i = 0;
	si = 1;
	store = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			si *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		store = store * 10 + (str[i++] - '0');
	return (store * si);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		strlen;
	char	*str;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * strlen + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	strlen = 0;
	while (s2[strlen])
		str[i++] = s2[strlen++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_error(char *err)
{
	printf("%s\n", err);
}
