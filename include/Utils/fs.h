#pragma once
/**
 * @file Utils/FS.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Filesystem utilities
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"

namespace Utils
{
    namespace FS
    {
        // Creates a directory and all parent directories
        bool make_dir(const std::string &path);

        // Writes content to a file, creating parent directories if needed
        bool write_file(const std::string &path, const std::string &content);

        // Reads the entire content of a file
        std::string read_file(const std::string &path);

        // Copies a file from one location to another
        bool copy_file(const std::string &src, const std::string &dest);

        // Checks whether a file or directory exists
        bool path_exists(const std::string &path);

        // Recursively deletes a directory or file
        bool delete_path(const std::string &path);

        // Recursively lists files in a directory
        std::vector<std::string> list_files(const std::string &path);

        // Recursively lists files of a particular extension in a directory
        std::vector<std::string> list_files_ext(const std::string& path, const std::string& extension);

        // Replaces all tokens in a file with given values
        bool replace_tokens_in_file(const std::string &filepath, const std::unordered_map<std::string, std::string> &tokens);

        // Returns the root project directory (if CWD is nested)
        std::optional<fs::path> detect_root_project_dir();

        // Get VS Mod Engine root/global storage location
        fs::path get_root_dir();

        // Get the temporary storage directory
        fs::path get_tmp_dir();
    } // namespace FS

} // namespace Utils
