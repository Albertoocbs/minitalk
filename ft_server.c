/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:32:02 by aoutumur          #+#    #+#             */
/*   Updated: 2025/02/27 11:39:49 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
- Reçoi le signal,le traite & garde l'info entre appels jusqua arriver a 8 bi
- bit_received = compteur bits recus
- i = ou stcoker les bits recus
- i = (i << 1) | 1; decale a gauche tous les bits 1 fois.Fait la place aux nouv
- et place le bit recu a la fin
- reset les variables pour le prochain caractere
- Stock client PID pour le reconaitre
*/
static void	ft_signal_handler(int signal)
{
	static int				bit_received = 0;
	static unsigned char	i = 0;

	if (bit_received > 8 || i < 0)
	{
		bit_received = 0;
		i = 0;
	}
	if (signal == SIGUSR1)
		i = ((i << 1) | 1);
	else if (signal == SIGUSR2)
		i = (i << 1);
	bit_received++;
	if (bit_received == 8)
	{
		if (i == '\0')
			write(1, "\n", 1);
		else
			write(1, &i, 1);
		bit_received = 0;
		i = 0;
	}
}

/* Print le pid du serveur. Recoi le signal et appel la fonction handler pour
obtenir chaque bit a chaque appel et chaque caractere une fois 8 bits recu
jusqua avoir recu toute la chaine passe en argument dans ./client
- ft_bzero(&sa, sizeof(sa)); initialise a 0 la structure
- sigemptyset(&sa.sa_mask); assure quil ny a pas de masks dancienns signaux
*/
int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	ft_printf("Waiting for message...\n");
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ft_signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
