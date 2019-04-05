#include "../../Logging/easylogging++.h"
#include <string>
#include "structures.h"
#include "convert_power.h"
#include "logging.h"


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

class Logger {
  public:
    void logger_init (const std::string PathToConfig);
    void write_values(const std::string var1, const std::string var2);
    void write_struct_user_power_to_log(const structures::PowerInput *power_input_ptr, const structures::PowerOutput *power_output_ptr, const structures::UserInput *user_input_ptr);
    void write_struct_control_data_to_log(const structures::ControlData *control_data_ptr);
    void write_struct_telemetry_input_to_log(const structures::TelemetryInput *telemetry_input_ptr);
    //int area () {return width*height;}
};

void Logger::logger_init (const std::string PathToConfig) {
    // Load configuration from file
    el::Configurations conf(PathToConfig);
    //el::Configurations conf("configuration.conf");
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);
    // Now all the loggers will use configuration from file
    
}



void Logger::write_values(const std::string var1, const std::string var2){
   LOG(INFO) << 12 << "," << 13;
}


void Logger::write_struct_user_power_to_log(const structures::PowerInput *power_input_ptr, const structures::PowerOutput *power_output_ptr, const structures::UserInput *user_input_ptr){
   LOG(INFO) << power_input_ptr->battery.cel_voltages << ","<< power_input_ptr->battery.state_of_charge << "," << power_input_ptr->battery.error_number << ","
           << power_input_ptr->battery.error_location << "," << power_input_ptr->battery.max_temp<< ","  << power_input_ptr->battery.min_temp << "," << power_input_ptr->battery.balance_state << ","
           << power_input_ptr->solar_panels.MPPT_power << ","<< power_input_ptr->solar_panels.panel_power << ","
           << power_input_ptr->driver.motor_temp << "," << power_input_ptr->driver.driver_temp << ","<< power_input_ptr->driver.driver_output_power << "," 
           << power_input_ptr->driver.motor_speed << ","<< power_input_ptr->driver.driver_voltage_input << "," << power_input_ptr->driver.driver_current_input << ","
           << power_input_ptr->driver.driver_state << ","
           << power_output_ptr->solar_panel_states << "," << power_output_ptr->throttle << "," << power_output_ptr->motor_state << "," << power_output_ptr->contractor_control << ","
           << power_output_ptr->balancing_control << "," << power_output_ptr->error << ","
           << user_input_ptr->control.PID_state << "," << user_input_ptr->control.roll << "," 
           << user_input_ptr->buttons.battery_on << ","  << user_input_ptr->buttons.force_battery << "," << user_input_ptr->buttons.motor_on << ","
           << user_input_ptr->buttons.deadmans_switch << "," << user_input_ptr->buttons.solar_on << ","
           << user_input_ptr->steer.raw_throttle << "," << user_input_ptr->steer.fly_mode << "," << user_input_ptr->steer.reverse;
}

void Logger::write_struct_control_data_to_log(const structures::ControlData *control_data_ptr){
   LOG(INFO) << control_data_ptr->xsens.raw_pitch << "," << control_data_ptr->xsens.raw_roll << "," << control_data_ptr->xsens.filtered_pitch << ","
           << control_data_ptr->xsens.filtered_roll << "," << control_data_ptr->xsens.raw_z_acceleration << ","
           << control_data_ptr->vlotters.angle_left << "," << control_data_ptr->vlotters.angle_right << ","
           << control_data_ptr->computed.force_roll << "," << control_data_ptr->computed.force_pitch << "," << control_data_ptr->computed.force_height << ","
           << control_data_ptr->computed.angle_left << "," << control_data_ptr->computed.angle_right << "," << control_data_ptr->computed.angle_back;
}

void Logger::write_struct_telemetry_input_to_log(const structures::TelemetryInput *telemetry_input_ptr){
   LOG(INFO) << telemetry_input_ptr->control.PID_telem.P  << "," << telemetry_input_ptr->control.PID_telem.I  << "," << telemetry_input_ptr->control.PID_telem.D  << "," << telemetry_input_ptr->control.PID_telem.N  << "," 
           << telemetry_input_ptr->control.PID_height  << "," << telemetry_input_ptr->control.PID_roll  << "," << telemetry_input_ptr->control.PID_pitch  << ","
           << telemetry_input_ptr->solar_panel_states  << "," << telemetry_input_ptr->advised_speed;
}

