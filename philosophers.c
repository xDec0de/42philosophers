/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/10/16 01:47:33 by danimart         ###   ########.fr       */
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
		free(info);
	}
	return (result);
}

int	print_end_msg(char *msg, t_philo_info *info, t_philo *philo)
{
	int	id;

	id = 0;
	if (philo != NULL)
	{
		id = philo->id;
		mutex_unlock(philo->m_ended, 0);
		mutex_unlock(philo->m_meal, 0);
	}
	free_info(NULL, info, NULL);
	if (philo != NULL)
		printf(msg, get_current_ms(info), id + 1);
	else
		printf(msg, get_current_ms(info));
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
	int			id;
	t_philo		*philo;

	id = 0;
	while (id < info->amount)
	{
		philo = info->philo_lst[id];
		mutex_lock(philo->m_meal);
		mutex_lock(philo->m_ended);
		if (info->eat_num > 0 && philo->meals >= info->eat_num)
			philo->ended = 1;
		else if ((get_current_ms(info) - philo->last_meal) > info->die_time && philo->ended != 0)
			return (print_end_msg(PHILO_DIED, info, philo));
		mutex_unlock(philo->m_ended, 0);
		mutex_unlock(philo->m_meal, 0);
		id++;
	}
	if (info->eat_num > 0)
		return (check_eat_times(info));
	return (1);
}

void	leaks(void)
{
	system("leaks -s philo");
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	atexit(leaks);
	if (DEBUG)
		printf("\n"DEBUG_NOTE);
	info = print_info(parse_arguments(argc, argv));
	if (info == NULL)
		return (1);
	info = build_philosophers(info);
	if (info == NULL)
		return (2);
	while (watcher_routine(info))
		usleep(50);
	return (0);
}
