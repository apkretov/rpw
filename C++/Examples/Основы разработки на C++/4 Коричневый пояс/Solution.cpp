#include "Common.h"

class Rectangle : public IShape {
private:
    Point position_;
    Size size_;
    std::shared_ptr<ITexture> texture_;

public:
    std::unique_ptr<IShape> Clone() const override {
        auto clone = std::make_unique<Rectangle>();
        clone->position_ = position_;
        clone->size_ = size_;
        clone->texture_ = texture_;
        return clone;
    }

    void SetPosition(Point position) override {
        position_ = position;
    }

    Point GetPosition() const override {
        return position_;
    }

    void SetSize(Size size) override {
        size_ = size;
    }

    Size GetSize() const override {
        return size_;
    }

    void SetTexture(std::shared_ptr<ITexture> texture) override {
        texture_ = texture;
    }

    ITexture* GetTexture() const override {
        return texture_.get();
    }

    void Draw(Image& image) const override {
        for (int y = 0; y < size_.height; ++y) {
            for (int x = 0; x < size_.width; ++x) {
                int img_x = position_.x + x;
                int img_y = position_.y + y;
                
                if (img_y >= 0 && img_y < static_cast<int>(image.size()) && 
                    img_x >= 0 && img_x < static_cast<int>(image[img_y].size())) {
                    
                    char pixel = '.';
                    if (texture_) {
                        Size tex_size = texture_->GetSize();
                        if (x < tex_size.width && y < tex_size.height) {
                            const auto& tex_image = texture_->GetImage();
                            pixel = tex_image[y][x];
                        }
                    }
                    image[img_y][img_x] = pixel;
                }
            }
        }
    }
};

class Ellipse : public IShape {
private:
    Point position_;
    Size size_;
    std::shared_ptr<ITexture> texture_;

public:
    std::unique_ptr<IShape> Clone() const override {
        auto clone = std::make_unique<Ellipse>();
        clone->position_ = position_;
        clone->size_ = size_;
        clone->texture_ = texture_;
        return clone;
    }

    void SetPosition(Point position) override {
        position_ = position;
    }

    Point GetPosition() const override {
        return position_;
    }

    void SetSize(Size size) override {
        size_ = size;
    }

    Size GetSize() const override {
        return size_;
    }

    void SetTexture(std::shared_ptr<ITexture> texture) override {
        texture_ = texture;
    }

    ITexture* GetTexture() const override {
        return texture_.get();
    }

    void Draw(Image& image) const override {
        for (int y = 0; y < size_.height; ++y) {
            for (int x = 0; x < size_.width; ++x) {
                if (IsPointInEllipse({x, y}, size_)) {
                    int img_x = position_.x + x;
                    int img_y = position_.y + y;
                    
                    if (img_y >= 0 && img_y < static_cast<int>(image.size()) && 
                        img_x >= 0 && img_x < static_cast<int>(image[img_y].size())) {
                        
                        char pixel = '.';
                        if (texture_) {
                            Size tex_size = texture_->GetSize();
                            if (x < tex_size.width && y < tex_size.height) {
                                const auto& tex_image = texture_->GetImage();
                                pixel = tex_image[y][x];
                            }
                        }
                        image[img_y][img_x] = pixel;
                    }
                }
            }
        }
    }
};

std::unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    if (shape_type == ShapeType::Rectangle) {
        return std::make_unique<Rectangle>();
    } else {
        return std::make_unique<Ellipse>();
    }
}