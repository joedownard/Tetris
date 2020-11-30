#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 transform;

out vec4 vertex;

void main() {
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    vertex = vec4(gl_Position);
}