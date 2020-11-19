/*
** EPITECH PROJECT, 2020
** AFinder
** File description:
** AFinder.cpp
*/

#include "AFinder.hpp"

AFinder::AFinder() : _dir(nullptr)
{}

std::string AFinder::_finalPath = "";

bool AFinder::findRootFolder()
{
    _dir = opendir(HOME);

    if (_dir == nullptr) {
        return false;
    }
    else {
        _finalPath += HOME;
    }
    return true;
}

bool AFinder::browseFolders(DIR *dir, const std::string &path)
{
    struct dirent *rddir = nullptr;
    bool isFound = false;

    if (dir != nullptr) {
        while ((rddir = readdir(dir)) && !isFound) {
            if (rddir != nullptr && rddir->d_type == DT_DIR && std::string(rddir->d_name) != ".." && std::string(rddir->d_name) != ".") {
                DIR *newDir = opendir((path + rddir->d_name).c_str());
                isFound = browseFolders(newDir, path + rddir->d_name + "/");
            }
            else if (rddir != nullptr && rddir->d_type == DT_REG) {
                std::string file(rddir->d_name);
                if (isRefFile(path + file)) {
                    _finalPath = path;
                    closedir(dir);
                    return true;
                }
            }
        }
        closedir(dir);
    }
    return isFound;
}

bool AFinder::isRefFile(const std::string &filename) const
{
    std::ifstream fs;

    if (filename.find(FILEREF) < filename.size()) {
        fs.open(filename);
        if (!fs.fail()) {
            std::string text((std::istreambuf_iterator<char>(fs)), (std::istreambuf_iterator<char>()));
            if (text == TEXTREF) {
                fs.close();
                return true;
            }
            fs.close();
        }
    }
    return false;
}

const std::string &AFinder::getFilePath() noexcept
{
    return _finalPath;
}
