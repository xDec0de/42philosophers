/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:31:27 by danimart          #+#    #+#             */
/*   Updated: 2022/07/13 18:38:21 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parameters:
number_of_philosophers, also the number of forks.
time_to_die (ms)
time_to_eat (ms)
time_to_sleep (ms)
number_of_times_each_philosopher_must_eat, optional
if not specified simulation stops after one death.

./philo 2 10 10 10
./philo 2 10 10 10 4
*/

#include "philosophers.h"

void	*print_error(char *err, void *ret)
{
	printf("%s", err);
	return (ret);
}

int	main(int argc, char **args)
{
	t_philo_info	*info;

	info = parse_arguments(argc, args);
	if (info == NULL)
		return (1);
	printf("Number of philosophers is %d\nTime to die is %d\nTime to eat is %d\nTime to sleep is %d\nEat times are %d\n", info->amount, info->die_time, info->eat_time, info->sleep_time, info->eat_num);
	return (0);
}
