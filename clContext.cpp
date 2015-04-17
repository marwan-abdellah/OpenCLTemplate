#include "clContext.h"

clContext::clContext()
{

}


/**
 * @brief clContext::getContextId
 * @return
 */
cl_context clContext::getContextId(void) const
{
    return _contextId;
}


/**
 * @brief clContext::getContextProperties
 * @return
 */
cl_context_properties clContext::getContextProperties(void) const
{
    return _contextProp;
}


/**
 * @brief clContext::~clContext
 */
clContext::~clContext()
{

}

