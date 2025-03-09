/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:37 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:48:45 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	nbr_len(unsigned int n)
{
	if (n <= 9)
		return (1);
	return (nbr_len(n / 10) + 1);
}

static char	*create_str(unsigned int nb, char *str, int i, int sign)
{
	if (sign == -1)
		str[i + 1] = '\0';
	else
		str[i] = '\0';
	if (str[0] != '-')
		i--;
	while (i >= 0 && str[i] != '-')
	{
		str[i] = '0' + (nb % 10);
		nb /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	long	nb;
	int		i;

	sign = 1;
	nb = n;
	if (nb < 0)
	{
		sign = -1;
		nb = -nb;
	}
	if (nb == 0)
		return (ft_strdup("0"));
	i = nbr_len(nb);
	if (sign == -1)
		str = calloc((i + 2), sizeof(char));
	else
		str = calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (sign < 0)
		str[0] = '-';
	return (create_str(nb, str, i, sign));
}

int	count_width(char *line)
{
	int	width;
	int	i;

	width = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
			width++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (width);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	fdf_strstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i -= 4;
	return (ft_strcmp(s + i, ".fdf"));
}
