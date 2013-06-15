#ifndef APRO_WINWINDOWIMP_H
#define APRO_WINWINDOWIMP_H

#include <Platform.h>
#include <WindowImplementation.h>
#include <SharedPointer.h>

using namespace APro;

class WinWindowImp : public WindowImplementation
{
    APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(WinWindowImp)

public:

    WinWindowImp();
    ~WinWindowImp();

public:

    const String getImplementationName() const;

public:

    bool init();
    void deinit();

    Implementation::ptr clone() const;

public:

    void loop();

public:

    void show();
    void hide();

    void move(int x, int y);
    void resize(size_t width, size_t height);

public:

    void setTitle(const String& title);
    void showCursor(bool m_show);

private:

    HINSTANCE mInstance;
    HWND handle;

};

#endif // APRO_WINWINDOWIMP_H

