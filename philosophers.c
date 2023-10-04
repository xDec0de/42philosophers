/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/10/04 19:23:45 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo_info	*print_info(t_philo_info *info)
{
	if (!DEBUG || info == NULL)
		return (info);
	printf(INFO_HEADER);
	printf(INFO_NUM, "Philosopher amount", info->amount);
	printf(INFO_NUM, "Time to die", info->die_time);
	printf(INFO_NUM, "Time to eat", info->eat_time);
	printf(INFO_NUM, "Time to sleep", info->sleep_time);
	if (info->eat_num == 0)
		printf(INFO_STR, "Times to eat", "unlimited");
	else
		printf(INFO_NUM, "Times to eat", info->eat_num);
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
		pthread_mutex_destroy(info->m_print);
		if (DEBUG)
			printf(DEBUG_PREFIX" Destroyed printf mutex.\n");
		while (id < info->amount && info->philo_lst[id] != NULL)
		{
			pthread_mutex_destroy(info->philo_lst[id]->m_state);
			pthread_detach(info->philo_lst[id]->th_id);
			if (DEBUG)
				printf(DEBUG_PREFIX" Destroyed philosopher %i.\n", id);
			id++;
		}
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

int	watcher_routine(t_philo_info *info)
{
	int		id;
	int		stop;
	t_philo	*philo;

	id = 0;
	stop = 1;
	while (id < info->amount && stop == 1)
	{
		philo = info->philo_lst[id];
		if (philo->state == DEAD)
		{
			printf(PHILO_DIED, get_current_ms(info), id);
			stop = 0;
		}
	}
	return (stop);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	//atexit(leaks);
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
