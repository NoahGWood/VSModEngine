#include "Utils/fs.h"
#include "Core/Logger.h"
namespace Utils
{
    namespace FS
    {

        bool make_dir(const std::string &path)
        {
            return fs::create_directories(path);
        }

        bool write_file(const std::string &path, const std::string &content)
        {
            fs::path p(path);
            auto parent = p.parent_path();
            if (!parent.empty())
            {
                fs::create_directories(parent);
            }
            std::ofstream out(path);
            if (!out)
                return false;
            out << content;
            return true;
        }

        bool copy_file(const std::string &src, const std::string &dest)
        {
            try
            {
                make_dir(fs::path(dest).parent_path());
                fs::copy_file(src, dest, fs::copy_options::overwrite_existing);
                return true;
            }
            catch (const fs::filesystem_error &e)
            {
                CORE_ERROR("Error copying file: {}", e.what());
            }
            return false;
        }

        std::string read_file(const std::string &path)
        {
            std::ifstream in(path);
            std::stringstream buffer;
            buffer << in.rdbuf();
            return buffer.str();
        }

        bool path_exists(const std::string &path)
        {
            return fs::exists(path);
        }

        bool delete_path(const std::string &path)
        {
            return fs::remove_all(path) > 0;
        }

        std::vector<std::string> list_files(const std::string &path)
        {
            std::vector<std::string> results;
            for (auto &entry : fs::recursive_directory_iterator(path))
            {
                if (entry.is_regular_file())
                    results.push_back(entry.path().string());
            }

            return results;
        }

        std::vector<std::string> list_files_ext(const std::string &path, const std::string &extension)
        {
            std::vector<std::string> results;
            std::string _extension = extension;
            std::transform(_extension.begin(), _extension.end(), _extension.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });
            for (auto &entry : fs::recursive_directory_iterator(path))
            {
                if (entry.is_regular_file())
                {
                    std::string ext = entry.path().extension().string();
                    std::transform(ext.begin(), ext.end(), ext.begin(),
                                   [](unsigned char c)
                                   { return std::tolower(c); });
                    if (ext == _extension)
                        results.push_back(entry.path().string());
                }
            }
            return results;
        }
        bool replace_tokens_in_file(const std::string &filepath, const std::unordered_map<std::string, std::string> &tokens)
        {
            std::ifstream in(filepath);
            if (!in)
                return false;

            std::stringstream buffer;
            buffer << in.rdbuf();
            in.close();

            std::string content = buffer.str();
            for (const auto &[key, value] : tokens)
            {
                size_t pos = 0;
                while ((pos = content.find(key, pos)) != std::string::npos)
                {
                    content.replace(pos, key.length(), value);
                    pos += value.length();
                }
            }

            std::ofstream out(filepath);
            out << content;
            return true;
        }

        // bool detect_existing_project() {
        //     return fs::exists("nmtk.conf");
        // }
        // bool detect_existing_project(const fs::path path){
        //     return fs::exists(path / "nmtk.conf");
        // }
        // // bool detect_existing_project(const std::string& dir){
        // //     // return detect_existing_project(fs::path(dir));
        // // }
        // // bool detect_existing_project(const std::string_view& dir){
        // //     return detect_existing_project(fs::path(dir));
        // // }
        // // Returns the root project directory (if CWD is nested)
        // std::optional<fs::path> detect_root_project_dir(){
        //     fs::path path = fs::current_path();
        //     while(path != path.root_path()){
        //         if(detect_existing_project(path)){
        //             return path;
        //         }
        //         path = path.parent_path();
        //     }
        //     return std::nullopt;
        // }

        fs::path get_root_dir()
        {
#if defined(_WIN32)
            const char *appdata = std::getenv("APPDATA");
            return fs::path(appdata ? appdata : ".") / "VSModEngine";
#elif defined(__APPLE__)
            const char *home = std::getenv("HOME") return fs::path(home ? home : ".") / "Library/Application Support/VSModEngine";
#else
            // Modern linux
            const char *xdg = std::getenv("XDG_CONFIG_HOME");
            if (xdg)
                return fs::path(xdg) / "VSModEngine";
            // Legacy
            const char *home = std::getenv("HOME");
            if (home)
                return fs::path(home) / ".config/VSModEngine";
            // Fallback
            return fs::path(".VSModEngine");
#endif
        }

        fs::path get_tmp_dir()
        {
#if defined(_WIN32)
            char tempPath[MAX_PATH];
            DWORD len = GetTempPathA(MAX_PATH, tempPath);
            return fs::path(tempPath) / "VSModEngine";
#elif defined(__APPLE__)
            return fs::path("/tmp/VSModEngine");
#else
            if (fs::exists("/dev/shm"))
                return fs::path("/dev/shm/VSModEngine");
            return "/tmp/VSModEngine";
#endif
        }
    } // namespace FS

} // namespace Utils
