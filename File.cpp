#include "File.hpp"
#include <iostream>
#include <regex>

std::string GetFilePath(const std::string& path)
{
	std::regex reg(R"(\/[^\/]*?\..+$)");
	return std::regex_replace(path, reg, "/");
}

namespace util
{
	File::File(const std::string& path)
	{
		this->path = path;
	}

	File::~File()
	{
		close();
	}

	bool File::isOpen() const
	{
		return _fstream.has_value() ? _fstream.value().is_open() : false;
	}

	const void File::mkdirs()
	{
		auto directory = GetFilePath(path);
		if (!directory.empty())
		{
			fs::create_directories(directory);
		}
	}

	bool File::open(const std::ios_base::openmode& openmode)
	{
		if (!isOpen())
		{
			_fstream.value().open(path, openmode);
			return isOpen();
		}
		return false;
	}

	void File::ProvideOpen(const std::ios_base::openmode& openmode)
	{
		if (!open(openmode))
		{
			mkdirs();
			open(openmode);
		}
	}

	const void File::close()
	{
		if (isOpen())
		{
			_fstream.value().close();
		}
	}

	bool File::isDirectory() const
	{
		return fs::is_directory(path);
	}

	std::optional<std::list<std::string>> File::getListOfFiles()
	{
		if (!isDirectory())
			return {};

		std::list<std::string> files;
		for (const auto& entry : fs::directory_iterator(path))
			files.push_back(entry.path().string());

		return files;
	}

	std::optional<std::fstream>& File::fstream()
	{
		return _fstream;
	}

	std::optional<std::string> File::ReadAndClose(const std::string& path)
	{
		File file(path);
		if (file.open())
		{
			auto& Ofstream = file.fstream();
			if (Ofstream.has_value())
			{
				auto& fstream = Ofstream.value();
				auto content = std::string((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());
				file.close();

				return content;
			}
		}
		file.close();

		return {};
	}
}