/*
 * File:          my_controller.c
 * Date:14 de noviembre de 2025
 * Description:codigo para el sumobot
 * Author:VSJJ
 * Modifications:BUSCA al oponente y lo saca de la pista
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <stdio.h>
/*
 * You may want to add macros here.
 */
#define TIME_STEP 120

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();
  int i;
  //bool avoid_obstacle_counter = 0;
  double ds_values[3];
  double left_speed=-1.0;
  double right_speed=1.0;
  
  //bool flag_i=1;
  WbDeviceTag ds[3];
  char ds_names[3][10]={"ds_left","ds_right","ds_center"};
  
  for (i=0; i<3;i++){
    ds[i]=wb_robot_get_device(ds_names[i]);
    wb_distance_sensor_enable(ds[i],TIME_STEP);
    }
    
  WbDeviceTag wheels[2];
  char wheels_names[2][8]={"wheel1","wheel2"};
  
  for (i=0; i<2; i++){
  wheels[i]=wb_robot_get_device(wheels_names[i]);
  wb_motor_set_position(wheels[i],INFINITY);  
  }
       
  //avoid_obstacle_counter=2;
  
  while (wb_robot_step(TIME_STEP) != -1) {
  
  for(i=0;i<3;i++){
    ds_values[i]=wb_distance_sensor_get_value(ds[i]); 
    printf("sensor_[%d]=%f\n",i,ds_values[i]);
    }
  /*if (ds_values[0] < 650.0 || ds_values[2]<650.0 || ds_values[1]<650.0)
    avoid_obstacle_counter=100;
  else {
    avoid_obstacle_counter = 40;}*/
  if ((ds_values[0]>990) & (ds_values[1]>990) & (ds_values[2]>990)){
   //avoid_obstacle_counter--;
   left_speed = -1.0;
   right_speed =  1.0;
  } 
  else if ((ds_values[0]<980) || (ds_values[1]<980)){
   //(avoid_obstacle_counter < 600
   //avoid_obstacle_counter--;
   left_speed = 0.3;
   right_speed =  1.0;
   }
   else if  ((ds_values[2]<980) || (ds_values[1]<980)){
   //(avoid_obstacle_counter < 600
   //avoid_obstacle_counter--;
   left_speed = 1;
   right_speed = 0.3;
   }
  wb_motor_set_velocity(wheels[0],left_speed);  
  wb_motor_set_velocity(wheels[1],right_speed); 
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
