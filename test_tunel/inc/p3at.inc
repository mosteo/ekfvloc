# Common parameters to all pioneers
define pioneer position (
  color "red"
  drive "diff"
  gui_nose 1                  # Indicate the front.
  gui_boundary 0              # Don't draw bounding box.
  obstacle_return 1           # Can hit things.
  laser_return 1              # Robot body seen by other lasers.
  ranger_return 1             # Seen by other sonar.
  blobfinder_return 1         # Seen by other blobfinders.
  fiducial_return 2           # Seen as "2" by other fiducial sensors.

  #odom_error [ 0.01 0.01 0.020 ]   # Odometry error or slip in X, Y and Theta
                                    # (Uniform random distribution) 

  # Used for position control commands (MOVE, HEAD):
  default_speed [1.5 0.0 1.3] # m(x), m(y), radians(theta)

  # Maximum limits:
  max_speed [2.0 0 1.74]   # m(x), m(y), radians(theta)

  # Acceleration:
  accel [0.3 0 1.74]        # m(x), m(y), radians(theta)
  decel [0.3 0 1.74]        # m(x), m(y), radians(theta)

  # Conversion factors for sending/recieving over client protocol
  pioneer_diffconv 0.0056
  pioneer_distconv 0.485
  pioneer_angleconv 0.001534
  pioneer_vel2div 20
  pioneer_velconv 1.0
  pioneer_rangeconv 1.0
)

# SICK LMS-200 laser rangefinder
define sicklms200 laser (
  range_min 0.0
#  range_max 32.0
#  samples 361
#  fov 180.0
  color "LightBlue"
  size [0.155 0.15]
  #height 0.195 # Uncomment to enable 
  laser_beam_height 0.08 # approx, it actually can vary a few cm in real life
  laser_return 1
  ranger_return 1
  blobfinder_return 0
  fiducial_return 0
#  noise 0.0075 # Adds uniform random number in [-0.0075, 0.0075] meters
  reading_angle_error 0.0007 # Adds uniform random number in [-0.0007,0.0007] radians
)

# Model for a p3at differential-drive robot base with sonar.
define p3at pioneer (
  pioneer_robot_subtype "p3at"

  # Speed profile:
  max_speed [0.6 0 0.75]
  accel [0.3 0 0.8]
  decel [0.3 0 0.8]

  # Body shape:
  size [0.626 0.505]
  polygons 1
  polygon[0].points 8
  polygon[0].point[0] [-0.18 0.313]
  polygon[0].point[1] [0.18 0.313]
  polygon[0].point[2] [0.2525 0.18]
  polygon[0].point[3] [0.2525 -0.18]
  polygon[0].point[4] [0.18 -0.313]
  polygon[0].point[5] [-0.18 -0.313]
  polygon[0].point[6] [-0.2525 -0.18]
  polygon[0].point[7] [-0.2525 0.18]
  polygon[0].filled 1

  #height 0.27724

  # client protocol conversion factors
  pioneer_diffconv 0.0034
  pioneer_distconv 0.465
  pioneer_angleconv 0.001534
  pioneer_velconv 1.0
)
