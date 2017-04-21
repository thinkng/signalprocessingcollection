
double InterpolateY(int nDegree, double* dCoeff, double dX)
{
	double dRet=0.0;
	for (int i = 0; i < nDegree+1; i++)
	{
		dRet += dCoeff[i] * pow(dX, (double)i);
	}
	return dRet;
}