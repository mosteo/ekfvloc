/*
 * localize.cc
 *
 *  Created on: Jan 12, 2010
 *      Author: amosteo@unizar.es
 */

#include <cassert>
#include "localize.hh"
#include <map>

Localize::Localize(double laser_max_range,
                   double laser_pose_x,
                   double laser_pose_y,
                   double laser_pose_angle,
                   double laser_noise_range, // uncertainty in distance measured
                   double laser_noise_bearing, // uncertainty in sample bearing
                   double odom_noise_x,
                   double odom_noise_y,
                   double odom_noise_angle // uncertainty for odometry
) :
    scan_(laser_max_range,
          laser_pose_x, laser_pose_y, laser_pose_angle,
          laser_noise_range, laser_noise_bearing),
    robot_(odom_noise_x, odom_noise_y, odom_noise_angle),
    has_pose_(false)
{
}

void Localize::SetLaserPose(double x, double y, double a)
{
    scan_.SetLaserPose(x, y, a);
}

void Localize::SetRobotPose(double x, double y, double angle)
{
    SetPoses(0, 0, 0, x, y, angle);
}

void Localize::SetPoses(double ox, double oy, double oth,
                        double gx, double gy, double gth)
{
    robot_.SetPoses(ox, oy, oth, gx, gy, gth);
    has_pose_ = true;
}

void Localize::SetRobotPoseError(double ex, double ey, double eth)
{
    robot_.SetCurrentError(ex, ey, eth);
}

void Localize::LoadMap(const char* filename)
{
    robot_.map() = SegmentMap(filename);
}

void Localize::SetMap(const SegmentsVector& map)
{
    robot_.map() = SegmentMap();

    for (int i = 0; i < (int) map.size(); i++)
    {
        robot_.map().AddSegment(map[i].x1, map[i].y1,
                                map[i].x2, map[i].y2);
    }
}

const SegmentMap &Localize::Map(void) const
{
    return robot_.map();
}

void Localize::AddSegment(const Segment& segment) {
    robot_.map().AddSegment(segment.x1, segment.y1,
                               segment.x2, segment.y2);
}

/// Compute actualization from robot accumulated odometry and laser reading
bool Localize::Update(double robot_x,
                      double robot_y,
                      double robot_angle,
                      DoublesVector ranges,
                      DoublesVector bearings)
{
    assert(has_pose_);
    assert(!robot_.map().IsEmpty());

    scan_.SetLastScan(ranges, bearings);

    return robot_.Locate(Transf(robot_x, robot_y, robot_angle), scan_);
}

Pose Localize::pose(void) const
{
    return robot_.EstimatedPose();
}
