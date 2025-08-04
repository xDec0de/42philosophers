/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:11:36 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/04 17:41:16 by daniema3         ###   ########.fr       */
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
		mutex_free(info->philo_lst[id]->m_last_meal_ms);
		mutex_free(info->philo_lst[id]->m_fork);
		free(info->philo_lst[id]);
		info->philo_lst[id] = NULL;
		id++;
	}
}

void	free_info(t_philo_info *info)
{
	free_philos(info);
	mutex_free(info->m_print);
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
	info->start_date = 0;
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
