/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:24 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 18:06:16 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	verify_info(t_philo_info *info)
{
	int	errors;

	errors = 0;
	if (info->amount <= 0 || info->amount > MAX_PHILOSOPHERS)
	{
		printf(AMOUNT_ERR, MAX_PHILOSOPHERS);
		errors++;
	}
	else if (info->amount > 200)
		print_error(AMOUNT_WARN, 1);
	if (info->die_time <= 0)
		errors += print_error(DIE_TIME_ERR, 1);
	if (info->eat_time <= 0)
		errors += print_error(EAT_TIME_ERR, 1);
	if (info->sleep_time <= 0)
		errors += print_error(SLEEP_TIME_ERR, 1);
	if (info->eat_num <= 0)
		errors += print_error(EAT_NUM_ERR, 1);
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

t_philo_info	*parse_arguments(int argc, char **argv)
{
	t_philo_info	info;
	t_philo_info	*res;

	if (argc < 5 || argc > 6)
	{
		print_error(ARGC_ERR, 1);
		return (NULL);
	}
	info.amount = get_number(argv[1]);
	info.die_time = get_number(argv[2]);
	info.eat_time = get_number(argv[3]);
	info.sleep_time = get_number(argv[4]);
	if (argc == 6)
		info.eat_num = get_number(argv[5]);
	else
		info.eat_num = 1;
	res = &info;
	if (verify_info(res) != 0)
		return (NULL);
	return (res);
}
