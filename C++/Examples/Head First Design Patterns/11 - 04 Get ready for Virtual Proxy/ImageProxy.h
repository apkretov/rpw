#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

#pragma region Trae
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/virtualproxy
package headfirst.designpatterns.proxy.virtualproxy;

import java.net.*;
import java.awt.*;
import javax.swing.*;

class ImageProxy implements Icon { // The ImageProxy implements the Icon interface.
	volatile ImageIcon imageIcon; // The imageIcon is the REAL icon that we eventually want to display when it's loaded.
	final URL imageURL;
	Thread retrievalThread;
	boolean retrieving = false;

	public ImageProxy(URL url) { imageURL = url; } // We pass the URL of the image into the constructor.This is the image we need to display once it's loaded!

	public int getIconWidth() { // We return a default width and height until the imageIcon is loaded; then we turn it over to the imageIcon.
		if (imageIcon != null) {
			return imageIcon.getIconWidth();
		} else {
			return 800;
		}
	}

	public int getIconHeight() { // We return a default width and height until the imageIcon is loaded; then we turn it over to the imageIcon.
		if (imageIcon != null) {
			return imageIcon.getIconHeight();
		} else {
			return 600;
		}
	}

	synchronized void setImageIcon(ImageIcon imageIcon) {
		this.imageIcon = imageIcon;
	}

	public void paintIcon(final Component c, Graphics  g, int x,  int y) { // This method is called when it's time to paint the icon on the screen.
		if (imageIcon != null) {
			imageIcon.paintIcon(c, g, x, y); // If we've got an icon already, we go ahead and tell it to paint itself.
		} else {
			g.drawString("Loading album cover, please wait...", x+300, y+190);

			// Here's where things get interesting. This code paints the icon on the screen (by delegating to the imageIcon). However, if we don't have a fully created ImageIcon, then we create one.
			// Here's where we load the REAL icon image. Note that the image loading with IconImage is synchronous: the ImageIcon constructor doesn't return until the image is loaded. That doesn't give us much of a chance to do screen updates and have our message displayed, so we're going to do this asynchronously
			if (!retrieving) { // If we aren't already trying to retrieve the image...
				retrieving = true; // ...then it's time to start retrieving it (in case you were wondering, only one thread calls paint, so we should be okay here in terms of thread safety).

				retrievalThread = new Thread(new Runnable() { // We don't want to hang up the entire user interface, so we're going to use another thread to retrieve the image.
					public void run() { 
						try {
							setImageIcon(new ImageIcon(imageURL, "Album Cover")); // In our thread we instantiate the Icon object. Its constructor will not return until the image is loaded.
							c.repaint(); // When we have the image, we tell Swing that we need to be repainted.
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				});

				retrievalThread = new Thread(() -> {
						try {
							setImageIcon(new ImageIcon(imageURL, "Album Cover")); // In our thread we instantiate the Icon object. Its constructor will not return until the image is loaded.
							c.repaint(); // When we have the image, we tell Swing that we need to be repainted.
						} catch (Exception e) {
							e.printStackTrace();
						}
				});
				retrievalThread.start();

			}
		}
	}
}

package headfirst.designpatterns.proxy.virtualproxy;

import java.awt.*;
import javax.swing.*;

class ImageComponent extends JComponent {
	private static final long serialVersionUID = 1L;
	private Icon icon;

	public ImageComponent(Icon icon) {
		this.icon = icon;
	}

	public void setIcon(Icon icon) {
		this.icon = icon;
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		int w = icon.getIconWidth();
		int h = icon.getIconHeight();
		int x = (800 - w)/2;
		int y = (600 - h)/2;
		icon.paintIcon(this, g, x, y);
	}
}
*/
class Icon {
public:
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Paint(HDC hdc, int x, int y) = 0;
	virtual ~Icon() = default;
};

class ImageProxy : public Icon { // The ImageProxy implements the Icon interface.
	std::unique_ptr<Gdiplus::Image> imageIcon; // The imageIcon is the REAL icon that we eventually want to display when it's loaded.
	std::wstring imageURL;
	std::thread retrievalThread;
	std::atomic<bool> retrieving;
	mutable std::mutex imageMutex;
	HWND hwnd;
public:
	ImageProxy(const std::wstring &url, HWND window) : imageURL(url), retrieving(false), hwnd(window) {} // We pass the URL of the image into the constructor.This is the image we need to display once it's loaded!

	~ImageProxy() {
		if (retrievalThread.joinable())
			retrievalThread.join();
	}

	int GetWidth() const override {
		std::lock_guard<std::mutex> guard(imageMutex);
		return imageIcon ? imageIcon->GetWidth() : 800;
	} // We return a default width and height until the imageIcon is loaded; then we turn it over to the imageIcon.
	int GetHeight() const override {
		std::lock_guard<std::mutex> guard(imageMutex);
		return imageIcon ? imageIcon->GetHeight() : 600;
	} // We return a default width and height until the imageIcon is loaded; then we turn it over to the imageIcon.
	void Paint(HDC hdc, int x, int y) override;
};
#pragma endregion //Trae
