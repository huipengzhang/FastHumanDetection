#include "fhd_math.h"
#include <math.h>
#include <float.h>
#include <assert.h>

fhd_vec2 fhd_vec2_sub(fhd_vec2 a, fhd_vec2 b) {
  fhd_vec2 r;
  r.x = a.x - b.x;
  r.y = a.y - b.y;
  return r;
}

fhd_vec2 fhd_vec2_normalize(fhd_vec2 v) {
  const float a = sqrtf(v.x * v.x + v.y * v.y);
  return fhd_vec2{v.x / a, v.y / a};
}

fhd_vec2 fhd_vec2_mul(fhd_vec2 a, float s) { return {a.x * s, a.y * s}; }

fhd_vec2 fhd_vec2_mul_pcw(fhd_vec2 a, fhd_vec2 b) {
  return {a.x * b.x, a.y * b.y};
}

float fhd_vec2_distance(fhd_vec2 a, fhd_vec2 b) {
  return hypotf(b.x - a.x, b.y - a.y);
}

float fhd_vec2_length(fhd_vec2 v) { return sqrtf(v.x * v.x + v.y * v.y); }

fhd_vec3 fhd_vec3_normalize(fhd_vec3 v) {
  const float a = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  return fhd_vec3{v.x / a, v.y / a, v.z / a};
}

float fhd_vec3_dot(fhd_vec3 a, fhd_vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

fhd_vec3 fhd_vec3_sub(fhd_vec3 a, fhd_vec3 b) {
  fhd_vec3 r;
  r.x = a.x - b.x;
  r.y = a.y - b.y;
  r.z = a.z - b.z;
  return r;
}

fhd_vec3 fhd_vec3_cross(fhd_vec3 u, fhd_vec3 v) {
  const float t1 = u.x - u.y;
  const float t2 = v.y + v.z;
  const float t3 = u.x * v.z;
  const float t4 = t1 * t2 - t3;

  fhd_vec3 r;
  r.x = v.y * (t1 - u.z) - t4;
  r.y = u.z * v.x - t3;
  r.z = t4 - u.y * (v.x - t2);

  return r;
}

void fhd_aabb_expand(fhd_aabb* bbox, fhd_vec2 point) {
  if (point.x < bbox->top_left.x)
    bbox->top_left.x = point.x;
  else if (point.x > bbox->bot_right.x)
    bbox->bot_right.x = point.x;

  if (point.y < bbox->top_left.y)
    bbox->top_left.y = point.y;
  else if (point.y > bbox->bot_right.y)
    bbox->bot_right.y = point.y;
}

fhd_vec2 fhd_aabb_center(const fhd_aabb* bbox) {
  return {(bbox->bot_right.x + bbox->top_left.x) * 0.5f,
          (bbox->bot_right.y + bbox->top_left.y) * 0.5f};
}

bool fhd_aabb_overlap(const fhd_aabb* a, const fhd_aabb* b) {
  if (a->bot_right.x < b->top_left.x || a->top_left.x > b->bot_right.x)
    return false;
  if (a->bot_right.y < b->top_left.y || a->top_left.y > b->bot_right.y)
    return false;

  return true;
}

fhd_vec2 fhd_aabb_size(const fhd_aabb* a) {
  fhd_vec2 r;
  r.x = a->bot_right.x - a->top_left.x;
  r.y = a->bot_right.y - a->top_left.y;
  return r;
}

fhd_aabb fhd_aabb_from_points(const fhd_vec2* points, int len) {
  assert(len >= 2);

  fhd_aabb bbox = {{FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX}};

  for (int i = 0; i < len; i++) {
    fhd_aabb_expand(&bbox, points[i]);
  }

  return bbox;
}

float fhd_plane_point_dist(fhd_plane p, fhd_vec3 q) {
  return (fhd_vec3_dot(p.n, q) - p.d) / fhd_vec3_dot(p.n, p.n);
}

fhd_plane fhd_make_plane(fhd_vec3 a, fhd_vec3 b, fhd_vec3 c) {
  fhd_plane p;
  p.n = fhd_vec3_normalize(fhd_vec3_cross(fhd_vec3_sub(b, a), fhd_vec3_sub(c, a)));
  p.d = fhd_vec3_dot(p.n, a);
  return p;
}
