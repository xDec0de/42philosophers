/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:36:24 by danimart          #+#    #+#             */
/*   Updated: 2023/10/16 19:25:04 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"
#include "headers/text_colors.h"

t_philo_info	*init_info(void)
{
	t_philo_info	*info;
	int				errors;

	errors = 0;
	info = malloc(sizeof(t_philo_info));
	if (info == NULL)
		return (free_info(MALLOC_ERR, NULL, NULL));
	info->ready = 0;
	info->m_print = mutex_init(&errors);
	info->m_ready = mutex_init(&errors);
	if (errors != 0)
		return (NULL);
	info->start_date = 0;
	info->valid = 1;
	return (info);
}

t_philo_info	*verify_info(t_philo_info *info)
{
	int	errors;

	errors = 0;
	if (info->amount <= 0 || info->amount > MAX_PHILOSOPHERS)
	{
		printf(AMOUNT_ERR, MAX_PHILOSOPHERS);
		errors++;
	}
	else if (info->amount > 200)
		errors += (int) free_info(AMOUNT_WARN, NULL, (void *)1);
	if (info->die_time <= 0)
		errors += (int) free_info(DIE_TIME_ERR, NULL, (void *)1);
	if (info->eat_time <= 0)
		errors += (int) free_info(EAT_TIME_ERR, NULL, (void *)1);
	if (info->sleep_time <= 0)
		errors += (int) free_info(SLEEP_TIME_ERR, NULL, (void *)1);
	if (info->eat_num < 0)
		errors += (int) free_info(EAT_NUM_ERR, NULL, (void *)1);
	if (errors == 0)
		return (info);
	return (free_info(NULL, info, NULL));
}

unsigned long long	get_number(char *str)
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

t_philo_info	*parse_arguments(int argc, char **argv)
{
	t_philo_info	*info;

	if (argc < 5 || argc > 6)
		return (notify_argc_err(argc));
	info = init_info();
	if (info == NULL)
		return (NULL);
	info->amount = get_number(argv[1]);
	info->die_time = get_number(argv[2]);
	info->eat_time = get_number(argv[3]);
	info->sleep_time = get_number(argv[4]);
	if (argc == 6)
		info->eat_num = get_number(argv[5]);
	else
		info->eat_num = 0;
	info = verify_info(info);
	return (info);
}
