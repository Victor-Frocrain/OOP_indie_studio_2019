/*
** EPITECH PROJECT, 2020
** Finder
** File description:
** Finder.cpp
*/

#include "Finder.hpp"

Finder::Finder()
{
    if (!findRootFolder() || !browseFolders(_dir, _finalPath))
        _finalPath = "../ressources/";
}
