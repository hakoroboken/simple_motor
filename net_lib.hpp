#include <cstddef>
#include <vector>
#include <cstdint>
#include "mbed.h"


#define func auto

// deserialize func
template <typename T>
T deserialize(std::vector<uint8_t>& bytes) {
    static_assert(std::is_trivially_copyable<T>::value, "Data type is not trivially copyable");

    T data;
    std::memcpy(&data, bytes.data(), sizeof(data));
    return data;
}

struct motor_control_msg{
    std::uint8_t id;
    float motor_1;
    float motor_2;
    float motor_3;
    float motor_4;
};


inline func set_motor(const float & power, mbed::PwmOut & pwm, mbed::DigitalOut & digital){
    auto power_ = power;

    if(power > 1.0){
        power_ = 1.0;
    }

    if(power < -1.0){
        power_ = -1.0;
    }

    auto width = abs((int)(power_ * (float)2000));
    pwm.pulsewidth_us(width);
    if(power_ > 0.0){
        digital = 1;
    }else{
        digital = 0;
    }
}