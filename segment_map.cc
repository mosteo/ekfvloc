/*
 * Seg_map.cpp
 *
 *  Created on: 17-dic-2009
 *      Author: mayte
 */

#include <fstream>
#include "segment_map.hh"

SegmentMap::SegmentMap()
{
}

SegmentMap::SegmentMap(string filename)
{
    // Initialization from file
    ifstream fmap;
    fmap.open(filename.c_str());
    if (fmap.fail())
    {
        throw invalid_argument(std::string("Error opening file: " + filename));
    }

    double p1x, p1y, p2x, p2y;
    int count = 0;

    while (!fmap.eof())
    {
        fmap >> p1x;
        fmap >> p1y;
        fmap >> p2x;
        fmap >> p2y;

        AddSegment(p1x, p1y, p2x, p2y);
        count++;
    }
    printf("Read %d segments from %s\n", count, filename.c_str());
}

void SegmentMap::AddSegment(double x1, double y1, double x2, double y2)
{

    const double &p1x = x1, &p1y = y1,
                 &p2x = x2, &p2y = y2;

    Transf seg = Transf((p1x + p2x) / 2,
                        (p1y + p2y) / 2,
                        atan2(p2y - p1y,
                              p2x - p1x));

    segments_.push_back(seg);
    lengths_.push_back(sqrt((p2x - p1x) * (p2x - p1x) +
                            (p2y - p1y) * (p2y - p1y)));
}

SegmentMap::~SegmentMap()
{
}

int SegmentMap::NumSegments() const
{
    return segments_.size();
}

Transf SegmentMap::segments(int i) const
{
    return segments_[i];
}

double SegmentMap::lengths(int i) const
{
    return lengths_[i];
}

bool SegmentMap::IsEmpty(void) const
{
    return lengths_.size() == 0;
}