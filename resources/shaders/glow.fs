#version 330

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
//uniform vec4 colDiffuse;
uniform float glow_size = 1.5;
uniform vec3 glow_colour = vec3(0.4, 0.7490, 1.0);
uniform float glow_intensity = 4.0;
uniform float glow_threshold = 0.5;

void main() {

    vec4 color = texture2D(texture0, fragTexCoord);
    //float brightness = (color.r * 0.2126) + (color.g * 0.7152) + (color.b * 0.0722);
    //gl_FragColor = color * brightness;
    //gl_FragColor = color + (color * brightness);
    //vec4 pixel = texture(texture0, fragTexCoord);
    //if (pixel.a <= glow_threshold) {
    //    ivec2 size = textureSize(texture0, 0);
	
    //    float uv_x = fragTexCoord.x * size.x;
    //    float uv_y = fragTexCoord.y * size.y;

    //    float sum = 0.0;
    //    for (int n = 0; n < 9; ++n) {
    //        uv_y = (fragTexCoord.y * size.y) + (glow_size * float(n - 4.5));
    //        float h_sum = 0.0;
    //        h_sum += texelFetch(texture0, ivec2(uv_x - (4.0 * glow_size), uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x - (3.0 * glow_size), uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x - (2.0 * glow_size), uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x - glow_size, uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x, uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x + glow_size, uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x + (2.0 * glow_size), uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x + (3.0 * glow_size), uv_y), 0).a;
    //        h_sum += texelFetch(texture0, ivec2(uv_x + (4.0 * glow_size), uv_y), 0).a;
    //        sum += h_sum / 9.0;
    //    }

    //    gl_FragColor = vec4(glow_colour, (sum / 9.0) * glow_intensity);
    //}
    gl_FragColor = color;
}

