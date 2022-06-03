/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:31:27 by danimart          #+#    #+#             */
/*   Updated: 2022/06/03 15:58:17 by danimart         ###   ########.fr       */
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

void	print_error(int code)
{
	if (code == ARGC_ERR)
		printf(ARGC_ERR_STR);
}

int	main(int argc, char **args)
{
	t_philo_info	*info;

	info = parse_arguments(argc, args);
	printf("Number of philosophers is %d\n", info->amount);
	return (0);
}
