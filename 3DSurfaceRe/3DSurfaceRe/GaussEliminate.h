#ifndef GAUSSELIMINATE_H
#define GAUSSELIMINATE_H

#include <math.h>

#pragma once
class CGaussEliminate
{
public:
	CGaussEliminate(void);
	~CGaussEliminate(void);
	void Eliminate(double **, double *, int );
	void Rewind(double **, double *, double *, int);
	void aa();
};

#endif