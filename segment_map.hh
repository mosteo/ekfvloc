/*
 * Seg_map.h
 *
 *  Created on: 17-dic-2009
 *      Author: mayte
 */

#ifndef SEG_MAP_H_
#define SEG_MAP_H_

#include <vector>
#include "transf.hh"

class SegmentMap
{
public:
    SegmentMap();
    SegmentMap(string filename);
    virtual ~SegmentMap();

    void AddSegment(double x1, double y1, double x2, double y2);

    bool IsEmpty(void) const;

    int NumSegments(void) const;

    Transf segments(int i) const;
    double lengths(int i) const;

private:
    vector<Transf> segments_;
    vector<double> lengths_;
};

#endif /* SEG_MAP_H_ */
