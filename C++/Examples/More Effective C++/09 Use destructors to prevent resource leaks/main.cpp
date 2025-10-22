struct WINDOW_HANDLE {}; //MINE

class WindowHandle { // class for acquiring and releasing a window handle
public:
	WindowHandle(WINDOW_HANDLE handle) : w(handle) {}
	~WindowHandle() { destroyWindow(w); }
	operator WINDOW_HANDLE() { return w; } // see below
private:
	WINDOW_HANDLE w;
	WindowHandle(const WindowHandle&); // The following functions are declared private to prevent // multiple copies of a WINDOW_HANDLE from being created. // See Item 28 for a discussion of a more flexible approach.
	WindowHandle& operator=(const WindowHandle&);
	void destroyWindow(WINDOW_HANDLE W) {} //MINE
};