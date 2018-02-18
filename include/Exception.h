//
// Created by dima on 18.02.18.
//

#ifndef STRING_CLASS_CPP_EXCEPTION_H
#define STRING_CLASS_CPP_EXCEPTION_H


class Exception {
protected:
    const char * message_ = nullptr;
public:
    Exception() = default;

    Exception (const Exception& other) = default;

    Exception& operator=(const Exception& other) = default;

    virtual ~Exception() = default;

    virtual const char* what(){
        return message_;
    };
};

class MathException : public Exception {
public:
    MathException(){
        this->message_ = "Math exception";
    };
};

class DivisionByZero : public MathException {
public:
    DivisionByZero(){
        this->message_ = "Division by zero exception";
    };
};

class RuntimeException : public Exception {
public:
    RuntimeException(const char* msg){
        this->message_ = msg;
    };
};

class OutOfRangeException : public Exception{
public:
    OutOfRangeException(){
        this->message_ = "Out of range exception";
    };
};

class MemoryException : public Exception{
public:
    MemoryException(){
        this->message_ = "Memory exception";
    };
};

class LogicException : public Exception{
public:
    LogicException(){
        this->message_ = "Logic exception";
    };
};

#endif //STRING_CLASS_CPP_EXCEPTION_H
