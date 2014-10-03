#include "globalsettings.h"

double GlobalSettings::time_scale = 1.0;

long GlobalSettings::timer_interval = 200;

float GlobalSettings::cars_distance = 0.1;

long GlobalSettings::time_to_next_car_primary = 6000;
long GlobalSettings::dispersion_time_next_car_primary = 400;

long GlobalSettings::time_to_next_car_secondary = 7000;
long GlobalSettings::dispersion_time_next_car_secondary = 400;

float GlobalSettings::default_distance_from_lights = 40;

float GlobalSettings::default_car_speed = 0.7;

float GlobalSettings::meter_to_pixel_scale = 10;
