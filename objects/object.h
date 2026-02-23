//
// Created by arsen on 23/02/2026.
//

#ifndef ROVER_OBJECT_H
#define ROVER_OBJECT_H

class Object
{
public:
    Object();
    virtual ~Object();
    virtual int draw();// int чтобы отлавливать ошибки, если не сделаем что-то более мудрое
protected:
    //scale
    //sprite_filepath
    //coordinates
};

#endif //ROVER_OBJECT_H