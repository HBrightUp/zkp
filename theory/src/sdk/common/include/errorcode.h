#pragma once

#include"./common.h"


enum  ErrorCode {
    Success = 0,
    InvalidParameter,
    ExceedProcessPrimeRange,
    NoCoprime,
    CalcTiFailed,
};