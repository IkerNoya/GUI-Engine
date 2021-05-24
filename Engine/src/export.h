#ifndef EXPORT_H

#ifdef ENGINE_EXPORT

#define ENGINE_API __declspec(dllimport) // specify class for import

#else

#define ENGINE_API __declspec(dllexport) // specify class for export

#endif // ENGINE_EXPORT

#endif // !EXPORT_H

