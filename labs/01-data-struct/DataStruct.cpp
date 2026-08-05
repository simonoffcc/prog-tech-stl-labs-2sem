#include "DataStruct.h"

std::istream &simonenko::operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    DataStruct input;
    {
        using sep = simonenko::DelimeterIO;
        in >> sep{ '(' } >> sep{ ':' };
        std::string get = "";
        for (int i = 0; i < 3; ++i) {
            in >> get;
            if (get == "key1") {
                in >> simonenko::UllOctIO{ input.key1 };
            }
            else if (get == "key2") {
                in >> simonenko::ComplexIO{ input.key2 };
            }
            else if (get == "key3") {
                in >> simonenko::StringIO{ input.key3 };
            }
            else {
                in.setstate(std::ios::failbit);
            }
            in >> sep{ ':' };
        }
        in >> sep{ ')' };
        if (in) {
            dest = input;
        }
    }
    return in;
}

std::ostream &simonenko::operator<<(std::ostream& out, const DataStruct& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    iofmtguard iofmtguard(out);
    out << "(";
    out << " : key1 " << "0" << std::oct << dest.key1;
    out << " : key2 " << "#c(" << dest.key2.real();
    double check1 = dest.key2.real();
    int check2 = dest.key2.real();
    if (check2 == check1) {
        out << ".0";
    }
    out << " " << dest.key2.imag();
    check1 = dest.key2.imag();
    check2 = dest.key2.imag();
    if (check2 == check1) {
        out << ".0";
    }
    out<< ")";
    out << " : key3 " << "\"" << dest.key3 << "\"";
    out << " : )";
    return out;
}

bool simonenko::comparator(const DataStruct& left, const DataStruct& right) {
    if (left.key1 != right.key1) {
        return left.key1 < right.key1;
    }
    if (left.key2 != right.key2) {
        return abs(left.key2) < abs(right.key2);
    }
    return left.key3 < right.key3;
}