/*
** EPITECH PROJECT, 2020
** IFinder
** File description:
** IFinder.hpp
*/

#ifndef IFINDER_HPP_
#define IFINDER_HPP_

#define FILEREF ".testPath.txt"
#define TEXTREF "TestPath:GoodPath"

#include <string>
#include <fstream>
#include <iostream>

#ifndef WIN32
#define HOME "/home/"
#include <dirent.h>
#include <sys/types.h>
#endif /* WIN32 */

#ifdef WIN32
#define HOME "C:/"
#include "../../WINDOWS/dirent/include/dirent.h"
#endif /* WIN32 */

#ifndef HOME
#define HOME "/home/"
#endif /* HOME */

class IFinder {
public:
    virtual ~IFinder() = default;

    //virtual std::string getFilePath() const noexcept = 0;
protected:
    virtual bool findRootFolder() = 0;
    virtual bool browseFolders(DIR *dir, const std::string &path) = 0;
    virtual bool isRefFile(const std::string &filename) const = 0;
};

#endif /* IFINDER_HPP_ */
