/*
** EPITECH PROJECT, 2020
** AFinder
** File description:
** AFinder.hpp
*/

#ifndef AFINDER_HPP_
#define AFINDER_HPP_

#include "IFinder.hpp"

class AFinder : public IFinder {
public:
    AFinder(void);

    virtual ~AFinder(void) = default;

    static const std::string &getFilePath() noexcept;

protected:
    virtual bool findRootFolder(void) final;

    virtual bool browseFolders(DIR *dir, const std::string &path) final;

    virtual bool isRefFile(const std::string &filename) const final;

protected:
    static std::string _finalPath;
    DIR *_dir;
};

#endif /* AFINDER_HPP_ */
