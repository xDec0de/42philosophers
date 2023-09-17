/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2023/09/17 21:07:03 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include "philosopher.h"
# include "text_colors.h"

// Struct used to store program information such as parameters and philosophers
typedef struct s_philo_info {
	int		amount;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_num;
	t_philo	philo_lst[MAX_PHILOSOPHERS];
}				t_philo_info;

/* Error messages */

// Invalid argument count.
# define ARGC_ERR RED"Error"B_GRAY": "B_RED"Invalid input\
"B_GRAY"."RESET"\n"
// Invalid amount of philosophers.
# define AMOUNT_ERR RED"Error"B_GRAY": "B_RED"Invalid number\
 of philosophers "B_GRAY"("B_YELLOW"Max is %d"B_GRAY")"RESET"\n"
// Warn philosophers over 200 if a higher amount is allowed.
# define AMOUNT_WARN YELLOW"Warning"B_GRAY": "B_YELLOW"Using over\
 200 philosophers is not recommended"B_GRAY"."RESET"\n"
// Invalid time to die.
# define DIE_TIME_ERR RED"Error"B_GRAY": "B_RED"Invalid time\
 to die"B_GRAY"."RESET"\n"
// Invalid time to eat.
# define EAT_TIME_ERR RED"Error"B_GRAY": "B_RED"Invalid time\
 to eat"B_GRAY"."RESET"\n"
// Invalid time to sleep.
# define SLEEP_TIME_ERR RED"Error"B_GRAY": "B_RED"Invalid time\
 to sleep"B_GRAY"."RESET"\n"
// Invalid amount of times to eat.
# define EAT_NUM_ERR RED"Error"B_GRAY": "B_RED"Invalid amount\
 of times to eat"B_GRAY"."RESET"\n"
// Error creating a thread.
# define THREAD_ERR RED"Error"B_GRAY": "B_RED"Could not create\
 a new thread"B_GRAY"."RESET"\n"

/* Debug messages, debug should be disabled on evaluation just in case */

# define DEBUG_NOTE B_WHITE"Debug "B_GREEN"enabled"B_WHITE", run\
 "B_YELLOW"make re DEBUG=0 "B_WHITE"to disable"B_GRAY"."RESET"\n"
# define INFO_HEADER "\n"WHITE"|-------------------------->"RESET"\n"
# define INFO_NUM B_RED"* "B_WHITE"%s"B_GRAY": "YELLOW"%d"RESET"\n"
# define INFO_FOOTER WHITE"|-------------------------->"RESET"\n\n"

/* Philosopher log messages */

// Invalid time to die.
# define PHILO_TAKE_RFORK B_GRAY"["YELLOW"%d"B_GRAY"] "B_YELLOW"%d "B_WHITE"\
has taken a "B_YELLOW"fork "B_GRAY"("B_BLUE"Right"B_GRAY")"RESET"\n"
// Invalid time to die.
# define PHILO_TAKE_LFORK B_GRAY"["YELLOW"%d"B_GRAY"] "B_YELLOW"%d "B_WHITE"\
has taken a "B_YELLOW"fork "B_GRAY"("B_BLUE"Left"B_GRAY")"RESET"\n"
// Invalid time to die.
# define PHILO_EATING B_GRAY"["YELLOW"%d"B_GRAY"] "B_YELLOW"%d "B_WHITE"\
is "B_MAGENTA"meating"B_GRAY"."RESET"\n"
// Invalid time to die.
# define PHILO_SLEEPING B_GRAY"["YELLOW"%d"B_GRAY"] "B_YELLOW"%d "B_WHITE"\
is "B_CYAN"sleeping"B_GRAY"."RESET"\n"
// Invalid time to die.
# define PHILO_THINKING B_GRAY"["YELLOW"%d"B_GRAY"] "B_YELLOW"%d "B_WHITE"\
is "B_GREEN"thinking"B_GRAY"."RESET"\n"
// Invalid time to die.
# define PHILO_DIED B_GRAY"["RED"%d"B_GRAY"] "B_RED"%d \
died"B_GRAY"."RESET"\n"

/* philosophers.c */

void			exit_error(char *err, t_philo_info *info);

/* input_parser.c */

t_philo_info	*parse_arguments(int argc, char **argv);

/* philo_builder.c */

t_philo_info	*build_philosophers(t_philo_info *info);

#endif