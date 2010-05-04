/*
 * types.hh
 *
 *  Created on: Jan 12, 2010
 *      Author: amosteo@unizar.es
 */

#ifndef TYPES_HH_
#define TYPES_HH_

#include <vector>

typedef std::vector<double> DoublesVector;

class Segment
{
public:
    double x1, y1, x2, y2;
    Segment(double x1, double y1, double x2, double y2)
    {
        this->x1 = x1; this->y1 = y1;
        this->x2 = x2; this->y2 = y2;
    }
};

typedef std::vector<Segment> SegmentsVector;

class Pose
{
public:
    double x, y, th;
    Pose(double x, double y, double th)
    {
       this->x = x; this->y = y; this->th = th;
    }
};

class GuiSegment
{
    public:
        GuiSegment(double rho0, double phi0, double rho1, double phi1) :
            rho0_(rho0), phi0_(phi0), rho1_(rho1), phi1_(phi1) {};

        double rho0(void) const { return rho0_; };
        double rho1(void) const { return rho1_; };
        double phi0(void) const { return phi0_; };
        double phi1(void) const { return phi1_; };
    private:
        double rho0_, phi0_, rho1_, phi1_;
};

class GuiRegion : public GuiSegment
{
    public:
        GuiRegion(double rho0, double phi0, double rho1, double phi1) :
            GuiSegment(rho0, phi0, rho1, phi1) {};
};

class GuiSplit : public GuiSegment
{
    public:
        GuiSplit(double rho0, double phi0, double rho1, double phi1) :
            GuiSegment(rho0, phi0, rho1, phi1) {};
};

class GuiData
{
    public:
        void Clear(void)
        {
            regions.clear(); splits.clear(); matches.clear(); mahala.clear();
            laser_rho.clear(); laser_phi.clear();
        }
        
        std::vector<GuiRegion> regions;
        std::vector<GuiSplit> splits;
        std::vector<GuiSplit> matches; // lasers that match
        std::vector<double> mahala; // mahala distance of the match, norm to 1
        std::vector<double> laser_rho;
        std::vector<double> laser_phi;
};

extern GuiData GUI_DATA; // Declared in the driver, for passing via the opaque

#endif /* TYPES_HH_ */
