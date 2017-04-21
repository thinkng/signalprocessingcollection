//Original codes: http://www.bragitoff.com/2015/09/c-program-for-polynomial-fit-least-squares/


double* Polyfit(double* pX, double* pY, int nDataSize, int nDegree, float* pPivotX, float* pPivotY, int nPivot)
{
	int i, j, k;
	int n = nDegree;
	int N = nDataSize+nPivot*2;
	double* x; x = new double[N];
	double* y; y = new double[N];
	
	if (pX==NULL || pY==NUL) return NULL;	

	//Data acquire
	
	for (i = 0; i < nPivot; i++)
	{
		x[i] = pPivotX[i];
		y[i] = pPivotY[i];
	}
	for (i = nPivot; i < N - nPivot; i++)
	{
		x[i] = m_pROIX[pIndex[i - nPivot]];
		y[i] = m_pROIY[pIndex[i - nPivot]];
	}
	for (i = N - nPivot; i < N; i++)
	{
		x[i] = pPivotX[2 *nPivot- (N-i)];
		y[i] = pPivotY[2 * nPivot - (N - i)];
	}	
		
	double* X; X = new double[2 * n + 1];	   //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	for (i = 0; i<2 * n + 1; i++)
	{
		X[i] = 0;
		for (j = 0; j<N; j++)
			X[i] = X[i] + pow(x[j], i);        //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	}
	double** B; B = new double*[n + 1];		  //B is the Normal matrix(augmented) that will store the equations
	for (i = 0; i < n + 1; i++)
		B[i] = new double[n + 2];
	double* a; a = new double[n + 1];		  // 'a' is for value of the final coefficients
	for (i = 0; i <= n; i++)
	for (j = 0; j <= n; j++)
		B[i][j] = X[i + j];					  //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
	double* Y; Y = new double[n + 1];		  //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	for (i = 0; i<n + 1; i++)
	{
		Y[i] = 0;
		for (j = 0; j<N; j++)
			Y[i] = Y[i] + pow(x[j], i)*y[j];  //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	}
	for (i = 0; i <= n; i++)
		B[i][n + 1] = Y[i];					//load the values of Y as the last column of B(Normal Matrix but augmented)
	n = n + 1;								//n is made n+1 because the Gaussian Elimination part below was for n equations, but here n is the degree of polynomial and for n degree we get n+1 equations
	for (i = 0; i<n; i++)                    //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)
	for (k = i + 1; k<n; k++)
	if (B[i][i]<B[k][i])
	for (j = 0; j <= n; j++)
	{
		double temp = B[i][j];
		B[i][j] = B[k][j];
		B[k][j] = temp;
	}

	for (i = 0; i<n - 1; i++)             //loop to perform the gauss elimination
	for (k = i + 1; k<n; k++)
	{
		double t = B[k][i] / B[i][i];
		for (j = 0; j <= n; j++)
			B[k][j] = B[k][j] - t*B[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
	}
	for (i = n - 1; i >= 0; i--)                //back-substitution
	{                         //x is an array whose values correspond to the values of x,y,z..
		a[i] = B[i][n];                //make the variable to be calculated equal to the rhs of the last equation
		for (j = 0; j<n; j++)
		if (j != i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
			a[i] = a[i] - B[i][j] * a[j];
		a[i] = a[i] / B[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}	

	delete x, y, X, Y, B;
	return a;
}