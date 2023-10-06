/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/10/06 20:52:06 by danimart         ###   ########.fr       */
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
			pthread_detach(info->philo_lst[id]->th_id);
			pthread_mutex_destroy(info->philo_lst[id]->m_state);
			pthread_mutex_destroy(info->philo_lst[id]->m_fork);
			pthread_mutex_destroy(info->philo_lst[id]->m_meal);
			id++;
		}
		pthread_mutex_destroy(info->m_print);
		pthread_mutex_destroy(info->m_ended);
		free(info);
	}
	return (result);
}

/**
 * @brief May cause segmentation faults and other errors, disable if any error
 * occurs to make sure this is not causing it.
 */
void	leaks(void)
{
	system("leaks philo | grep 'leaks for' | awk '$1 == \"Process\" {leaks = $3} END {printf(\"\e[0;31mLeaks\e[1;30m: \e[0;33m%d\e[0m\\n\"), leaks}'");
}

int	print_end_msg(char *msg, t_philo_info *info, u_int64_t ms, int id)
{
	pthread_mutex_lock(info->m_ended);
	info->ended = 1;
	pthread_mutex_unlock(info->m_ended);
	pthread_mutex_lock(info->m_print);
	printf(msg, ms, id);
	pthread_mutex_unlock(info->m_print);
	free_info(NULL, info, NULL);
	return (0);
}

int	watcher_routine(t_philo_info *info)
{
	int			id;
	t_philo		*philo;
	u_int64_t	c_ms;

	id = 0;
	c_ms = get_current_ms(info);
	while (id < info->amount)
	{
		philo = info->philo_lst[id];
		pthread_mutex_lock(philo->m_meal);
		if (info->eat_num > 0 && philo->meals >= info->eat_num)
			return (print_end_msg(PHILO_SURVIVED, info, c_ms, id));
		else if ((get_current_ms(info) - philo->last_meal) > info->die_time)
			return (print_end_msg(PHILO_DIED, info, c_ms, id));
		pthread_mutex_unlock(philo->m_meal);
		id++;
	}
	return (1);
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
		usleep(100);
	free_info(NULL, info, NULL);
	return (0);
}
