#ifndef QSDK_QSDK_LIBLOADER_HPP_
#define QSDK_QSDK_LIBLOADER_HPP_
#include <vector>
#include <string>

void initLibLoader();

void loadDynDevs(const char * path);
void addHandlerForExt(const char* ext, int(*callback)(const char *, const char *));

void getFilesWithExt(const char * path, const char * ext, std::vector<std::string> & output);
void loadSOFile(char * path_to_so);

#endif /* QSDK_QSDK_LIBLOADER_HPP_ */
