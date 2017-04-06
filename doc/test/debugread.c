/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:16:41 by dogokar           #+#    #+#             */
/*   Updated: 2017/04/03 20:17:16 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void init_termios(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, &term);
}

int main (int ac, char **av)
{
	int rt = 0;
	int douggydrog = 1;

	if (!isatty(0))
	{
			printf("The input is not from the terminal\n");
			return (0);
	}
	system("man ascii | tail -24 | head -16");
	init_termios();
	while (douggydrog)
	{
		rt = 0;
		read(0, &rt, sizeof(int));
		if (rt >= 32 && rt <= 126)
			printf("Key [%c] ", (char)rt);
		printf("RAW [%d] Hexa [0x%08.8x]\n", rt, rt);
		if (rt == 27)
			break ;
	}
	return (0);
}
