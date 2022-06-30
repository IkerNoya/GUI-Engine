#version 460 core
out vec4 fragColor;
in vec3 outColor;

uniform float thiccness;
uniform float marker_radius;
uniform vec2 PointA;
uniform vec2 PointB;

vec3 finalColor;

void marker(vec2 point){
	if(length(gl_FragCoord.xy - point) < marker_radius){
			finalColor += outColor;
		}	
}

void drawLine(vec2 point1, vec2 point2){
	vec2 coord = gl_FragCoord.xy;
	
	vec2 p1result = vec2(point2-point1);
	vec2 p2result = vec2(coord-point1);
	
	float dotResult = dot(p1result, p2result) / length(p1result); 
	
	vec2 p4 = point1 + normalize(p1result) * dotResult;
	
	if(length(p4 - coord) < thiccness && length(p4 - point1) <= length(p1result) && length(p4 - point2) <= length(p1result)){
		finalColor += outColor;	
	}
	marker(point1);
	marker(point2);	
}

void main(){
	finalColor = vec3(0);

	drawLine(PointA, PointB);

	fragColor = vec4(finalColor, 1.0);
}