/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:47:13 by danimart          #+#    #+#             */
/*   Updated: 2022/06/24 16:45:13 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>

# define ARGC_ERR "\e[0;31mError\e[1;30m: \e[0;31mInvalid input\
\e[1;30m.\e[0m\n"
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[0;31mInvalid number\
 of philosophers\e[1;30m.\e[0m\n"
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[0;31mInvalid time\
 to die\e[1;30m.\e[0m\n"
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[0;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[0;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"

typedef struct s_philo_info {
	int	amount;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	eat_num;
}				t_philo_info;

// philosophers.c
void			*print_error(char *err, void *ret);

// input_parser.c
t_philo_info	*parse_arguments(int argc, char **args);

#endif