#pragma once
#include <list>
#include <optional>
#include <fstream>
#include <ostream>
#include <filesystem>
namespace fs = std::filesystem;

namespace util
{
	class File
	{
	private:
		std::optional<std::fstream> _fstream = std::optional(std::fstream());
		std::string path;
	public:
		File(const std::string& path);
		File(const File&) = delete;
		virtual ~File();

		// Return true if this file is open
		bool isOpen() const;

		// Create parent-folders if it's need
		const void mkdirs();

		// Open file, it's return true if it's successful and false if it's not
		bool open(const std::ios_base::openmode& openmode = (std::fstream::in | std::fstream::out | std::fstream::app));

		// if open return false, trying create parent-folders and then open this again
		void ProvideOpen(const std::ios_base::openmode& openmode = (std::fstream::in | std::fstream::out | std::fstream::app));

		// Close this file
		const void close();

		// True if it's Directory/Folder
		bool isDirectory() const;

		// Return list of strings which is path to file
		std::optional<std::list<std::string>> getListOfFiles();

		// In-Out File (Read, Write)
		std::optional<std::fstream>& fstream();

		// Read file if it's exist and return a optional string
		static std::optional<std::string> ReadAndClose(const std::string& path);
	};
}