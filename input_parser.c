/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:24 by danimart          #+#    #+#             */
/*   Updated: 2023/09/07 10:02:40 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo_info	*verify_info(t_philo_info *info)
{
	if (info->amount <= 0 || info->amount > MAX_PHILOSOPHERS)
	{
		printf(AMOUNT_ERR, MAX_PHILOSOPHERS);
		free(info);
		exit(1);
	}
	else if (info->amount > 200)
		exit_error(AMOUNT_WARN, info);
	if (info->die_time <= 0)
		exit_error(DIE_TIME_ERR, info);
	if (info->eat_time <= 0)
		exit_error(EAT_TIME_ERR, info);
	if (info->sleep_time <= 0)
		exit_error(SLEEP_TIME_ERR, info);
	if (info->eat_num <= 0)
		exit_error(EAT_NUM_ERR, info);
	return (info);
}

t_philo_info	*print_info(t_philo_info *info)
{
	printf(INFO_HEADER);
	printf(INFO_NUM, "Philosopher amount", info->amount);
	printf(INFO_NUM, "Time to die", info->die_time);
	printf(INFO_NUM, "Time to eat", info->eat_time);
	printf(INFO_NUM, "Time to sleep", info->sleep_time);
	printf(INFO_NUM, "Times to eat", info->eat_num);
	printf(INFO_FOOTER);
	return (info);
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
	t_philo_info	*info;

	if (argc < 5 || argc > 6)
		exit_error(ARGC_ERR, NULL);
	info = malloc(sizeof(t_philo_info));
	info->amount = get_number(argv[1]);
	info->die_time = get_number(argv[2]);
	info->eat_time = get_number(argv[3]);
	info->sleep_time = get_number(argv[4]);
	if (argc == 6)
		info->eat_num = get_number(argv[5]);
	else
		info->eat_num = 1;
	print_info(verify_info(info));
	return (info);
}
