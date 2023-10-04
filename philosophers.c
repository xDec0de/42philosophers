/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:15 by danimart          #+#    #+#             */
/*   Updated: 2023/10/04 17:47:21 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	*free_info(char *err, t_philo_info *info, void *result)
{
	if (err != NULL)
		printf("%s", err);
	if (info != NULL)
	{
		info->valid = 0;
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
	info = parse_arguments(argc, argv);
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
