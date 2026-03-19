#include "lklog/lklog.h"

namespace lklog {

	void init(const level level)
	{
		logger::init();
		logger::set_level(level);
	}

}
