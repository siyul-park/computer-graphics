#version 330 core

in vec3 EntryPoint;
in vec4 ExitPointCoord;

out vec4 FragColor;

uniform sampler2D ExitPoints;
uniform sampler3D VolumeTex;
uniform vec2      ScreenSize;
uniform vec3      VolumeSize;

void main() {
    float step = max(VolumeSize.x, max(VolumeSize.r, VolumeSize.s));
    float stepSize = 1.0f / step;

    vec2 exitFragCoord = (ExitPointCoord.xy / ExitPointCoord.w + 1.0f) / 2.0f;
    vec3 exitPoint = texture(ExitPoints, exitFragCoord).xyz;

    vec3 dir = exitPoint - EntryPoint;
    float len = length(dir);

    if (len < stepSize) {
        FragColor = vec4(0.0f);
        return;
    }

    vec3 deltaDir = normalize(dir) * stepSize;
    float deltaDirLen = length(deltaDir);

    vec3 voxelCoord = EntryPoint;
    vec4 colorAcum = vec4(0.0f);
    float lengthAcum;
    vec4 backgoundColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    float min = 119.0f / 65535.0f;
    float max = 325.0f / 65535.0f;

    while (true) {
        float alpha = 1.0f;
        float intensity = texture(VolumeTex, voxelCoord).x / 256.0f;

        if (intensity > max) {
            alpha = 1.0f;
        } else if (intensity < min) {
            alpha = 0.0f;
        } else {
            alpha = min * abs(intensity - max) / (max - min) + max * abs(intensity - min) / (max - min);
        }

        vec4 colorSample = vec4(1.0f, 1.0f, 1.0f, alpha);
        if (colorSample.a > 0.0f) {
            colorSample.a = 1.0 - pow(1.0 - colorSample.a, stepSize * pow(step, 1.5f));
            colorAcum.rgb += (1.0f - colorAcum.a) * colorSample.rgb * colorSample.a;
            colorAcum.a += (1.0f - colorAcum.a) * colorSample.a;
        }

        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            colorAcum.rgb = colorAcum.rgb * colorAcum.a + (1 - colorAcum.a) * backgoundColor.rgb;
            break;
        } else if (colorAcum.a > 1.0f) {
            colorAcum.a = 1.0f;
            break;
        }
    }

    FragColor = colorAcum;
}