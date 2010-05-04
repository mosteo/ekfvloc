/*
 * Sub_opt.h
 *
 *  Created on: 29-sep-2009
 *      Author: mayte
 */

#ifndef SUB_OPT_H_
#define SUB_OPT_H_

#include "transf.hh"

void EIFnn(Matrix H, Matrix G, Matrix h, Matrix S, Matrix &F, Matrix &N);
void CalculateEstimationEIFnn(Matrix Fk, Matrix Nk, Matrix &x, Matrix &P);

#endif /* SUB_OPT_H_ */
