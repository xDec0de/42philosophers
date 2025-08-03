/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:29:55 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/03 20:09:14 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	build_philosophers(t_philo_info *info)
{
	int		id;
	t_philo	*philo;

	id = 1;
	while (id <= info->philo_n)
	{
		philo = init_philo(info, (unsigned int) id);
		if (philo == NULL)
		{
			free_info(info);
			return (false);
		}
		info->philo_lst[id - 1] = philo;
		id++;
	}
	return (true);
}

static bool	launch_simulation(t_philo_info *info)
{
	int			id;
	t_philo		*philo;

	id = 0;
	info->start_date = get_current_time();
	while (id < info->philo_n)
	{
		philo = info->philo_lst[id];
		if (pthread_create(&philo->thread_id, NULL, &launch_philo, philo) != 0)
		{
			printf(THREAD_ERR);
			return (false);
		}
		id++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	info = parse_arguments(argc, argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	if (!build_philosophers(info))
		return (EXIT_FAILURE);
	if (!launch_simulation(info))
		return (EXIT_FAILURE);
	while (launch_watcher(info))
		usleep(500);
	return (EXIT_SUCCESS);
}
