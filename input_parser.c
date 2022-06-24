/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:05:44 by danimart          #+#    #+#             */
/*   Updated: 2022/06/24 13:21:06 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_number(char *str)
{
	int		i;
	long	res;

	res = 0;
	i = 0;
	if (str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	if (res > INT_MAX)
		return (-2);
	return (res);
}

t_philo_info	*parse_arguments(int argc, char **args)
{
	t_philo_info	info;
	t_philo_info	*res;
	int				i;
	long			current_num;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		print_error(ARGC_ERR);
		return (NULL);
	}
	while (i < argc)
	{
		current_num = get_number(args[i]);
		printf("Number at %d is %ld\n", i, current_num);
		i++;
	}
	info.amount = 10;
	res = &info;
	return (res);
}
