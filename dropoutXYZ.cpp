
int* DropOutXYZ(float* pInput, int nDataSize, float fRatio, float fThres) //return indices of Dropped Array
{
	int nInputSize = m_nROICount;
	int* pThresDim = new int[nInputSize];
	memcpy(pThresDim, pInput, nDataSize*sizeof(byte));
	
	int	nStep = (int)(1/fRatio);
	int i = 0;
	int nOutIndex = 0;
	while (i<nInputSize)
	{
		if (pThresDim[i]>fThres)
		{
			nOutIndex++;			
		}
		i += nStep;
	}

	int* ret = new int[m_nDropCount];	

	nOutIndex = 0;
	i = 0;
	while (i<nInputSize)
	{
		if (pThresDim[i]>fThres)
		{
			ret[nOutIndex] = i;			
			nOutIndex++;
			if (nOutIndex > m_nDropCount)
				AfxMessageBox("Out of index range! ExStackingImg/DropOutXYZ");
		}
		i += nStep;
	}

	delete pThresDim;
	return ret;		
}
