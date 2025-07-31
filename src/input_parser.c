/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:30:02 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/31 15:06:13 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	verify_info(t_philo_info *info)
{
	unsigned int	err;

	err = 0;
	if (info->philo_n <= 0 || info->philo_n > MAX_PHILOSOPHERS)
		err += printf(AMOUNT_ERR, MAX_PHILOSOPHERS);
	else if (info->philo_n > MAX_RECOMMENDED_PHILOSOPHERS)
		printf(AMOUNT_WARN, MAX_RECOMMENDED_PHILOSOPHERS);
	if (info->die_ms <= 0)
		err += printf(DIE_TIME_ERR);
	if (info->eat_ms <= 0)
		err += printf(EAT_TIME_ERR);
	if (info->sleep_ms <= 0)
		err += printf(SLEEP_TIME_ERR);
	if (info->eat_num < 0)
		err += printf(EAT_NUM_ERR);
	return (err == 0);
}

static long long	get_number(char *str)
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
		return (-1);
	return (res);
}

static void	*notify_argc_err(int argc)
{
	if (argc > 6)
		return (printf(ARGC_LONG), NULL);
	printf(ARGC_SMALL);
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
	info = get_info();
	if (info == NULL)
		return (NULL);
	info->philo_n = get_number(argv[1]);
	info->die_ms = get_number(argv[2]);
	info->eat_ms = get_number(argv[3]);
	info->sleep_ms = get_number(argv[4]);
	if (argc == 6)
		info->eat_num = get_number(argv[5]);
	else
		info->eat_num = 0;
	if (verify_info(info))
		return (info);
	free_info(info);
	return (NULL);
}
