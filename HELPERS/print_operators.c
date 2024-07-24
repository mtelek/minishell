void print_operators(t_operator *operators)
{
	while (operators != NULL)
	{
		printf("Operator sign:%s\n", operators->operator);
		printf("Operator name:%s\n", operators->name);
		operators = operators->next;
	}
}


void	qoutes_checker(char *input, char check)
{
	int i;
	int n_quotes;

	i = 0;
	n_quotes = 0;
	while (input[i] != "\0")
	{
		if (intput[i] == check)
			n_qoutes++;
		i++;
	}
}