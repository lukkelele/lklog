# lklog

Logging abstraction for my projects.


## Usage

```cpp
#include <lklog/lklog.h>

/* Initialize lklog */
lklog::init(lklog::level log_level, std::string_view log_file);

/* Example */
lklog::init(lklog::level::debug, "logfile.txt");
/* ... all set! */
```
<br>

Both functions and macros can be used, use what you prefer.
```cpp
/* Functions */
lklog::trace(...)
lklog::debug(...)
lklog::info(...)
lklog::warn(...)
lklog::error(...)
lklog::fatal(...)

/* Example */
lklog::info("the result is {} and {}", 3, 9.5f)
lklog::debug("pi: {:.9f}", 3.14159265359)

/* Macros */
LKLOG_TRACE(...)
LKLOG_DEBUG(...)
LKLOG_INFO(...)
LKLOG_WARN(...)
LKLOG_ERROR(...)
LKLOG_FATAL(...)

/* Example */
LKLOG_INFO("the result is {} and {}", 3, 9.5f)
LKLOG_DEBUG("pi: {:.9f}", 3.14159265359)

/* Adds a tag before the log message */
LKLOG_TRACE_TAG(tag, ...)
LKLOG_DEBUG_TAG(tag, ...)
LKLOG_INFO_TAG(tag, ...)
LKLOG_WARN_TAG(tag, ...)
LKLOG_ERROR_TAG(tag, ...)
LKLOG_FATAL_TAG(tag, ...)

/* Example */
LKLOG_INFO_TAG("result_subsystem", "the result is {} and {}", 3, 9.5f)
LKLOG_DEBUG_TAG("math", "pi: {:.9f}", 3.14159265359)
```
<br>

Building with **LKLOG_ADD_LOG_MACROS** adds the following macros for a more 'standard' logging API.  
Enabled by default.
```cpp
LOG_TRACE(...)
LOG_DEBUG(...)
LOG_INFO(...)
LOG_WARN(...)
LOG_ERROR(...)
LOG_FATAL(...)

LOG_TRACE_TAG(tag, ...)
LOG_DEBUG_TAG(tag, ...)
LOG_INFO_TAG(tag, ...)
LOG_WARN_TAG(tag, ...)
LOG_ERROR_TAG(tag, ...)
LOG_FATAL_TAG(tag, ...)
```

### Modules

Inspired by [Zephyr](https://github.com/zephyrproject-rtos/zephyr)'s log system.  
The module name is placed as a tag in every log automatically.  
> :warning: Modules are only used/supported when using the log macros, for now :warning:

```cpp
/**
 * Define a module. 
 * Used ONCE per module.
 */
LKLOG_MODULE_DEFINE(<module_name>);

/* Example */
LKLOG_MODULE_DEFINE(lukas_module);

/**
 * Declare a module. 
 * Most use cases for this is in headers to make a module accessable from multiple files.
 * A module that is only used in one .cpp file does not need to be declared.
 */
LKLOG_MODULE_DECLARE(<module_name>);

/* Example */
LKLOG_MODULE_DECLARE(lukas_module);
```

---

## Todo
:black_square_button: Use std\:\:source_location in macro invocations<br>
:black_square_button: Option to use std\:\:source_location in untagged and non-module logs<br>
:black_square_button: Custom sink to capture output in tests so length and formatting can be validated<br>
:black_square_button: Logfile placement is broken<br>

