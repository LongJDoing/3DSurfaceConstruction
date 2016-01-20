#pragma once
class CMy1DMorphology
{
public:
	CMy1DMorphology(void);
	~CMy1DMorphology(void);
	void OneDDilation(int *, int);
	void OneDErosion(int *, int);
	void OneDOpening(int *, int);
	void OneDClosing(int *, int);
};

