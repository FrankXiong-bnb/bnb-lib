#ifndef ____bnb_Folder_H_
#define ____bnb_Folder_H_

_bnb_space_in

_declare_inline bool GetAppPath(char* path, _size_t n) { return (_getcwd(path, n) != nullptr); }

template<_size_t n> bool GetAppPath(char (&path)[n]) { return GetAppPath(path, n); }

_declare_inline bool GetAppPath(wchar_t* path, _size_t n) { return (_wgetcwd(path, n) != nullptr); }

template<_size_t n> bool GetAppPath(wchar_t (&path)[n]) { return GetAppPath(path, n); }










_bnb_space_out

#endif