#include "OtherStructures.h"

simonenko::DelimeterIO::DelimeterIO(char exp) :
    exp_(exp)
{}

simonenko::LabelIO::LabelIO(std::string exp) :
    exp_(exp)
{}

simonenko::UllOctIO::UllOctIO(unsigned long long& ref) :
    ref_(ref)
{}

simonenko::StringIO::StringIO(std::string& ref) :
    ref_(ref)
{}

simonenko::ComplexIO::ComplexIO(std::complex<double>& ref) :
    ref_(ref)
{}

std::istream &simonenko::operator>>(std::istream& in, DelimeterIO&& dest) {
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

std::istream &simonenko::operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    std::string data = "";
    if ((in >> data) && (data != dest.exp_)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream &simonenko::operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    in >> simonenko::DelimeterIO('\"');
    std::getline(in, dest.ref_, '\"');
    return in;
}

std::istream &simonenko::operator>>(std::istream& in, UllOctIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char check = '0';
    unsigned long long num;
    in >> check >> std::skipws >> std::oct >> num >> std::skipws;
    if (check != '0')
        in.setstate(std::ios::failbit);
    else {
        dest.ref_ = num;
    }
    return in;
}

std::istream &simonenko::operator>>(std::istream& in, ComplexIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    double real = 0.0;
    double imag = 0.0;
    using sep = simonenko::DelimeterIO;
    in >> sep{ '#' } >> sep{ 'c' } >> sep{ '(' };
    in >> real >> imag >> sep{ ')' };
    dest.ref_.real(real);
    dest.ref_.imag(imag);
    return in;
}
