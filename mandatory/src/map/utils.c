/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:59:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/21 18:01:37 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	usleep(10000);
}

char *get_next_string(char *line, char *str)
{
	int i;
	int j;
	char *tmp;
	char **check_split;

	i = 0;
	j = 0;
	tmp = NULL;
	check_split = ft_split(line, ' ');
	if (ft_arrlen(check_split) != 2)
	{
		ft_arrdel((void **)check_split);
		ft_error("Invalid map info");
	}
	ft_arrdel((void **)check_split);
	if (!line || !str)
		return (NULL);
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	while (line[i] == str[j] && line[i] != '\0' && str[j] != '\0')
	{
		i++;
		j++;
	}
	while (line[i] != '\0' && ft_isspace(line[i]) && line[i] != '\n')
		i++;
	tmp = ft_malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		tmp[j] = line[i];
		i++;
		j++;
	}
	return (tmp);
}

int ft_strlen_space(char *s)
{
	size_t i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]))
			i++;
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

int ft_check_line(char *line)
{
	int i;

	i = 0;
	if (ft_strlen_space(line) == 0)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
