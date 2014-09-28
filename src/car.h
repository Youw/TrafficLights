#ifndef CAR_H
#define CAR_H

class Car
{
public:
    Car(float length, float width);

    float width() const;
    float length() const;

    Car& setFrontPos(float pos);
    float frontPos() const;

private:
    float my_length;
    float my_width;

    float my_pos;
};

#endif // CAR_H
