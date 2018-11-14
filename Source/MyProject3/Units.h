// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
constexpr float operator"" _cm( long double _cm )
{
    return _cm;
}

constexpr float operator"" _m( long double _cm )
{
    return _cm * 100.0;
}

constexpr float operator"" _cm( unsigned long long int _cm )
{
    return _cm;
}

constexpr float operator"" _m( unsigned long long int _cm )
{
    return _cm * 100.0;
}

#define UNIT(x) x