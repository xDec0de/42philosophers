/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/10/11 17:23:19 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo_info	*print_info(t_philo_info *info)
{
	if (!DEBUG || info == NULL)
		return (info);
	printf(INFO_HEADER);
	printf(INFO_INT, "Philosopher amount", info->amount);
	printf(INFO_LONG, "Time to die", info->die_time);
	printf(INFO_INT, "Time to eat", info->eat_time);
	printf(INFO_INT, "Time to sleep", info->sleep_time);
	if (info->eat_num == 0)
		printf(INFO_STR, "Times to eat", "unlimited");
	else
		printf(INFO_INT, "Times to eat", info->eat_num);
	printf(INFO_FOOTER);
	return (info);
}

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
			mutex_lock(info->philo_lst[id]->m_dead);
			info->philo_lst[id]->dead = 1;
			mutex_unlock(info->philo_lst[id]->m_dead, 0);
			mutex_unlock(info->philo_lst[id]->m_fork, 0);
			id++;
		}
		usleep(100);
		id = 0;
		while (id < info->amount && info->philo_lst[id] != NULL)
			id += free_philo(info->philo_lst[id]);
		mutex_unlock(info->m_print, 1);
	}
	return (result);
}

int	print_end_msg(char *msg, t_philo_info *info, int id)
{
	free_info(NULL, info, NULL);
	printf(msg, get_current_ms(info), id);
	return (0);
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
		if (info->eat_num > 0 && philo->meals >= info->eat_num)
		{
			mutex_unlock(philo->m_meal, 0);
			return (print_end_msg(PHILO_SURVIVED, info, id));
		}
		else if ((get_current_ms(info) - philo->last_meal) > info->die_time)
		{
			mutex_unlock(philo->m_meal, 0);
			return (print_end_msg(PHILO_DIED, info, id));
		}
		mutex_unlock(philo->m_meal, 0);
		id++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

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
	free(info);
	return (0);
}
