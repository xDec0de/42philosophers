/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:11:36 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/31 15:26:45 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_philos(t_philo_info *info)
{
	int	id;

	id = 0;
	while (id < info->philo_n && info->philo_lst[id] != NULL)
	{
		pthread_join(info->philo_lst[id]->thread_id, NULL);
		id++;
	}
	id = 0;
	while (id < info->philo_n && info->philo_lst[id] != NULL)
	{
		free(info->philo_lst[id]);
		info->philo_lst[id] = NULL;
		id++;
	}
}

void	free_info(t_philo_info *info)
{
	pthread_mutex_unlock(info->m_print);
	pthread_mutex_destroy(info->m_print);
	free(info->m_print);
	free_philos(info);
	free(info);
}

static t_philo_info	*init_info(void)
{
	t_philo_info	*info;
	int				id;

	info = malloc(sizeof(t_philo_info));
	if (info == NULL)
	{
		printf(MALLOC_ERR);
		return (NULL);
	}
	id = 0;
	while (id < MAX_PHILOSOPHERS)
	{
		info->philo_lst[id] = NULL;
		id++;
	}
	info->philo_n = 0;
	info->die_ms = 0;
	info->eat_ms = 0;
	info->sleep_ms = 0;
	info->m_print = mutex_init();
	if (info->m_print == NULL)
		return (NULL);
	return (info);
}

t_philo_info	*get_info(void)
{
	static t_philo_info	*info = NULL;

	if (info == NULL)
		info = init_info();
	return (info);
}
