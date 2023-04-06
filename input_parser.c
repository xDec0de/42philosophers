/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:24 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 19:48:45 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	verify_info(t_philo_info *info)
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
	verify_info(info);
	return (info);
}
