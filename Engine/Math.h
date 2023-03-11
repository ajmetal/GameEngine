#pragma once

// Clamp float value
float Clamp(float value, float min, float max)
{
    const float res = value < min ? min : value;
    return res > max ? max : res;
}

// Calculate linear interpolation between two floats
float Lerp(float start, float end, float amount)
{
    return start + amount * (end - start);
}

// Normalize input value within input range
float Normalize(float value, float start, float end)
{
    return (value - start) / (end - start);
}

// Remap input value within input range to output range
float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd)
{
    return (value - inputStart) / (inputEnd - inputStart) * (outputEnd - outputStart) + outputStart;
}