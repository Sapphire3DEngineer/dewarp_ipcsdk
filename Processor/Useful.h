

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}


template <class T> void SafeDelete(T **ppT)
{
	if (*ppT)
	{
		delete (*ppT);
		*ppT = NULL;
	}
}


template <class T> void SafeDeleteArray(T **ppT)
{
	if (*ppT)
	{
		delete[](*ppT);
		*ppT = NULL;
	}
}


#define CHECK_HR(hr) if (FAILED(hr)) { goto done; }
