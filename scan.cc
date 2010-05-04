/*
 * Scan.cpp
 *
 *  Created on: 29-sep-2009
 *      Author: mayte
 */

#include <cassert>

#include "scan.hh"

Scan::Scan(
			double max_range,
			double laser_x,
			double laser_y,
			double laser_angle,
            double laser_noise_range,
            double laser_noise_bearing) :
            kOutOfRange_         (max_range),
            kLaserNoiseRange_    (laser_noise_range),
            kLaserNoiseBearing_  (laser_noise_bearing),
            xform_laser_to_robot_(Transf (laser_x, laser_y, laser_angle))
{
}

void Scan::SetLaserPose(double x, double y, double a)
{
    xform_laser_to_robot_ = Transf(x, y, a);
}

const Uloc & Scan::uloc(const int i) const
{
    return ulocs_[i];
}

void Scan::addUloc (Uloc u) {
    ulocs_.push_back (u);
}

int Scan::ScanCount (void) const {
    return ulocs_.size();
}

double   Scan::phi (const int i) const {
    return phi_[i];
}

double   Scan::rho (const int i) const {
    return rho_[i];
}

/////////////////////////////////////////////////////////
Uloc Scan::AttachReferenceToScanPoint (double rho, double phi) {

	Uloc pnt = Uloc(POINT);

	pnt.SetLoc(Transf(rho * cos(phi), rho * sin(phi), phi));

	const double sphi = kLaserNoiseBearing_;
	const double srho = kLaserNoiseRange_;

	// sphi=0.004; // (0.5*pi)/(180*2)
	// srho=0.045; // SICK model, in meters

	pnt.Cov()(0,0) = pow(srho,2);
	pnt.Cov()(1,1) = pow(rho * sphi, 2);

	return pnt;
}
/////////////////////////////////////////////////////////

void Scan::SetLastScan (const DoublesVector& ranges,
                        const DoublesVector& bearings) {

	if (ranges.size() != bearings.size())
		throw range_error("Mismatching ranges in SetLastScan");

	ulocs_.clear();
	rho_.clear();
	phi_.clear();

	for (size_t i = 0; i < ranges.size(); i++) {

		// Prune out-of-range readings
		if (ranges[i] < kOutOfRange_) {

			rho_.push_back(ranges[i]);
			phi_.push_back(bearings[i]);

			addUloc (AttachReferenceToScanPoint(ranges[i], bearings[i]));

			assert(rho_.size() == phi_.size());
			assert(rho_.size() == ulocs_.size());

			// Move to robot reference frame
			ulocs_[ulocs_.size()-1].SetLoc (
			        Compose(xform_laser_to_robot_,
			                ulocs_[ulocs_.size()-1].kX()));
		}
	}
}
