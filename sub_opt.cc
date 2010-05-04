/*
 * Sub_opt.cpp
 *
 *  Created on: 29-sep-2009
 *      Author: mayte
 */

#include "sub_opt.hh"


void CalculateEstimationEIFnn(Matrix Fk, Matrix Nk, Matrix &x, Matrix &P){

	P = !Fk;
	x = P * Nk;

	for (unsigned int i = 0; i < x.RowNo(); i++)
		x(i,0) *= -1;
}

void EIFnn(Matrix H, Matrix G, Matrix h, Matrix S, Matrix &F, Matrix &N){

	Matrix R = ~H * !(G * S * ~G);

	F = R * H;
	N = R * h;
}
