// FileName: common_math.h
// Copyright (c) 2025 Wonjin Kim. All rights reserved.

#ifndef COMMON_MATH_H
#define COMMON_MATH_H

// NOTE(wj): Constants
#define Pi32 3.14159265359f
#define Tau32 6.28318530717958647692f
#define EularNumber32 2.7182818284590452f

// NOTE(wj):Intrinsic & floating point operations 

#define SinF32(f) sinf(f)
#define CosF32(f) cosf(f)
#define TanF32(f) tanf(f)


// NOTE(wj): Vectors
union vec2
{
	struct
	{
		f32 x, y;
	};

	struct
	{
		f32 u, v;
	};

	f32 E[2];
};

union vec3
{
	struct
	{
		f32 x, y, z;
	};

	struct
	{
		f32 u, v, w;
	};

	struct
	{
		f32 r, g, b;
	};

	// NOTE(wj): swizzling
	struct
	{
		vec2 xy;
		f32  _;
	};

	struct
	{
		f32  _;
		vec2 yz;
	};

	f32 E[3];
};

union vec4
{
	vec4();
	vec4(f32 x_, f32 y_, f32 z_, f32 w_);

	struct
	{
		union
		{
			vec3 xyz;

			struct
			{
				f32 x, y, z;
			};
		};

		f32 w;
	};

	struct
	{
		union
		{
			vec3 rgb;

			struct
			{
				f32 r, g, b;
			};
		};

		f32 a;
	};

	struct
	{
		vec2 xy;
		f32 _1;
	};

	struct
	{
		f32 _2;
		vec2  yz;
		f32 _3;
	};

	struct
	{
		f32 _4;
		f32 _5;
		vec2 zw;
	};

	f32 E[4];
};




// NOTE(Wj): Constructors


// Matrix

#endif COMMON_MATH_H
