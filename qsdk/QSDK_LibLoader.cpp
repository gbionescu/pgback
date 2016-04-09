#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <map>
#include "util.h"
#include "QSDK_LibLoader.hpp"
#include "QSDK_SOLoader.hpp"
#include "QSDK_PyLoader.hpp"

void getFilesWithExt(const char * path, const char * ext, std::vector<std::string> & output)
{
    DIR * cdir;
    struct dirent *dir;

    cdir = opendir(path);

    if (cdir)
    {
        while ((dir = readdir(cdir)) != NULL)
        {
            if ((strlen(dir->d_name) >= strlen(ext)) && strcmp(dir->d_name + strlen(dir->d_name) - strlen(ext), ext) == 0)
            {
                output.push_back(std::string(dir->d_name));
            }
        }

        closedir(cdir);
    }
    else
    {
        cprint("Could not open directory %s.\n", path);
    }
}

static std::map<const char*, int(*)(const char*, const char*)> extMap;

void loadDynDevs(const char * path)
{
    std::vector<std::string> out;

    for (auto const &it : extMap)
    {
        getFilesWithExt(path, it.first, out);

        for (auto const &vit : out)
        {
            it.second(path, vit.data());
        }
        out.clear();
    }
}

void addHandlerForExt(const char* ext, int(*callback)(const char *, const char *))
{
    extMap[ext] = callback;
}

void initLibLoader()
{
    addHandlerForExt(".so",     &loadSOFile);
    addHandlerForExt(".dylib",  &loadSOFile);
    addHandlerForExt(".pyc",    &loadPYCFile);
}
