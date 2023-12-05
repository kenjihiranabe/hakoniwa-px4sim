#ifndef _DRON_DYNAMICS_HPP_
#define _DRON_DYNAMICS_HPP_

#include "idrone_dynamics.hpp"

namespace hako::assets::drone {


class DroneDynamicsBodyFrame : public hako::assets::drone::IDroneDynamics {
private:
    /*
     * parameters
     */
    double param_mass;
    double param_drag;
    double param_cx;
    double param_cy;
    double param_cz;
    /*
     * internal state
     */
    DronePositionType position;
    DroneVelocityType velocity;
    DroneAngleType angle;
    DroneAngularVelocityType angularVelocity;

    DronePositionType next_position;
    DroneVelocityType next_velocity;
    DroneAngleType next_angle;
    DroneAngularVelocityType next_angularVelocity;

    DroneVelocityBodyFrameType velocityBodyFrame;
    DroneAngularVelocityBodyFrameType angularVelocityBodyFrame;
    DroneVelocityBodyFrameType next_velocityBodyFrame;
    DroneAngularVelocityBodyFrameType next_angularVelocityBodyFrame;

    double delta_time_sec;
    double total_time_sec;

    void run_x(const DroneThrustype &thrust, const DroneTorqueType &torque);
    void run_y(const DroneThrustype &thrust, const DroneTorqueType &torque);
    void run_z(const DroneThrustype &thrust, const DroneTorqueType &torque);
    void run_rx(const DroneThrustype &thrust, const DroneTorqueType &torque);
    void run_ry(const DroneThrustype &thrust, const DroneTorqueType &torque);
    void run_rz(const DroneThrustype &thrust, const DroneTorqueType &torque);

public:
    // Constructor with zero initialization
    DroneDynamicsBodyFrame(double dt)
    {
        this->total_time_sec = 0;
        this->delta_time_sec = dt;
        this->param_mass = 1;
        this->param_drag = 0;
        this->param_cx = 1;
        this->param_cy = 1;
        this->param_cz = 1;
    }
    virtual ~DroneDynamicsBodyFrame() {}

    void set_mass(double mass)
    {
        this->param_mass = mass;
    }
    void set_drag(double drag) override
    {
        this->param_drag = drag;
    }
    // Setters
    void set_pos(DronePositionType &pos) override {
        position = pos;
    }

    void set_vel(DroneVelocityType &vel) override {
        velocity = vel;
    }

    void set_angle(DroneAngleType &ang) override {
        angle = ang;
    }

    void set_angular_vel(DroneAngularVelocityType &angularVel) override {
        angularVelocity = angularVel;
    }

    // Getters
    DronePositionType get_pos() const override {
        return position;
    }

    DroneVelocityType get_vel() const override {
        return velocity;
    }

    DroneAngleType get_angle() const override {
        return angle;
    }

    DroneAngularVelocityType get_angular_vel() const override {
        return angularVelocity;
    }
    DroneVelocityBodyFrameType get_vel_body_frame() const override {
        return velocityBodyFrame;
    }
    DroneAngularVelocityBodyFrameType get_angular_vel_body_frame() const override {
        return angularVelocityBodyFrame;
    }

    // Implementation for the run function is required
    void run(DroneThrustype &thrust, DroneTorqueType &torque) override 
    {
        run_x(thrust, torque);
        run_y(thrust, torque);
        run_z(thrust, torque);
        run_rx(thrust, torque);
        run_ry(thrust, torque);
        run_rz(thrust, torque);

        this->velocityBodyFrame = this->next_velocityBodyFrame;
        this->angularVelocityBodyFrame = this->next_angularVelocityBodyFrame;

        //boundary condition
        if (this->next_position.data.z > 0) {
            this->next_position.data.z = 0;
            this->next_velocity.data.z = 0;
        }

        this->position = this->next_position;
        this->velocity = this->next_velocity;
        this->angle = this->next_angle;
        this->angularVelocity = this->next_angularVelocity;
        
        this->total_time_sec += this->delta_time_sec;
    }
};

}


#endif /* _DRON_DYNAMICS_HPP_ */