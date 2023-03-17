#include "FileWatcher.hpp"
#include <filesystem>
#include <iostream>

int main(const int argc, const char** argv) noexcept(true)
{
	std::filesystem::path inputPath;
	
	if (argc > 1)
	{
		inputPath = argv[1U];

		if (!std::filesystem::exists(inputPath))
		{
			std::cerr << inputPath << " isn't a valid file!\n";
			return -1;
		}
	}
	// setting the locale might give better error messages 
	// std::setlocale(LC_ALL, "en_US"); 
	std::filesystem::path pathToObeserve{ !inputPath.empty() ? inputPath : std::filesystem::current_path() };
	std::wcout << "Observing path: " << pathToObeserve << '\n';

	std::error_code error;
	FileWatcher fileWatcher(pathToObeserve,
		[](
			const std::filesystem::path filepath,
			const std::optional<std::filesystem::path> renamedNew,
			const EFileAction fileAction,
			const std::error_code ec
			) noexcept
		{
			if (fileAction == EFileAction::Error)
			{
				if (!filepath.empty())
					std::wcout << filepath << '\n';
				return;
			}

			if (ec)
			{
				std::cerr << "File watcher error: " << ec.value() << ", " << ec.message() << '\n';
				return;
			}
			else
			{
				switch (fileAction)
				{
					case EFileAction::Created:
					{
						std::wcout << L"Created: " << filepath << L'\n';
					} break;

					case EFileAction::Deleted:
					{
						std::wcout << L"Deleted: " << filepath << L'\n';
					} break;

					case EFileAction::Modified:
					{
						std::wcout << L"Modified: " << filepath << L'\n';
					} break;

					case EFileAction::Renamed:
					{
						assert(renamedNew.has_value());
						std::wcout << L"Renamed: " << filepath << L" to " << renamedNew.value() << L'\n';
					} break;

					case EFileAction::Error:
					{
						if (!ec)
							std::cerr << "Unknown filewatcher error had occured\n";
					} break;
				}
			}
		}, false, error);

	if (error)
	{
		std::cout << error.message() << '\n';
		return -1;
	}

	while (fileWatcher.IsWatching())
	{
	}

	if (error)
		std::cout << error.message() << '\n';

	return 0;
}