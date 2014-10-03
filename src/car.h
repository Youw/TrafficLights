#ifndef CAR_H
#define CAR_H

class QImage;

class Car
{
public:
    Car(float length, float width);

    float width() const;
    float length() const;

    Car& setFrontPos(float pos);
    float frontPos() const;

    Car& setImage(QImage *image);
    QImage *image() const;

private:
    float my_length;
    float my_width;

    float my_pos = 0;

    QImage *car_image = 0;
};

#endif // CAR_H
