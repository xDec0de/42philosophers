/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2025/07/01 19:30:25 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	*free_info(char *err, t_philo_info *info, void *result)
{
	int		id;

	if (err != NULL)
		printf("%s", err);
	if (info != NULL && info->valid == 1)
	{
		id = 0;
		info->valid = 0;
		while (id < info->amount && info->philo_lst[id] != NULL)
		{
			mutex_lock(info->philo_lst[id]->m_ended);
			info->philo_lst[id]->ended = 1;
			mutex_unlock(info->philo_lst[id]->m_ended, 0);
			mutex_unlock(info->philo_lst[id]->m_fork, 0);
			id++;
		}
		usleep(1000);
		free_philos(info);
		mutex_unlock(info->m_print, 1);
		mutex_unlock(info->m_ready, 1);
		free(info);
	}
	return (result);
}

int	print_end_msg(char *msg, t_philo_info *info, t_philo *philo)
{
	int	id;
	int	ms;

	id = 0;
	if (philo != NULL)
	{
		id = philo->id;
		mutex_unlock(philo->m_ended, 0);
		mutex_unlock(philo->m_meal, 0);
	}
	ms = get_current_ms(info);
	free_info(NULL, info, NULL);
	if (philo != NULL)
		printf(msg, ms, id);
	else
		printf(msg, ms);
	return (0);
}

int	check_eat_times(t_philo_info *info)
{
	int	id;
	int	ended;

	id = 0;
	ended = 0;
	while (id < info->amount)
	{
		mutex_lock(info->philo_lst[id]->m_ended);
		if (info->philo_lst[id]->ended == 1)
			ended++;
		mutex_unlock(info->philo_lst[id]->m_ended, 0);
		id++;
	}
	if (ended != info->amount)
		return (1);
	return (print_end_msg(ALL_SURVIVED, info, NULL));
}

int	watcher_routine(t_philo_info *info)
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
		if ((ms - philo->last_meal) > info->die_time && philo->ended != 1)
			return (print_end_msg(PHILO_DIED, info, philo));
		mutex_unlock(philo->m_ended, 0);
		mutex_unlock(philo->m_meal, 0);
		id++;
	}
	if (info->eat_num > 0)
		return (check_eat_times(info));
	return (1);
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
		usleep(100);
	return (0);
}
