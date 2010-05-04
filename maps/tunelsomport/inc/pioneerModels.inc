# Stage model definitions for ActivMedia robots
# Include into a Stage world file with 'include'
# $Id: PioneerRobotModels.world.inc,v 1.25 2006/02/20 16:28:26 reed Exp $

# These settings are intended to represent typical values for the various
# models, but more importantly, agree with Aria's parameter files.

# Sonar array
define pioneerSonar ranger (
  sview [0.1 5.0 30]  # min (m), max (m), field of view (deg)
  ssize [0.01 0.04]
  laser_return 0
  fiducial_return 0
)

# Common parameters to all pioneers
define pioneer position (
  color "red"
  drive "diff"
  gui_nose 1                  # Indicate the front.
  obstacle_return 1           # Can hit things.
  laser_return 1              # Robot body seen by other lasers.
  ranger_return 1             # Seen by other sonar.
  fiducial_return 2           # Seen as "2" by other fiducial sensors.

  localization "odom"         # Change to "gps" to have impossibly perfect, global odometry
  localization_origin [0 0 0] # Start odometry at (0, 0, 0).
  odom_error [ 0.1 0.1 0.15 ]  # Odometry error or slip in X, Y and Theta
#  odom_error [ 0.01 0.01 0.015 ]  # Odometry error or slip in X, Y and Theta

)

# Model for a p3at differential-drive robot base with sonar.
define p3at pioneer (

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

  # Sonar:
  pioneerSonar (
    scount 16
    sview [0.1 4.0 30]
    ssize [0.01 0.04]
    spose[0] [0.147 0.136 90]
    spose[1] [0.193 0.119 50]
    spose[2] [0.227 0.079 30]
    spose[3] [0.245 0.027 10]
    spose[4] [0.245 -0.027 -10]
    spose[5] [0.227 -0.079 -30]
    spose[6] [0.193 -0.119 -50]
    spose[7] [0.147 -0.136 -90]
    spose[8] [-0.144 -0.136 -90]
    spose[9] [-0.189 -0.119 -130]
    spose[10] [-0.223 -0.079 -150]
    spose[11] [-0.241 -0.027 -170]
    spose[12] [-0.241 0.027 170]
    spose[13] [-0.223 0.079 150]
    spose[14] [-0.189 0.119 130]
    spose[15] [-0.144 0.136 90]
  )
  #sicklms200( pose [0.160 0 0] )
)

#####################
## ROBOT CHIQUITITO
#####################

# Model for a p3dx differential-drive robot base with sonar.
define p3dx pioneer (

  # Body shape:
  origin [-0.04465 0.0 0.0]
  size [0.511 0.425]
  polygons 1
  polygon[0].points 8
  polygon[0].point[0] [-0.12 0.255]
  polygon[0].point[1] [0.12 0.255]
  polygon[0].point[2] [0.2125 0.12]
  polygon[0].point[3] [0.2125 -0.12]
  polygon[0].point[4] [0.12 -0.255]
  polygon[0].point[5] [-0.12 -0.255]
  polygon[0].point[6] [-0.2125 -0.12]
  polygon[0].point[7] [-0.2125 0.12]

  # Sonar:
  pioneerSonar (
    scount 16
    spose[0] [0.069 0.136 90]
    spose[1] [0.114 0.119 50]
    spose[2] [0.148 0.078 30]
    spose[3] [0.166 0.027 10]
    spose[4] [0.166 -0.027 -10]
    spose[5] [0.148 -0.078 -30]
    spose[6] [0.114 -0.119 -50]
    spose[7] [0.069 -0.136 -90]
    spose[8] [-0.157 -0.136 -90]
    spose[9] [-0.203 -0.119 -130]
    spose[10] [-0.237 -0.078 -150]
    spose[11] [-0.255 -0.027 -170]
    spose[12] [-0.255 0.027 170]
    spose[13] [-0.237 0.078 150]
    spose[14] [-0.203 0.119 130]
    spose[15] [-0.157 0.136 90]
  )
  #sicklms200( pose [0.018 0 0] )
)