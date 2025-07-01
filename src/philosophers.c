/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2025/07/01 20:48:48 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_info(char *err, t_philo_info *info, void *result)
{
	int		id;

	if (err != NULL)
		printf("%s", err);
	if (info != NULL && info->valid)
	{
		id = 0;
		info->valid = false;
		while (id < info->amount && info->philo_lst[id] != NULL)
		{
			mutex_lock(info->philo_lst[id]->m_ended);
			info->philo_lst[id]->ended = true;
			mutex_unlock(info->philo_lst[id]->m_ended, false);
			mutex_unlock(info->philo_lst[id]->m_fork, false);
			id++;
		}
		usleep(1000);
		free_philos(info);
		mutex_unlock(info->m_print, true);
		mutex_unlock(info->m_ready, true);
		free(info);
	}
	return (result);
}

bool	print_end_msg(char *msg, t_philo_info *info, t_philo *philo)
{
	int	id;
	int	ms;

	id = 0;
	if (philo != NULL)
	{
		id = philo->id;
		mutex_unlock(philo->m_ended, false);
		mutex_unlock(philo->m_meal, false);
	}
	ms = get_current_ms(info);
	free_info(NULL, info, NULL);
	if (philo != NULL)
		printf(msg, ms, id);
	else
		printf(msg, ms);
	return (false);
}

bool	check_eat_times(t_philo_info *info)
{
	int	id;
	int	ended;

	id = 0;
	ended = 0;
	while (id < info->amount)
	{
		mutex_lock(info->philo_lst[id]->m_ended);
		if (info->philo_lst[id]->ended)
			ended++;
		mutex_unlock(info->philo_lst[id]->m_ended, false);
		id++;
	}
	if (ended != info->amount)
		return (true);
	return (print_end_msg(ALL_SURVIVED, info, NULL));
}

bool	watcher_routine(t_philo_info *info)
{
	int		id;
	t_philo	*philo;
	int		ms;

	id = 0;
	while (id < info->amount)
	{
		philo = info->philo_lst[id];
		mutex_lock(philo->m_meal);
		mutex_lock(philo->m_ended);
		ms = get_current_ms(info);
		if ((ms - philo->last_meal) > info->die_time && !philo->ended)
			return (print_end_msg(PHILO_DIED, info, philo));
		mutex_unlock(philo->m_ended, false);
		mutex_unlock(philo->m_meal, false);
		id++;
	}
	if (info->eat_num > 0)
		return (check_eat_times(info));
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	info = parse_arguments(argc, argv);
	if (info == NULL)
		return (1);
	info = build_philosophers(info);
	if (info == NULL)
		return (2);
	while (watcher_routine(info))
		usleep(1000);
	return (0);
}
