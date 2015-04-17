#ifndef CLCONTEXT_H
#define CLCONTEXT_H

#include "clHeaders.h"

class clContext
{
public:
    clContext();

    /**
     * @brief getContextId
     * @return
     */
    cl_context getContextId(void) const;

    /**
     * @brief getContextProperties
     * @return
     */
    cl_context_properties getContextProperties(void) const;

    ~clContext();

private:
    /** @brief */
    cl_context _contextId;

    /** @brief */
    cl_context_properties _contextProp;


};

#endif // CLCONTEXT_H
