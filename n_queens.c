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

void writeit (char **board, int nb, int *sol)
{
    int i;
    int j;
	// i = 0;
	// while (i < nb)
	// {
	// 	j = 0;
	// 	while (j < nb)
	// 		printf ("%c ", board[i][j++]);
	// 	printf ("\n");
	// 	i++;
	// }
	// printf ("\n");
	// i = 0;
    // while (i < nb)
    // {
	// 	j = 0;
	// 	while (j < nb)
	// 	{
	// 		if (board[i][j] == '1')
	// 		{
	// 			printf ("%d,", j);
	// 			break;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
    // }
	// printf ("\n");
	*sol += 1;
	myputnbr (*sol);
	myputstr ("\n");
	return; 
}

void is_valid(char **board, int start, int nb, int *sol)
{
	int i;
	int j;
	if (start == nb)
		return ;
	int pos = 0;
	// search for the index of the queens position for this line
	while (pos < nb)
	{
		if (board[start][pos] == '1')
			break;
		pos ++;
	}
	i = 0;
	// -->
	while (i < nb)
	{
		if (board[start][i] == '1' && i != pos)
			return ;
		i++;
	}
	i = 0;
	// ||
	// ||
	// \/
	while (i < nb)
	{
		if (board[i][pos] == '1' && i != start)
			return ;
		i++;
	}
	i = start;
	j = pos;
	// .
	//  .
	//   .
	//    .
	//     *
	while (i < nb && j < nb)
	{
		if (i != start && j != pos && board[i][j] == '1')
			return ;
		i++;
		j++;
	}
	i = start;
	j = pos;
	// *
	//  .
	//   .
	//    .
	//     .
	while (i > -1 && j > -1)
	{
		if (i != start && j != pos && board[i][j] == '1')
			return ;
		i--;
		j--;
	}
	i = start;
	j = pos;
	//      .
	//     .
	//    .
	//   .
	//  .
	// *
	while (i < nb && j > -1)
	{
		if (i != start && j != pos && board[i][j] == '1')
			return ;
		i++;
		j--;
	}
	i = start;
	j = pos;
	//      *
	//     .
	//    .
	//   .
	//  .
	// .
	while (i > -1 && j < nb)
	{
		if (i != start && j != pos && board[i][j] == '1')
			return ;
		i--;
		j++;
	}
	// increment the line only if its not the last line, otherwise it will reach writeit function
	if (start + 1 < nb)
	{
		start ++;
		is_valid(board, start, nb, sol);
		return ;
	}
	writeit(board, nb, sol);
	return ;
}

int last_dance(char **board, int nb)
{
	int i = 0;
	int j;
	while (i < nb)
	{
		j = 0;
		while (j < nb)
		{
			if (board[i][j] == '0' && j == nb - 1)
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

int move_on(char **board, int line, int nb)
{
	int i = 0;
	while (i < nb)
	{
		if (board[line][i] == '1')
		{
			if (i == nb - 1)
			{
				if (line == nb - 1)
					return -1;
				board[line][i] = '0';
				board[line][0] = '1';
				if (line != nb - 1)
				{
					line ++;
					move_on(board, line, nb);
					return 1;
				}
			}
			else
			{
				board[line][i++] = '0';
				board[line][i] = '1';
			}
			return 1;
		}
		i ++;
	}
	return 1;
}

void startit(char **board, int nb, int *sol)
{
	while (1)
	{
		if (last_dance(board, nb))
			return ;
		is_valid(board, 0, nb, sol);
		if (move_on(board, 0, nb) == -1)
			return ;
	}
    return ;
}

void set_up(char **board, int nb)
{
	int i = 0;
    int j;
    while (i < nb)
    {
        j = 0;
        while (j < nb)
		{
			if (j == 0)
				board[i][j++] = '1';
			else
				board[i][j++] = '0';
		}
        i ++;
    }
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
    char **board;
	board = (char **) malloc (sizeof(char *) * (nb + 1));
	if (board == NULL)
	{
		myputstr ("board alloaction failed\n");
		return 1;
	}
	while (i < nb)
	{
		board[i] = (char *) malloc (sizeof(char) * (nb + 1));
		if (board[i] == NULL)
		{
			myputstr ("board ind alloaction failed\n");
			return 1;
		}
		i++;
	}
	board[i] = NULL;
	set_up(board, nb);
	startit(board, nb, &sol);
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
