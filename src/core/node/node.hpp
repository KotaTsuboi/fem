#pragma once

class Node {
    public:
        virtual double X() const = 0;
        virtual double Y() const = 0;
        virtual double Z() const = 0;
        virtual int Index() const = 0;
        virtual ~Node() = default;
};

