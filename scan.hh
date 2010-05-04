/*
 * Scan.h
 *
 *  Created on: 29-sep-2009
 *      Author: mayte
 */

#ifndef SCAN_H_
#define SCAN_H_

#include <vector>
#include "types.hh"
#include "uloc.hh"

class Scan
{
public:

    /// Provide laser parameters: maximum range and its pose on top of robot,
    /// and noise model.
    Scan(double max_range,
         double laser_x,
         double laser_y,
         double laser_angle,
         double laser_noise_range,
         double laser_noise_bearing);

    const Uloc & uloc(const int i) const; // read only access

    /// Update laser pose
    void SetLaserPose(double x, double y, double a);

    /// Set last laser reading
    /// Removes out of range values and attaches the uncertainty model
    void SetLastScan(const DoublesVector& ranges,
                     const DoublesVector& bearings);

    int ScanCount(void) const;

    double phi(const int i) const;
    double rho(const int i) const;

    const double kOutOfRange_;
    const double kLaserNoiseRange_;
    const double kLaserNoiseBearing_;
private:
    Uloc AttachReferenceToScanPoint(double rho, double phi);

    void addUloc(Uloc u);
    vector<Uloc> ulocs_;

    DoublesVector rho_; // Distance
    DoublesVector phi_; // Bearing

    Transf xform_laser_to_robot_;
};

#endif /* SCAN_H_ */
