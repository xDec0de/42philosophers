/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:24 by danimart          #+#    #+#             */
/*   Updated: 2023/10/01 14:53:23 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo_info	*verify_info(t_philo_info *info)
{
	int	errors;
	int	one;

	errors = 0;
	one = 1;
	if (info->amount <= 0 || info->amount > MAX_PHILOSOPHERS)
	{
		printf(AMOUNT_ERR, MAX_PHILOSOPHERS);
		errors++;
	}
	else if (info->amount > 200)
		errors += (int) print_error(AMOUNT_WARN, info, &one);
	if (info->die_time <= 0)
		errors += (int) print_error(DIE_TIME_ERR, info, &one);
	if (info->eat_time <= 0)
		errors += (int) print_error(EAT_TIME_ERR, info, &one);
	if (info->sleep_time <= 0)
		errors += (int) print_error(SLEEP_TIME_ERR, info, &one);
	if (info->eat_num <= 0)
		errors += (int) print_error(EAT_NUM_ERR, info, &one);
	if (errors == 0)
		return (info);
	return (NULL);
}

t_philo_info	*print_info(t_philo_info *info)
{
	if (!DEBUG || info == NULL)
		return (info);
	printf(DEBUG_NOTE);
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

void	*notify_argc_err(int argc)
{
	if (argc > 6)
		return (print_error(ARGC_LONG, NULL, NULL));
	print_error(ARGC_SMALL, NULL, NULL);
	if (argc < 2)
		printf(MISSING_ARG, "Amount of philosophers");
	if (argc < 3)
		printf(MISSING_ARG, "Time to die");
	if (argc < 4)
		printf(MISSING_ARG, "Time to eat");
	if (argc < 5)
		printf(MISSING_ARG, "Time to sleep");
	return (NULL);
}

t_philo_info	*parse_arguments(int argc, char **argv)
{
	t_philo_info	*info;

	if (argc < 5 || argc > 6)
		return (notify_argc_err(argc));
	info = malloc(sizeof(t_philo_info));
	info->amount = get_number(argv[1]);
	info->die_time = get_number(argv[2]);
	info->eat_time = get_number(argv[3]);
	info->sleep_time = get_number(argv[4]);
	if (argc == 6)
		info->eat_num = get_number(argv[5]);
	else
		info->eat_num = 1;
	info->start_date = 0;
	info->valid = 1;
	return (print_info(verify_info(info)));
}
