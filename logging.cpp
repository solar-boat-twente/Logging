#include "headerfiles/logging.h"


Logger::Logger(const std::string PathToConfig)
{
    // constructor: variables initialzing 
    el::Configurations conf(PathToConfig);
    //el::Configurations conf("configuration.conf");
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);

}

Logger::Logger(const Logger& orig)
{
}

Logger::~Logger()
{
    // ~ deconstructor
}

INITIALIZE_EASYLOGGINGPP



PowerHandler::PowerHandler(structures::PowerInput* power_input,
                           structures::PowerOutput* power_output,
                           structures::UserInput* user_input,
                           structures::TelemetryInput* telemetry_input) {


  PowerHandler::power_input = power_input;
  PowerHandler::power_output = power_output;
  PowerHandler::user_input = user_input;
  PowerHandler::telemetry_input = telemetry_input;
}

/*
std::string append_array_to_csv_format(const float array[]){
//std::string append_array_to_csv_format(std:: array<const float, 5> array){
    std::string string_to_append;
    std::cout << "Nr of array elements:" << std::to_string(num_elements) << std::endl;
    for (int i=0; i < num_elements; i++)
    {
        string_to_append.append(",");
        string_to_append.append(std::to_string(array[i]));
    }
    
    std::cout << "Testing string appending" << string_to_append << std::endl;
    return string_to_append;
    
}
*/
void Logger::write_struct_user_power_to_log(const structures::PowerInput *power_input_ptr, const structures::PowerOutput *power_output_ptr, const structures::UserInput *user_input_ptr){
    //std::string testing_func;
    //testing_func = append_array_to_csv_format(power_input_ptr->battery.cel_voltages);
    LOG(INFO) << "," << power_input_ptr->battery.cel_voltages[0] << "," << power_input_ptr->battery.cel_voltages[1] << "," << power_input_ptr->battery.cel_voltages[2] << "," << power_input_ptr->battery.cel_voltages[3] 
           << "," << power_input_ptr->battery.cel_voltages[4] << "," << power_input_ptr->battery.cel_voltages[5] << "," << power_input_ptr->battery.cel_voltages[6] << "," << power_input_ptr->battery.cel_voltages[7] 
           << "," << power_input_ptr->battery.cel_voltages[8] << "," << power_input_ptr->battery.cel_voltages[9] << "," << power_input_ptr->battery.cel_voltages[10] << "," << power_input_ptr->battery.cel_voltages[11] 
           << ","<< power_input_ptr->battery.state_of_charge << "," << power_input_ptr->battery.error_number 
           << ","<< power_input_ptr->battery.error_location << "," << power_input_ptr->battery.max_temp<< ","  << power_input_ptr->battery.min_temp << "," << power_input_ptr->battery.balance_state
           << "," << power_input_ptr->battery.contactor_ready << "," << power_input_ptr->battery.contactor_status 
           << ","<< power_input_ptr->solar_panels.MPPT_power[0] << ","<< power_input_ptr->solar_panels.MPPT_power[1] << ","<< power_input_ptr->solar_panels.MPPT_power[2] 
           << ","<< power_input_ptr->solar_panels.MPPT_power[3] << ","<< power_input_ptr->solar_panels.MPPT_power[4] << ","<< power_input_ptr->solar_panels.MPPT_power[5] 
           << ","<< power_input_ptr->solar_panels.MPPT_power[6] << ","<< power_input_ptr->solar_panels.MPPT_power[7] << ","<< power_input_ptr->solar_panels.MPPT_power[8] 
           << ","<< power_input_ptr->solar_panels.MPPT_power[9] 
           << ","<< power_input_ptr->solar_panels.panel_power[0] << ","<< power_input_ptr->solar_panels.panel_power[1] << ","<< power_input_ptr->solar_panels.panel_power[2] 
           << ","<< power_input_ptr->solar_panels.panel_power[3] << ","<< power_input_ptr->solar_panels.panel_power[4] << ","<< power_input_ptr->solar_panels.panel_power[5] 
           << ","<< power_input_ptr->solar_panels.panel_power[6] << ","<< power_input_ptr->solar_panels.panel_power[7] << ","<< power_input_ptr->solar_panels.panel_power[8] 
           << ","<< power_input_ptr->solar_panels.panel_power[9] 
           << ","<< power_input_ptr->driver.motor_temp << "," << power_input_ptr->driver.driver_temp << ","<< power_input_ptr->driver.driver_output_power 
           << ","<< power_input_ptr->driver.motor_speed << ","<< power_input_ptr->driver.driver_voltage_input << "," << power_input_ptr->driver.driver_current_input
           << ","<< power_input_ptr->driver.driver_state 
           << ","<< power_output_ptr->solar_panel_states[0] << ","<< power_output_ptr->solar_panel_states[2]<< ","<< power_output_ptr->solar_panel_states[3]
           << ","<< power_output_ptr->solar_panel_states[4]<< ","<< power_output_ptr->solar_panel_states[5]<< ","<< power_output_ptr->solar_panel_states[6]
           << ","<< power_output_ptr->solar_panel_states[7]<< ","<< power_output_ptr->solar_panel_states[8]<< ","<< power_output_ptr->solar_panel_states[9]
           << "," << power_output_ptr->throttle << "," << power_output_ptr->motor_state << "," << power_output_ptr->contractor_control 
           << ","<< power_output_ptr->balancing_control << "," << power_output_ptr->error 
           << ","<< user_input_ptr->control.PID_state << "," << user_input_ptr->control.roll 
           << ","<< user_input_ptr->buttons.battery_on << ","  << user_input_ptr->buttons.force_battery << "," << user_input_ptr->buttons.motor_on 
           << ","<< user_input_ptr->buttons.deadmans_switch << "," << user_input_ptr->buttons.solar_on 
           << ","<< user_input_ptr->steer.raw_throttle << "," << user_input_ptr->steer.fly_mode << "," << user_input_ptr->steer.reverse;
}

