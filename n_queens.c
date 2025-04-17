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
// int x_dire(int *(0, 2, ..), int 4, int 2, int 1)
{
	int i = 0;
	int pos = cur - head;
	if (head > cur)
	{
		pos = 0;
		i = head - cur;
	}
	// i = 1
	while (i < head)
	{
		if (range[i] == pos)
			return 1;
		i++;
		pos++;
	}
	if (cur == nb - 1)
	{
		if (head == 2)
			myputstr("mara min hona\n");
		return 0;
	}
	head--;
	pos += 2;
	while (pos < nb && head <= 0)
	{
		if (range[i] == pos)
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
	myputstr("check\n");
	if (head == nb)
	{
		myputstr("head equals nb\n");
		return ;
	}
	myputstr("setup\n");
	int i = 0;
	while (i < nb)
	{
		myputstr("while, i = ");
		myputnbr(i);
		myputstr(", head = ");
		myputnbr(head);
		myputstr("\n");
		if (head == 0)
		{
			myputstr("head is 0\n");
			head++;
			range[0] = head;
			i++;
			set_up(head, range, nb, sol);
			myputstr("lhna\n");
			continue;
		}
		if (sameline(range, head, i) == 1)
		{
			myputstr("same line\n");
			myputstr("i++\n");
			i++;
			continue;
		}
		else if (x_dire(range, nb, head, i))
		{
			myputstr("x_dire\n");
			myputstr("i++\n");
			i++;
			continue;
		}
		myputstr("set range\n");
		range[head] = i;
		if (head == nb - 1)
		{
			myputstr("write\n");
			writeit(sol, range, nb);
			i++;
			continue;
		}
		head++;
		myputstr("go again\n");
		set_up(head, range, nb, sol);
		i++;
	}
	myputstr("raje rjae\n");
	return;
}

int teenqueens(char *str)
{
	int sol;
	int nb;
	sol = 0;
    nb = myatoi(str);
	if (nb < 0)
	{
		myputstr ("not a positive nb\n");
		return -1;
	}
	if (nb < 4)
	{
		if (nb == 1)
		{
			myputstr ("1\n");
			return 1;
		}
		return 0;
	}
	int i = 0;
    int *range;
	range = malloc (sizeof(int) * nb);
	if (!range)
	{
		myputstr("range failed\n");
		return 1;
	}
	range[0] = -1;
	set_up(0, range, nb, &sol);
	return sol;
}

char *gnl(int fd)
{
    char *str = NULL;
    char *readd = NULL;
    char *buffer = NULL;
    char *tmp = NULL;
    int i;
    int j;
    int r;
    int buffer_size = 1;
    while (1)
    {
        readd = malloc (buffer_size + 1);
        if (!readd)
        {
            myputstr ("readd allocation failed\n");
            return NULL;
        }
        r = read (fd, readd, buffer_size);
        if (r == -1)
        {
            myputstr ("r == -1\n");
            return NULL;
        }
        if (r == 0)
            break;
        readd[r] = 0;
        if (buffer)
            tmp = buffer;
        buffer = malloc (mystrlen(tmp) + mystrlen(readd) + 1);
        if (!buffer)
        {
            myputstr ("buffer alllcation failed \n");
            return NULL;
        }
        i = 0;
        if (tmp)
        {
            j = 0;
            while (tmp[j])
                buffer[i++] = tmp[j++];
        }
        j = 0;
        while (readd[j])
            buffer[i++] = readd[j++];
        buffer[i] = 0;
        free(tmp);
        free(readd);
        if (full_line(buffer) == 1)
            return buffer;
    }
    if (!buffer && r == 0)
        return NULL;
    return buffer;
}
int main ()
{
    char *str;
	int solutions;
    while (1)
    {
        str = gnl(0);
        if (!str)
            return 1;
        solutions = teenqueens(str);
		if (solutions == -1)
			return 1;
        myputstr("\nsolutions are : ");
        myputnbr(solutions);
        myputstr("\n");
    }

}
