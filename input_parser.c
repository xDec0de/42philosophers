/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:05:44 by danimart          #+#    #+#             */
/*   Updated: 2022/07/13 22:07:23 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	verify_info(t_philo_info info)
{
	int	errors;

	errors = 0;
	if (info.amount <= 0)
		errors += (int)print_error(AMOUNT_ERR, (void *)1);
	if (info.die_time <= 0)
		errors += (int)print_error(DIE_TIME_ERR, (void *)1);
	if (info.eat_time <= 0)
		errors += (int)print_error(EAT_TIME_ERR, (void *)1);
	if (info.sleep_time <= 0)
		errors += (int)print_error(SLEEP_TIME_ERR, (void *)1);
	if (info.eat_num <= 0)
		errors += (int)print_error(EAT_NUM_ERR, (void *)1);
	return (errors);
}

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

	i = 1;
	if (argc < 5 || argc > 6)
		return (print_error(ARGC_ERR, NULL));
	info.amount = get_number(args[1]);
	info.die_time = get_number(args[2]);
	info.eat_time = get_number(args[3]);
	info.sleep_time = get_number(args[4]);
	if (argc == 6)
		info.eat_num = get_number(args[5]);
	else
		info.eat_num = 1;
	res = &info;
	if (verify_info(info) != 0)
		return (NULL);
	return (res);
}
