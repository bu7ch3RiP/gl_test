#include "Searcher.h"

Searcher::Searcher(const fs::path path)
{
	this->path = path;
}

bool Searcher::finder(const fs::path& path, std::string& file_name)
{
    if (fs::is_directory(path))
    {
        fs::path temp_path = path;
        for (auto& p : fs::recursive_directory_iterator(temp_path, fs::directory_options::skip_permission_denied))
        {
            temp_path = p;
            if (temp_path.filename() == file_name)
            {
                set_path(temp_path);
                return true;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}

//void Searcher::work(std::string& file_name)
//{
//    set_list_of_root_dir();
//    std::stack<std::string> temp_s = get_list_of_root_dir();
//    //std::unique_lock<std::mutex> ul(mtx);
//    mtx.lock();
//    fs::path temp_p = temp_s.top();
//    if (temp_s.empty() == 0)
//        temp_s.pop();
//    mtx.unlock();
//    //ul.unlock();
//    if (fs::is_regular_file(temp_p) == 0)
//    {
//        if (finder(temp_p, file_name))
//        {
//            set_found(true);
//        }
//    }
//}

void Searcher::set_list_of_root_dir()
{
    for (const auto& file : fs::directory_iterator(ROOT_PATH))
        list_of_root_dir.push((file.path().string()));
}

fs::path Searcher::get_current_dir()
{
    return path;
}

bool Searcher::get_found()
{
    return this->found;
}

std::queue<std::string> Searcher::get_list_of_root_dir()
{
    return this->list_of_root_dir;
}

int Searcher::get_size_of_dir_list()
{
    return this->list_of_root_dir.size();
}

void Searcher::set_path(const fs::path& path)
{
    this->path = path;
}

void Searcher::set_found(const bool& found)
{
    this->found = found;
}
