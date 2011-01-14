define sicklms200 laser
(
  range_min 0.0
  range_max 8.0
  fov 180.0
  samples 361

  color "LightBlue"
  size [0.155 0.15]	
)


#####################################
# Definicion del Laser en MobileSim
#####################################

#define sicklms200 laser (
#  range_min 0.0
#  range_max 32.0
#  samples 360
#  color "LightBlue"
#  size [0.155 0.15]
#  laser_return 1
#  ranger_return 1
#  blobfinder_return 0
#  fiducial_return 0
#  noise 0.005
#  reading_angle_error 0.001
#
#  laser_return_rules 2
#  laser_return_rule[0].model 2
#  laser_return_rule[0].condition "outside_range"
#  laser_return_rule[0].range 8
#  laser_return_rule[0].detect 1
#
#  laser_return_rule[1].model 2
#  laser_return_rule[1].condition "outside_angle"
#  laser_return_rule[1].angle 60
#  laser_return_rule[1].detect 1
#)
