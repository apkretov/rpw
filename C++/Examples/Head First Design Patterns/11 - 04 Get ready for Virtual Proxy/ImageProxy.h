#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <memory>
#include <thread>
#include <atomic>

#pragma region Trae
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/proxy/virtualproxy
package headfirst.designpatterns.proxy.virtualproxy;

import java.net.*;
import java.awt.*;
import javax.swing.*;

class ImageProxy implements Icon {
	volatile ImageIcon imageIcon;
	final URL imageURL;
	Thread retrievalThread;
	boolean retrieving = false;

	public ImageProxy(URL url) { imageURL = url; }

	public int getIconWidth() {
		if (imageIcon != null) {
			return imageIcon.getIconWidth();
		} else {
			return 800;
		}
	}

	public int getIconHeight() {
		if (imageIcon != null) {
			return imageIcon.getIconHeight();
		} else {
			return 600;
		}
	}

	synchronized void setImageIcon(ImageIcon imageIcon) {
		this.imageIcon = imageIcon;
	}

	public void paintIcon(final Component c, Graphics  g, int x,  int y) {
		if (imageIcon != null) {
			imageIcon.paintIcon(c, g, x, y);
		} else {
			g.drawString("Loading album cover, please wait...", x+300, y+190);
			if (!retrieving) {
				retrieving = true;

				retrievalThread = new Thread(new Runnable() {
					public void run() {
						try {
							setImageIcon(new ImageIcon(imageURL, "Album Cover"));
							c.repaint();
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				});

				retrievalThread = new Thread(() -> {
						try {
							setImageIcon(new ImageIcon(imageURL, "Album Cover"));
							c.repaint();
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

class ImageProxy : public Icon {
private:
	std::unique_ptr<Gdiplus::Image> imageIcon;
	std::wstring imageURL;
	std::thread retrievalThread;
	std::atomic<bool> retrieving;
	HWND hwnd;

public:
	ImageProxy(const std::wstring &url, HWND window)
		: imageURL(url), retrieving(false), hwnd(window) {
	}

	~ImageProxy() {
		if (retrievalThread.joinable()) {
			retrievalThread.join();
		}
	}

	int GetWidth() const override {
		return imageIcon ? imageIcon->GetWidth() : 800;
	}

	int GetHeight() const override {
		return imageIcon ? imageIcon->GetHeight() : 600;
	}

	void Paint(HDC hdc, int x, int y) override;
};
#pragma endregion //Trae
