#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int mystrlen(char *str)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void myputchar(char c)
{
	write (1, &c, 1);
}

void myputstr(char *str)
{
	write (1, str, mystrlen(str));
}

void	myputnbr(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			myputstr("-2147483648");
			return ;
		}
		myputchar('-');
		n = -n;
	}
	if (n / 10)
	{
		myputnbr(n / 10);
		myputnbr(n % 10);
	}
	else
		myputchar('0' + n);
}

int full_line(char *buffer)
{
    int i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            return 1;
        i++;
    }
    return 0;
}

int myatoi(char *str)
{
	int i = 0;
	int sign = 1;
	int nb = 0;

	if (str[i] == '\n')
	{
		myputstr ("empty string\n");
		exit(1);
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
	{
		myputstr ("no number\n");
		exit(1);
	}
	while (str[i] && str[i] != '\n')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			myputstr ("invalid nb\n");
			exit(1);
		}
		nb = (nb * 10) + (str[i++] - 48);
	}
	return nb * sign;
}

void writeit (int *sol, int *range, int nb)
{
	*sol += 1;
	myputnbr (*sol);
	myputstr ("\n");
	int i = 0;
	while (i < nb)
	{
		myputnbr (range[i++]);
		myputstr (",");
	}
	myputstr ("\n");
	return; 
}

int x_dire(int *range, int nb, int head, int cur)
{
	int i = 0;
	int pos = cur - head;
	if (head > cur)
	{
		pos = 0;
		i = head - cur;
	}
	while (i < head)
	{
		if (range[i] == pos)
			return 1;
		i++;
		pos++;
	}
	if (cur == nb - 1)
		return 0;
	head--;
	pos ++;
	while (pos < nb && head >= 0)
	{
		if (range[head] == pos)
			return 1;
		head--;
		pos++;
	}
	return 0;
}

int	sameline(int *range, int head, int cur)
{
	int i = 0;
	while (i < head)
	{
		if (range[i] == cur)
			return 1;
		i++;
	}
	return 0;
}

void set_up(int head, int *range, int nb, int *sol)
{
	if (head == nb)
		return ;
	int i = 0;
	while (i < nb)
	{
		if (head == 0)
		{
			range[head] = i;
			set_up(head + 1, range, nb, sol);
		}
		else
		{
			if (sameline(range, head, i) == 1)
			{
				i++;
				continue;
			}
			else if (x_dire(range, nb, head, i))
			{
				i++;
				continue;
			}
			range[head] = i;
			if (head == nb - 1)
				writeit(sol, range, nb);
			set_up(head + 1, range, nb, sol);
		}
		i++;
	}
	return;
}

void teenqueens(char *input)
{
	int sol = 0;
	int nb;
	sol = 0;
    nb = myatoi(input);
	if (nb < 0)
	{
		myputstr ("not a positive nb\n");
		return ;
	}
	if (nb < 4)
	{
		if (nb == 1)
		{
			myputstr ("1\n");
			myputstr ("solutions are : 1\n");
			return ;
		}
		myputstr ("no solution\n");
		return ;
	}
    int range[nb];
	range[0] = -1;
	set_up(0, range, nb, &sol);
	return ;
}

int main (int ac, char **av)
{
	if (ac != 2)
	{
		myputstr("the number of arguments isnt valid\n");
		return 1;
	}
	teenqueens(av[1]);
}