void Logger::write_struct_control_data_to_log(const structures::ControlData *control_data_ptr){
   LOG(INFO) << "," << control_data_ptr->xsens.raw_pitch << "," << control_data_ptr->xsens.raw_roll << "," << control_data_ptr->xsens.filtered_pitch << ","
           << control_data_ptr->xsens.filtered_roll << "," << control_data_ptr->xsens.raw_z_acceleration << ","
           << control_data_ptr->vlotters.angle_left << "," << control_data_ptr->vlotters.angle_right << ","
           << control_data_ptr->computed.force_roll << "," << control_data_ptr->computed.force_pitch << "," << control_data_ptr->computed.force_height << ","
           << control_data_ptr->computed.angle_left << "," << control_data_ptr->computed.angle_right << "," << control_data_ptr->computed.angle_back;
}

void Logger::write_struct_telemetry_input_to_log(const structures::TelemetryInput *telemetry_input_ptr){
   LOG(INFO) << "," << telemetry_input_ptr->control.PID_telem.P  << "," << telemetry_input_ptr->control.PID_telem.I  << "," << telemetry_input_ptr->control.PID_telem.D  << "," << telemetry_input_ptr->control.PID_telem.N  << "," 
           //<< telemetry_input_ptr->control.PID_height  << "," << telemetry_input_ptr->control.PID_roll  << "," << telemetry_input_ptr->control.PID_pitch  << ","
           << telemetry_input_ptr->control.overwrite  << ","
           << telemetry_input_ptr->solar_panel_states[0]  << "," << telemetry_input_ptr->solar_panel_states[1]  << ","<< telemetry_input_ptr->solar_panel_states[2]  << ","
           << telemetry_input_ptr->solar_panel_states[3]  << ","<< telemetry_input_ptr->solar_panel_states[4]  << ","<< telemetry_input_ptr->solar_panel_states[5]  << ","
           << telemetry_input_ptr->solar_panel_states[6]  << ","<< telemetry_input_ptr->solar_panel_states[7]  << ","<< telemetry_input_ptr->solar_panel_states[8]  << ","
           << telemetry_input_ptr->solar_panel_states[9]  << ","
           << "," << telemetry_input_ptr->advised_speed;
}



