#pragma once

// Map legacy role macros to the new terminology

#if defined(ROLE_MASTER) && !defined(ROLE_CONTROLLER)
#define ROLE_CONTROLLER
#endif

#if defined(ROLE_SLAVE) && !defined(ROLE_TARGET)
#define ROLE_TARGET
#endif

// Also map new names back to older ones for compatibility if needed
#if defined(ROLE_CONTROLLER) && !defined(ROLE_MASTER)
#define ROLE_MASTER
#endif

#if defined(ROLE_TARGET) && !defined(ROLE_SLAVE)
#define ROLE_SLAVE
#endif
