/** @addtogroup math
 *  @{
 */
/*
  Copyright (C) 2016 D Levin (https://www.kfrlib.com)
  This file is part of KFR

  KFR is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  KFR is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with KFR.

  If GPL is not suitable for your project, you must purchase a commercial license to use KFR.
  Buying a commercial license is mandatory as soon as you develop commercial activities without
  disclosing the source code of your own applications.
  See https://www.kfrlib.com for details.
 */
#pragma once

#include "../function.hpp"

namespace kfr
{

namespace intrinsics
{

#if defined CMT_ARCH_SSE2 && defined KFR_NATIVE_INTRINSICS

KFR_SINTRIN f32x1 sqrt(const f32x1& x) { return slice<0, 1>(f32x4(_mm_sqrt_ss(*extend<4>(x)))); }
KFR_SINTRIN f64x1 sqrt(const f64x1& x)
{
    return slice<0, 1>(f64x2(_mm_sqrt_sd(_mm_setzero_pd(), *extend<2>(x))));
}
KFR_SINTRIN f32sse sqrt(const f32sse& x) { return _mm_sqrt_ps(*x); }
KFR_SINTRIN f64sse sqrt(const f64sse& x) { return _mm_sqrt_pd(*x); }

#if defined CMT_ARCH_AVX
KFR_SINTRIN f32avx sqrt(const f32avx& x) { return _mm256_sqrt_ps(*x); }
KFR_SINTRIN f64avx sqrt(const f64avx& x) { return _mm256_sqrt_pd(*x); }
#endif

#if defined CMT_ARCH_AVX512
KFR_SINTRIN f32avx512 sqrt(const f32avx512& x) { return _mm512_sqrt_ps(*x); }
KFR_SINTRIN f64avx512 sqrt(const f64avx512& x) { return _mm512_sqrt_pd(*x); }
#endif

KFR_HANDLE_ALL_SIZES_FLT_1(sqrt)

#else

// fallback
template <typename T, size_t N, typename Tout = flt_type<T>>
KFR_SINTRIN vec<Tout, N> sqrt(const vec<T, N>& x)
{
    return apply([](Tout x) { return std::sqrt(x); }, cast<Tout>(x));
}
#endif
KFR_I_FLT_CONVERTER(sqrt)
}
KFR_I_FN(sqrt)

}
