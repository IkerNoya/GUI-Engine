#version 460 core
out vec4 fragColor;

uniform vec3 outColor;
uniform float thickness;
uniform float marker_radius;
uniform vec3 PointA;
uniform vec3 PointB;

in vec4 coords;

vec3 finalColor;

void marker(vec3 point){
	if(length(coords.xyz - point) < marker_radius){
			finalColor += outColor;
		}	
		
}

void drawLine(vec3 point1, vec3 point2){
	vec3 coord = coords.xyz;
	
	vec3 p1result = vec3(point2-point1);
	vec3 p2result = vec3(coord-point1);
	
	float dotResult = dot(p1result, p2result) / length(p1result); 
	
	vec3 p4 = point1 + normalize(p1result) * dotResult;
	
	if(length(p4 - coord) < thickness && length(p4 - point1) <= length(p1result) && length(p4 - point2) <= length(p1result)){
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