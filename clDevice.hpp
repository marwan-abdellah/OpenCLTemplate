#ifndef CLDEVICE_HPP
#define CLDEVICE_HPP

#include "clHardware.h"
#include <string>

class clDevice
{
public:
    /**
     * @brief clDevice
     * @param name
     * @param id
     */
    clDevice( const std::string name, const cl_device_id id ) :
        _name(name), _id(id) { }

    /**
     * @brief getName
     * @return
     */
    std::string getName( void ) const { return _name; }

    /**
     * @brief getId
     * @return
     */
    cl_device_id getId( void ) const { return _id; }

private:

    /** @brief */
    const std::string _name;

    /** @brief */
    const cl_device_id _id;
};

#endif // CLDEVICE_HPP

