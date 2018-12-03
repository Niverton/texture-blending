#version 330 core

uniform sampler2D text;

in vec2 texcoords;
in vec2 smpcoords;

out vec4 out_color;

//hash = permute ?
//http://webstaff.itn.liu.se/~stegu/jgt2011/article.pdf

vec2 permute(vec2 uv){
  return mod(((uv*34.00)+1.0)*uv, 289.0f);
}

//https://en.wikipedia.org/wiki/Simplex_noise
vec2 skew (vec2 coord) {
    float n = 2;
    float F = (sqrt(n+1)-1)/n;
    return coord + (coord.x+coord.y)*F;
}

//https://thebookofshaders.com/11/
//http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
vec3 simplexGrid (vec2 st, out vec2 uv1, out vec2 uv2, out vec2 uv3) {
    vec3 w = vec3(0.0);

    vec2 sp = st;
    vec2 p = fract(sp);
    uv1 = sp;
    uv2 = uv1 + vec2(1.0,1.0);
    if (p.x > p.y) { // upper triangle
        w.xy = 1-vec2(p.x,p.y-p.x);
        w.z = p.y;
        uv3 = uv1 + vec2(1.0,0.0);
    } else { // lower triangle
        w.yz = 1.0-vec2(p.x-p.y,p.y);
        w.x = p.x;
        uv3 = uv1 + vec2(0.0,1.0);
    }
    return fract(w);
}

vec2 fpermute(vec2 v){
    return permute(floor(v)) + fract(v);
}

void main() {
  vec2 uv1, uv2, uv3;
  vec3 w = simplexGrid(smpcoords, uv1, uv2, uv3);
  
  //uv1 = fpermute(uv1);
  uv2 = fpermute(uv2);
  uv3 = fpermute(uv3);

  vec2 duvdx = dFdx(texcoords);
  vec2 duvdy = dFdy(texcoords);

  vec4 g1 = textureGrad(text, uv1/4.0, duvdx, duvdy);
  vec4 g2 = textureGrad(text, uv2/4.0, duvdx, duvdy);
  vec4 g3 = textureGrad(text, uv3/4.0, duvdx, duvdy);

  out_color = g1*w.r + g2*w.g + g3*w.b - vec4(vec3(0.5), 0.0);
  out_color /= sqrt(w.r*w.r + w.g*w.g + w.b*w.b);
  out_color += vec4(vec3(0.5), 0.0);
  out_color = vec4(floor(uv1)/8.0, 0.0, 1.0);
}
