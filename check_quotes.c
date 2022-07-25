	int i;
	int j;
    int counter34;
    int counter39;

	i = 0;
	j = ft_strlen(s) - 1;
    while(i < j)
    {
        if (s[i] == 39)
        {
            counter39 += 1;
            while(i < j)
            {
                if (s[j] == 39)
                {
                    j--;
                    counter39 += 1;
                    break;
                }
                else if (s[j] == 34)
                    return(0);
                j--;
            }
        }
        else if (s[i] == 34)
        {
            counter34 += 1;
            while(i < j)
            {
                if (s[j] == 34)
                {
                    j--;
                    counter34 += 1;
                    break;
                }
                else if (s[j] == 39)
                    return(0);
                j--;
            }
        }
        i++;
    }
    if ((counter34 % 2) || (counter39 % 2))
		return(0);
	else
		return(1);
    return (1);