#include "lklog/lklog.h"

namespace lklog {

	void init(level lvl, std::string_view logfile)
	{
		log::init(lvl, logfile);
	}

	namespace internal {

		void log(log_module const& mod, level const lvl, std::string_view msg)
		{
			constexpr bool use_logger = true;
			if constexpr (use_logger) {
				log::print_msg_with_tag(lvl, mod.name, msg);
			} else {
				std::printf("[%.*s] %.*s\n",
					static_cast<int>(mod.name.size()), mod.name.data(),
					static_cast<int>(msg.size()), msg.data());
			}
		}
	}

}
