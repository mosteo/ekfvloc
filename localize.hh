/*
 * localize.hh
 *
 *  Created on: Jan 12, 2010
 *      Author: amosteo@unizar.es
 */

#ifndef LOCALIZE_HH_
#define LOCALIZE_HH_

#include "robot_location.hh"
#include "scan.hh"
#include "segment_map.hh"

class Localize
{
public:
    /// Initialize parameters
    Localize(double laser_max_range,
             double laser_pose_x,
             double laser_pose_y,
             double laser_pose_angle,
             double laser_noise_range,   // uncertainty in distance measured (2sigma)
             double laser_noise_bearing, // uncertainty in sample bearing (2sigma)
             double odom_noise_x,
             double odom_noise_y,
             double odom_noise_angle // uncertainty for odometry model
             );

    /// Initialize robot map pose, and reset odometry to zero
    void SetRobotPose(double x, double y, double angle);
    /// Initialize both odometry (if it is not zero) and global (map) pose
    void SetPoses(double ox, double oy, double oth,
                  double gx, double gy, double gth);
    /// Initial pose error
    void SetRobotPoseError(double ex, double ey, double eth);

    /// Update laser pose (limited to x, y ,a for now, though)
    /// m m rad
    void SetLaserPose(double x, double y, double a);

    void LoadMap(const char* filename);
    void SetMap(const SegmentsVector& map);
    void AddSegment(const Segment& segment);
    const SegmentMap &Map(void) const;

    /// Compute actualization from robot accumulated odometry and laser reading
    /// Returns true if the update was performed (minimum delta in odometry)
    bool Update(double robot_x, double robot_y, double robot_angle,
                DoublesVector ranges, DoublesVector bearings);

    Pose pose(void) const;
    Matrix GetCovariance(void) const { return robot_.Covariance(); };
private:
    Scan scan_;
    RobotLocation robot_;
    bool has_pose_;
};

#endif /* LOCALIZE_HH_ */
