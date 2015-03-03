void build_predicting_analysis_table()
{
	int i = 0 , j = 0 ;
	for(i = 0 ; i < 20 ; i++)
	{
		for(j = 0 ; j < 32 ; j++)
		{
			TABLE[i][j] = -1;
		}
	}
	TABLE[0][0]	 = 3;
	TABLE[0][1]	 = 3;
	TABLE[0][2]	 = 3;
	TABLE[0][31] = 5;

	TABLE[1][3]	 = 5;
	TABLE[1][4]  = 4;
	TABLE[1][5]	 = 4;

	TABLE[2][]
}

/*
 * E	0
 * E'	1
 * T	2
 * T'	3
 * Bop1	4
 * Bop2	5
 * F	6
 * B	7
 * B'	8
 * S	9
 * Relop10
 * ELS	11
 * L	12
 * Elist13
 * ARRAY14
 * P	15
 * TYPE	16
 * A	17
 * FUNC	18
 *
 * id	0
 * d	1
 * (	2
 * )	3
 * +	4
 * -	5
 * *	6
 * /	7
 * %	8
 * !	9
 * &	10
 * |	11
 * if	12
 * while13
 * return 14
 * else 15
 * elsif16
 * {	17
 * }	18
 * [	19
 * ]	20
 * =	21
 * ==	22
 * >	23
 * <	24
 * >=	25
 * <=	26
 * num	27
 * string 28
 * void	29
 * call 30
 * #	31
 */

