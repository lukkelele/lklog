#include "lklog/lklog.h"

namespace lklog {

	void init(level const level)
	{
		log::init();
		log::set_level(level);
	}

	namespace internal {

		void log(log_module const& mod, level const lvl, std::string_view msg)
		{
			static constexpr bool use_logger = true;
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
