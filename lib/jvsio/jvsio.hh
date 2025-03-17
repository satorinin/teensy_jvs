#pragma once

#include <jvs_parallel.hh>
#include <jvs_config.hh>
#include <jvs_frame.hh>
#include <jvs_serial.hh>
#include <jvs_config.hh>
#include <bitset>


/**
 * @brief   Class for JVS IO.
 * 
 * This class is responsible for handling the IO of the JVS system.
 * 
 */
class JVSIO
{
    public:
     JVSIO(JVSParallel::Interface&, const JVSConfig&);
     void setup_io(const JVSConfig&);
     void build_io_packet(int player, JVSResponse& response);
     void update_analog(uint16_t (&analog_values)[8]);

    private:
        JVSParallel::Interface& parallel_;
        const JVSConfig& config_;
};
