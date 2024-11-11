#ifndef _IBATTERY_DYNAMICS_HPP_
#define _IBATTERY_DYNAMICS_HPP_

#include "idischarge_dynamics.hpp"
#include "config/drone_config_types.hpp"
#include <vector>

namespace hako::assets::drone {

class IBatteryDynamics {
protected:
    void *vendor_model;
    void *context;
    BatteryModelParameters params;
    std::vector<IDischargeDynamics*> devices;
public:
    virtual ~IBatteryDynamics() {}
    virtual void set_vendor(void *vendor, void *context)
    {
        this->vendor_model = vendor;
        this->context = context;
    }
    virtual void add_device(IDischargeDynamics& device)
    {
        devices.push_back(&device);
    }
    //calculate battery remained value
    virtual double get_vbat() = 0;
    virtual void set_params(const BatteryModelParameters &p)
    {
        this->params = p;
    }

};
}

#endif /* _IBATTERY_DYNAMICS_HPP_ */