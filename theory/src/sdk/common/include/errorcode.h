#pragma once

#include"./common.h"


enum  ErrorCode {
    Success = 0,
    Failed,
    InvalidParameter,
    ExceedProcessPrimeRange,
    NoCoprime,
    CalcTiFailed,
};