#include "lklog/internal/utility.h"

#include <spdlog/common.h>

#include "internal/core.h"

namespace lklog::internal {

	std::string current_timestamp(std::string_view format)
	{
		using namespace std::chrono;
		time_point<system_clock> now = system_clock::now();
		std::time_t time = system_clock::to_time_t(now);

		std::stringstream stream;
		stream << std::put_time(std::localtime(&time), format.data());
		return stream.str();
	}

	/** Assuming the log files are formatted with a timestamp. */
	bool compare_logfiles(const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
	{
		return (a.path().filename().string() < b.path().filename().string());
	}

	std::size_t count_logfiles_in_dir(const std::filesystem::path& dir)
	{
		namespace fs = std::filesystem;
		if (!fs::exists(dir) || !fs::is_directory(dir)) {
			LKLOG_ASSERT(false, "Invalid directory");
			return 0;
		}

		std::size_t files = 0;
		for (const auto& entry : fs::directory_iterator(dir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".log") {
				files++;
			}
		}

		return files;
	}

	void clean_log_dir(const std::filesystem::path& dir, const std::size_t max_logfiles)
	{
		namespace fs = std::filesystem;
		if (!fs::exists(dir) || !fs::is_directory(dir)) {
			LKLOG_ASSERT(false, "Invalid directory");
			return;
		}

		std::vector<fs::directory_entry> logfiles;
		logfiles.reserve(max_logfiles);
		for (const auto& entry : fs::directory_iterator(dir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".log") {
				logfiles.push_back(entry);
			}
		}

		/* Sort and remove oldest logfiles. */
		if (logfiles.size() > max_logfiles) {
			/* Sort log files based on their names (timestamps in filenames). */
			std::sort(logfiles.begin(), logfiles.end(), compare_logfiles);

			/* Remove the oldest files, keeping only the most recent ones. */
			for (std::size_t idx = 0; idx < logfiles.size() - max_logfiles; idx++) {
				const fs::directory_entry& entry = logfiles[idx];
				if ((entry.path().extension() == ".log") && std::filesystem::exists(entry)) {
					std::filesystem::remove(entry.path());
				}
			}
		}
	}
}
