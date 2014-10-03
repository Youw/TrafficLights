#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

struct GlobalSettings
{
  static double time_scale;

  static long timer_interval;

  static float cars_distance;

  static long time_to_next_car_primary;
  static long dispersion_time_next_car_primary;

  static long time_to_next_car_secondary;
  static long dispersion_time_next_car_secondary;

  static float default_distance_from_lights;

  static float default_car_speed;

  static float meter_to_pixel_scale;

};

#endif // GLOBALSETTINGS_H
