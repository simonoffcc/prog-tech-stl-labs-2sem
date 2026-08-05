#include "OtherStructures.h"

DelimiterIO::DelimiterIO(char exp) :
    exp_(exp)
{}

PointIO::PointIO(Point& ref) :
    ref_(ref)
{}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp_)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, PointIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> DelimiterIO{ '(' } >> dest.ref_.x_ >> DelimiterIO{ ';' } >> dest.ref_.y_ >> DelimiterIO{ ')' };
}
