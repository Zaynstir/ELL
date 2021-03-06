////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     IRVectorUtilities.h (emitters)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "EmitterTypes.h"
#include "IRFunctionEmitter.h"
#include "LLVMInclude.h"

// utilities
#include "TypeTraits.h"

namespace ell
{
namespace emitters
{
    /// <summary> Create an integer vector filled with copies of a value </summary>
    ///
    /// <typeparam name="ValueType"> The type of the value </typeparam>
    /// <param name="function"> The function being emitted </param>
    /// <param name="type"> The LLVM type of the result vector value </param>
    /// <param name="elementValue"> The value to place in the vector elements </param> 
    ///
    /// <returns> An LLVM vector with repeated entries of the indicated value </returns>
    template <typename ValueType, utilities::IsIntegral<ValueType> = true>
    llvm::Value* FillVector(IRFunctionEmitter& function, llvm::VectorType* type, ValueType elementValue);

    /// <summary> Create a floating-point vector filled with copies of a value </summary>
    ///
    /// <typeparam name="ValueType"> The type of the value </typeparam>
    /// <param name="function"> The function being emitted </param>
    /// <param name="type"> The LLVM type of the result vector value </param>
    /// <param name="elementValue"> The value to place in the vector elements </param> 
    ///
    /// <returns> An LLVM vector with repeated entries of the indicated value </returns>
    template <typename ValueType, utilities::IsFloatingPoint<ValueType> = true>
    llvm::Value* FillVector(IRFunctionEmitter& function, llvm::VectorType* type, ValueType elementValue);

    /// <summary> Compute the sum of the entries in a vector </summary>
    ///
    /// <param name="function"> The function being emitted </param>
    /// <param name="vectorValue"> The value to sum the elements of </param>
    ///
    /// <returns> The sum of the elements in the given vector </returns>
    template <typename ValueType>
    llvm::Value* HorizontalVectorSum(IRFunctionEmitter& function, llvm::Value* vectorValue);
}
}

#include "../tcc/IRVectorUtilities.tcc"
