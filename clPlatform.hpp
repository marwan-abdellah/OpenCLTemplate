#ifndef CLPLATFORM_HPP
#define CLPLATFORM_HPP

#include "clHeaders.h"
#include <string>

class clPlatform
{
public:
    /**
     * @brief clPlatform
     * @param name
     * @param id
     */
    clPlatform( const std::string name, const cl_platform_id id ) :
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
    cl_platform_id getId( void ) const { return _id; }

private:

    /** @brief */
    const std::string _name;

    /** @brief */
    const cl_platform_id _id;
};

#endif // CLPLATFORM_HPP

