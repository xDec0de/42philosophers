/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:30:02 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/30 19:43:52 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo_info	*verify_info(t_philo_info *info, long long die_time)
{
	unsigned int	err;

	err = 0;
	if (info->philo_n <= 0 || info->philo_n > MAX_PHILOSOPHERS)
		err += printf(AMOUNT_ERR, MAX_PHILOSOPHERS);
	else if (info->philo_n > MAX_RECOMMENDED_PHILOSOPHERS)
		printf(AMOUNT_WARN, MAX_RECOMMENDED_PHILOSOPHERS);
	if (die_time <= 0)
		err += printf(DIE_TIME_ERR);
	if (info->eat_ms <= 0)
		err += printf(EAT_TIME_ERR);
	if (info->sleep_ms <= 0)
		err += printf(SLEEP_TIME_ERR);
	if (info->eat_num < 0)
		err += printf(EAT_NUM_ERR);
	if (err == 0)
		return (info);
	return (NULL);
}

long long	get_number(char *str)
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

void	*notify_argc_err(int argc)
{
	if (argc > 6)
		return (free_info(ARGC_LONG, NULL, NULL));
	free_info(ARGC_SMALL, NULL, NULL);
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

t_philo_info	*parse_arguments(t_philo_info *info, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (notify_argc_err(argc));
	info = init_info();
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
	info = verify_info(info, get_number(argv[2]));
	return (info);
}
