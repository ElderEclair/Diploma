#pragma once

struct Vect
{
    double nx = 0, ny = 0;
    const bool operator==(const Vect &other) const;
    double mult(const Vect &snd);
};

double Vect::mult(const Vect &snd)
{
    return nx * snd.ny - ny * snd.nx;
}

const bool Vect::operator==(const Vect &other) const
{
    return (nx == other.nx) &&
           (ny == other.ny);
}
