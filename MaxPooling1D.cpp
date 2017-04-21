int* MaxPooling1D(float* pInput, int nInputSize, int nWindowSize, int nStrike) //return indices of Pooled Array
{
	int* pRet;
	
	int nStartPoint = 0, nEndPoint;
	int nPool1Dcount = round ((nInputSize - nWindowSize) / nStrike + 1 + 0.5);
	pRet = new int[nPool1Dcount] 

	float fMax;
	int nMaxIndex;
	int nPoolCount = 0;
	while (nStartPoint<m_nDropCount-nStrike)
	{
		nEndPoint = nStartPoint + nWindowSize;
		if (nEndPoint>m_nDropCount)
			nEndPoint = m_nDropCount;
		fMax = 0.f;
		nMaxIndex = 0;
		for (int i = nStartPoint; i < nEndPoint; i++)
		{
			if (pInput[i]>fMax)
			{
				fMax = pInput[i];
				nMaxIndex = pIndex[i];
			}
		}
		pRet[nPoolCount] = nMaxIndex;
		nPoolCount++;
		nStartPoint += nStrike;
	}	

	return pRet;
}