#include <stdlib.h>
#include <string>
#include "headerfiles/easylogging++.h"
#include "headerfiles/structures.h"
#include "headerfiles/convert_power.h"
#include "headerfiles/logging.h"
#include "headerfiles/thread.h"



int gen_rand()
{
    return std::rand()  % 100;
}


int main(int argc, const char** argv) {
   Thread Threads; 
   std::srand(std::time(nullptr));
   Threads.CreateThreads();
   structures::PowerInput *power_input_ptr, power_input;
   power_input_ptr = &power_input;
   structures::PowerOutput *power_output_ptr, power_output;
   power_output_ptr = &power_output;
   structures::UserInput *user_input_ptr, user_input;
   user_input_ptr = &user_input;
   
   structures::ControlData *control_data_ptr, control_data;
   control_data_ptr = &control_data;
   
   
   while(1)
   {

        control_data_ptr->xsens.raw_pitch =gen_rand(); 
        control_data_ptr->xsens.raw_roll  =gen_rand();
        control_data_ptr->xsens.filtered_pitch =gen_rand(); 
        control_data_ptr->xsens.filtered_roll =gen_rand();
        control_data_ptr->xsens.raw_z_acceleration =gen_rand(); 
        control_data_ptr->vlotters.angle_left =gen_rand();
        control_data_ptr->vlotters.angle_right =gen_rand();
        control_data_ptr->computed.force_roll =gen_rand();
        control_data_ptr->computed.force_pitch =gen_rand(); 
        control_data_ptr->computed.force_height =gen_rand();
        control_data_ptr->computed.angle_left =gen_rand();
        control_data_ptr->computed.angle_right =gen_rand();
        control_data_ptr->computed.angle_back=gen_rand();
      
   
   
   
   
   //control_data_ptr->computed.angle_back = gen_rand();
   //power_input_ptr->battery.state_of_charge = 9.3;
   //user_power_logger.write_struct_user_power_to_log(power_input_ptr, power_output_ptr, user_input_ptr);
   //control_data_logger.write_struct_control_data_to_log(control_data_ptr);
   Threads.writeControlData(control_data_ptr, 0, 1);
   //usleep(20000); 
   }
   return 0;
}