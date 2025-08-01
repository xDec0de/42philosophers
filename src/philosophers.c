/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:29:55 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 22:05:11 by daniema3         ###   ########.fr       */
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

static	void launch_simulation(t_philo_info *info)
{
	int	id;

	id = 0;
	info->start_date = get_current_time();
	while (id < info->philo_n)
	{
		launch_philo(info->philo_lst[id]);
		id++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	info = parse_arguments(argc, argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	if (!build_philosophers(info))
		return (EXIT_FAILURE);
	launch_simulation(info);
	free_info(info);
	return (EXIT_SUCCESS);
}
